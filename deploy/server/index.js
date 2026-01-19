/**
 * Everywhere Airlines - Secure Web Terminal Server
 * Ultra-secure, sandboxed terminal for C++ CLI application
 *
 * Security Features:
 * - Session isolation with unique IDs
 * - Rate limiting per IP
 * - Connection timeouts
 * - Input sanitization
 * - Resource limits
 * - No shell escape possible (direct binary execution)
 */

const express = require('express');
const http = require('http');
const WebSocket = require('ws');
const pty = require('node-pty');
const path = require('path');
const crypto = require('crypto');
const helmet = require('helmet');
const rateLimit = require('express-rate-limit');

// Configuration
const CONFIG = {
    PORT: process.env.PORT || 3000,
    MAX_SESSIONS: parseInt(process.env.MAX_SESSIONS) || 50,
    SESSION_TIMEOUT: parseInt(process.env.SESSION_TIMEOUT) || 600000, // 10 minutes
    BINARY_PATH: process.env.BINARY_PATH || '/app/airlines',
    ALLOWED_ORIGINS: (process.env.ALLOWED_ORIGINS || '*').split(','),
    RATE_LIMIT_WINDOW: 60000, // 1 minute
    RATE_LIMIT_MAX: 10, // connections per window
    HEARTBEAT_INTERVAL: 30000,
    MAX_INPUT_LENGTH: 1024,
};

// Session storage
const sessions = new Map();

// Express app setup
const app = express();

// Security middleware
app.use(helmet({
    contentSecurityPolicy: {
        directives: {
            defaultSrc: ["'self'"],
            scriptSrc: ["'self'", "'unsafe-inline'", "cdn.jsdelivr.net", "unpkg.com"],
            styleSrc: ["'self'", "'unsafe-inline'", "cdn.jsdelivr.net", "fonts.googleapis.com"],
            fontSrc: ["'self'", "fonts.gstatic.com", "cdn.jsdelivr.net"],
            connectSrc: ["'self'", "wss:", "ws:"],
            imgSrc: ["'self'", "data:", "blob:"],
        },
    },
    crossOriginEmbedderPolicy: false,
}));

// Rate limiting for HTTP requests
const httpLimiter = rateLimit({
    windowMs: CONFIG.RATE_LIMIT_WINDOW,
    max: 100,
    message: { error: 'Too many requests, please try again later.' },
    standardHeaders: true,
    legacyHeaders: false,
});

app.use(httpLimiter);

// Serve static files
app.use(express.static(path.join(__dirname, '../public'), {
    maxAge: '1h',
    etag: true,
}));

// Health check endpoint
app.get('/health', (req, res) => {
    res.json({
        status: 'healthy',
        sessions: sessions.size,
        maxSessions: CONFIG.MAX_SESSIONS,
        uptime: process.uptime(),
    });
});

// Session info endpoint
app.get('/api/session-info', (req, res) => {
    res.json({
        available: sessions.size < CONFIG.MAX_SESSIONS,
        currentSessions: sessions.size,
        maxSessions: CONFIG.MAX_SESSIONS,
    });
});

// Create HTTP server
const server = http.createServer(app);

// WebSocket server
const wss = new WebSocket.Server({
    server,
    path: '/terminal',
    maxPayload: CONFIG.MAX_INPUT_LENGTH * 2,
    clientTracking: true,
});

// Rate limiting for WebSocket connections
const connectionAttempts = new Map();

function checkConnectionRateLimit(ip) {
    const now = Date.now();
    const attempts = connectionAttempts.get(ip) || [];

    // Clean old attempts
    const validAttempts = attempts.filter(t => now - t < CONFIG.RATE_LIMIT_WINDOW);

    if (validAttempts.length >= CONFIG.RATE_LIMIT_MAX) {
        return false;
    }

    validAttempts.push(now);
    connectionAttempts.set(ip, validAttempts);

    return true;
}

// Session class for managing terminal instances
class TerminalSession {
    constructor(ws, sessionId) {
        this.ws = ws;
        this.sessionId = sessionId;
        this.pty = null;
        this.createdAt = Date.now();
        this.lastActivity = Date.now();
        this.isAlive = true;
        this.inputBuffer = '';
    }

    start() {
        try {
            // Use binary directory as working directory (works in Docker and locally)
            const workingDir = path.dirname(CONFIG.BINARY_PATH);

            // Spawn the C++ binary directly - no shell access
            this.pty = pty.spawn(CONFIG.BINARY_PATH, [], {
                name: 'xterm-256color',
                cols: 120,
                rows: 40,
                cwd: workingDir,
                env: {
                    TERM: 'xterm-256color',
                    LANG: 'en_US.UTF-8',
                    LC_ALL: 'en_US.UTF-8',
                },
            });

            // Handle output from the binary
            this.pty.onData((data) => {
                this.lastActivity = Date.now();
                if (this.ws.readyState === WebSocket.OPEN) {
                    this.ws.send(JSON.stringify({ type: 'output', data }));
                }
            });

            // Handle binary exit
            this.pty.onExit(({ exitCode, signal }) => {
                console.log(`Session ${this.sessionId} exited: code=${exitCode}, signal=${signal}`);
                if (this.ws.readyState === WebSocket.OPEN) {
                    this.ws.send(JSON.stringify({
                        type: 'exit',
                        code: exitCode,
                        message: '\r\n\x1b[1;36m[Sesion terminada - La aplicacion ha finalizado]\x1b[0m\r\n' +
                                 '\x1b[1;33mPresiona el boton "Reiniciar" para comenzar de nuevo.\x1b[0m\r\n'
                    }));
                }
                this.cleanup();
            });

            console.log(`Session ${this.sessionId} started`);
            return true;
        } catch (error) {
            console.error(`Failed to start session ${this.sessionId}:`, error);
            return false;
        }
    }

    write(data) {
        if (this.pty && data.length <= CONFIG.MAX_INPUT_LENGTH) {
            this.lastActivity = Date.now();
            // Sanitize input - only allow printable ASCII and control chars
            const sanitized = data.replace(/[^\x00-\x7F]/g, '');
            this.pty.write(sanitized);
        }
    }

    resize(cols, rows) {
        if (this.pty) {
            // Validate dimensions
            cols = Math.min(Math.max(cols, 20), 500);
            rows = Math.min(Math.max(rows, 10), 200);
            this.pty.resize(cols, rows);
        }
    }

    cleanup(removeFromSessions = true) {
        if (this.pty) {
            try {
                this.pty.kill();
            } catch (e) {
                // Ignore errors during cleanup
            }
            this.pty = null;
        }
        if (removeFromSessions) {
            sessions.delete(this.sessionId);
        }
        console.log(`Session ${this.sessionId} cleaned up. Active sessions: ${sessions.size}`);
    }
}

// WebSocket connection handler
wss.on('connection', (ws, req) => {
    const ip = req.headers['x-forwarded-for']?.split(',')[0]?.trim() ||
               req.socket.remoteAddress ||
               'unknown';

    // Rate limit check
    if (!checkConnectionRateLimit(ip)) {
        ws.close(4029, 'Rate limit exceeded');
        console.log(`Rate limited connection from ${ip}`);
        return;
    }

    // Session limit check
    if (sessions.size >= CONFIG.MAX_SESSIONS) {
        ws.send(JSON.stringify({
            type: 'error',
            message: 'Server at capacity. Please try again later.',
        }));
        ws.close(4030, 'Server at capacity');
        console.log(`Rejected connection from ${ip}: server at capacity`);
        return;
    }

    // Create session
    const sessionId = crypto.randomBytes(16).toString('hex');
    const session = new TerminalSession(ws, sessionId);
    sessions.set(sessionId, session);

    console.log(`New connection from ${ip}, session: ${sessionId}`);

    // Send welcome message
    ws.send(JSON.stringify({
        type: 'connected',
        sessionId,
        message: 'Connected to Everywhere Airlines Terminal',
    }));

    // Start the terminal
    if (!session.start()) {
        ws.send(JSON.stringify({
            type: 'error',
            message: 'Failed to start terminal session',
        }));
        ws.close(4031, 'Terminal start failed');
        return;
    }

    // Heartbeat
    ws.isAlive = true;
    ws.on('pong', () => {
        ws.isAlive = true;
        session.lastActivity = Date.now();
    });

    // Message handler
    ws.on('message', (message) => {
        try {
            const msg = JSON.parse(message.toString());

            switch (msg.type) {
                case 'input':
                    if (typeof msg.data === 'string') {
                        session.write(msg.data);
                    }
                    break;

                case 'resize':
                    if (typeof msg.cols === 'number' && typeof msg.rows === 'number') {
                        session.resize(msg.cols, msg.rows);
                    }
                    break;

                case 'restart':
                    // Allow restarting the session (keep in sessions map)
                    session.cleanup(false);
                    if (session.start()) {
                        ws.send(JSON.stringify({
                            type: 'restarted',
                            message: 'Session restarted successfully',
                        }));
                    }
                    break;

                case 'ping':
                    ws.send(JSON.stringify({ type: 'pong' }));
                    break;
            }
        } catch (e) {
            console.error(`Invalid message from ${sessionId}:`, e.message);
        }
    });

    // Disconnect handler
    ws.on('close', () => {
        console.log(`Connection closed: ${sessionId}`);
        session.cleanup();
    });

    // Error handler
    ws.on('error', (error) => {
        console.error(`WebSocket error for ${sessionId}:`, error.message);
        session.cleanup();
    });
});

// Heartbeat interval
const heartbeatInterval = setInterval(() => {
    wss.clients.forEach((ws) => {
        if (ws.isAlive === false) {
            return ws.terminate();
        }
        ws.isAlive = false;
        ws.ping();
    });
}, CONFIG.HEARTBEAT_INTERVAL);

// Session timeout check
const timeoutInterval = setInterval(() => {
    const now = Date.now();
    sessions.forEach((session, sessionId) => {
        if (now - session.lastActivity > CONFIG.SESSION_TIMEOUT) {
            console.log(`Session ${sessionId} timed out`);
            session.ws.send(JSON.stringify({
                type: 'timeout',
                message: '\r\n\x1b[1;31m[Session timed out due to inactivity]\x1b[0m\r\n',
            }));
            session.cleanup();
            session.ws.close(4032, 'Session timeout');
        }
    });
}, 60000);

// Graceful shutdown
function shutdown() {
    console.log('Shutting down server...');

    clearInterval(heartbeatInterval);
    clearInterval(timeoutInterval);

    // Close all sessions
    sessions.forEach((session) => {
        session.cleanup();
    });

    wss.close(() => {
        server.close(() => {
            console.log('Server shut down complete');
            process.exit(0);
        });
    });

    // Force exit after 10 seconds
    setTimeout(() => {
        console.error('Forced shutdown');
        process.exit(1);
    }, 10000);
}

process.on('SIGTERM', shutdown);
process.on('SIGINT', shutdown);

// Start server
server.listen(CONFIG.PORT, '0.0.0.0', () => {
    console.log(`
╔═══════════════════════════════════════════════════════════════╗
║           Everywhere Airlines - Web Terminal Server           ║
╠═══════════════════════════════════════════════════════════════╣
║  Port: ${CONFIG.PORT.toString().padEnd(54)}║
║  Max Sessions: ${CONFIG.MAX_SESSIONS.toString().padEnd(46)}║
║  Session Timeout: ${(CONFIG.SESSION_TIMEOUT / 1000 / 60).toString().padEnd(43)}min ║
║  Binary Path: ${CONFIG.BINARY_PATH.padEnd(47)}║
╚═══════════════════════════════════════════════════════════════╝
    `);
});

module.exports = { app, server };
