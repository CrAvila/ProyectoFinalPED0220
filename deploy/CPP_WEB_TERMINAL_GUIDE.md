# Ultimate Guide: C++ CLI App to Secure Web Terminal

> Complete guide to transform any C++ CLI application into a secure, dockerized web terminal accessible from anywhere.

---

## Table of Contents
1. [Architecture Overview](#architecture-overview)
2. [C++ Application Best Practices](#c-application-best-practices)
3. [Web Terminal Server](#web-terminal-server)
4. [Frontend Terminal UI](#frontend-terminal-ui)
5. [Docker Security Hardening](#docker-security-hardening)
6. [Production Deployment](#production-deployment)
7. [Quick Reference](#quick-reference)

---

## Architecture Overview

```
┌─────────────────────────────────────────────────────────────────┐
│                         BROWSER                                  │
│  ┌─────────────────────────────────────────────────────────┐   │
│  │                    xterm.js                              │   │
│  │              (Terminal Emulator)                         │   │
│  └─────────────────────────────────────────────────────────┘   │
│                            │                                     │
│                     WebSocket                                    │
└────────────────────────────┼────────────────────────────────────┘
                             │
┌────────────────────────────┼────────────────────────────────────┐
│                     DOCKER CONTAINER                             │
│  ┌─────────────────────────┼───────────────────────────────┐   │
│  │              Node.js Server                              │   │
│  │         (Express + WebSocket + node-pty)                 │   │
│  └─────────────────────────┼───────────────────────────────┘   │
│                            │                                     │
│                      PTY (stdin/stdout)                          │
│                            │                                     │
│  ┌─────────────────────────┼───────────────────────────────┐   │
│  │              C++ Binary                                  │   │
│  │         (Your CLI Application)                           │   │
│  └─────────────────────────────────────────────────────────┘   │
└─────────────────────────────────────────────────────────────────┘
```

---

## C++ Application Best Practices

### 1. Project Structure

```
project/
├── main.cpp              # Entry point
├── validaciones.hpp      # Input validation utilities
├── logo.hpp              # ASCII art and branding
├── [feature].hpp         # Feature-specific modules
└── deploy/
    ├── Dockerfile
    ├── docker-compose.yml
    ├── server/
    │   ├── index.js
    │   ├── package.json
    │   └── package-lock.json
    └── public/
        ├── index.html
        └── favicon.svg
```

### 2. ANSI Color Codes

```cpp
namespace Colors {
    const string RESET   = "\033[0m";
    const string BOLD    = "\033[1m";
    const string DIM     = "\033[2m";
    const string RED     = "\033[31m";
    const string GREEN   = "\033[32m";
    const string YELLOW  = "\033[33m";
    const string BLUE    = "\033[34m";
    const string MAGENTA = "\033[35m";
    const string CYAN    = "\033[36m";
    const string WHITE   = "\033[97m";
}

// Usage
cout << Colors::GREEN << "Success!" << Colors::RESET << endl;
```

### 3. Input Validation Template

```cpp
#include <iostream>
#include <string>
#include <limits>

using namespace std;

// Clear input buffer - CRITICAL for web terminals
inline void limpiarBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Check for EOF (user disconnect)
inline bool verificarEOF() {
    if (cin.eof()) {
        cout << "\n[Session ended]\n";
        return true;
    }
    return false;
}

// Validate integer in range
int validarRango(int min, int max) {
    string input;
    int resultado;

    while (true) {
        if (!(cin >> input)) {
            if (verificarEOF()) return -1;
            limpiarBuffer();
            cout << "Invalid input. Try again: ";
            continue;
        }

        try {
            resultado = stoi(input);
        } catch (...) {
            cout << "Enter a valid number: ";
            continue;
        }

        if (resultado < min || resultado > max) {
            cout << "Enter a number between " << min << " and " << max << ": ";
            continue;
        }

        // IMPORTANT: Clear buffer before returning
        limpiarBuffer();
        return resultado;
    }
}

// Validate non-empty string
string validarString() {
    string texto;

    while (true) {
        getline(cin, texto);

        if (cin.eof()) return "";

        // Check for empty or whitespace-only
        bool soloEspacios = true;
        for (char c : texto) {
            if (!isspace(c)) {
                soloEspacios = false;
                break;
            }
        }

        if (texto.empty() || soloEspacios) {
            cout << "Cannot be empty. Try again: ";
            continue;
        }

        return texto;
    }
}
```

### 4. ASCII Art Box Drawing

```cpp
// Box drawing characters (UTF-8)
// ╔ ═ ╗
// ║   ║
// ╠ ═ ╣
// ╚ ═ ╝

void mostrarMenu() {
    cout << "╔═══════════════════════════════════════╗\n";
    cout << "║           MAIN MENU                   ║\n";
    cout << "╠═══════════════════════════════════════╣\n";
    cout << "║  1. Option One                        ║\n";
    cout << "║  2. Option Two                        ║\n";
    cout << "║  3. Exit                              ║\n";
    cout << "╚═══════════════════════════════════════╝\n";
}

// TIP: Count characters carefully for alignment
// Each line between ║ must have EXACT same width
```

---

## Web Terminal Server

### package.json

```json
{
  "name": "cpp-web-terminal",
  "version": "1.0.0",
  "description": "Secure web terminal for C++ CLI application",
  "main": "index.js",
  "scripts": {
    "start": "node index.js"
  },
  "dependencies": {
    "express": "^4.18.2",
    "express-rate-limit": "^7.1.5",
    "helmet": "^7.1.0",
    "node-pty": "^1.0.0",
    "ws": "^8.16.0"
  }
}
```

### index.js (Complete Server)

```javascript
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
    SESSION_TIMEOUT: parseInt(process.env.SESSION_TIMEOUT) || 600000,
    BINARY_PATH: process.env.BINARY_PATH || './your-binary',
    HEARTBEAT_INTERVAL: 30000,
    MAX_INPUT_LENGTH: 1024,
};

const sessions = new Map();
const app = express();

// Trust proxy (for reverse proxy setups)
app.set('trust proxy', 1);

// Security middleware
app.use(helmet({
    contentSecurityPolicy: {
        directives: {
            defaultSrc: ["'self'"],
            scriptSrc: ["'self'", "'unsafe-inline'", "cdn.jsdelivr.net"],
            styleSrc: ["'self'", "'unsafe-inline'", "cdn.jsdelivr.net", "fonts.googleapis.com"],
            fontSrc: ["'self'", "fonts.gstatic.com", "cdn.jsdelivr.net"],
            connectSrc: ["'self'", "wss:", "ws:"],
        },
    },
    crossOriginEmbedderPolicy: false,
}));

// Rate limiting
app.use(rateLimit({
    windowMs: 60000,
    max: 100,
    message: { error: 'Too many requests' },
}));

// Static files
const publicPath = process.env.NODE_ENV === 'production'
    ? path.join(__dirname, 'public')
    : path.join(__dirname, '../public');
app.use(express.static(publicPath));

// Health check
app.get('/health', (req, res) => {
    res.json({ status: 'healthy', sessions: sessions.size });
});

const server = http.createServer(app);
const wss = new WebSocket.Server({ server, path: '/terminal' });

// Terminal Session Class
class TerminalSession {
    constructor(ws, sessionId) {
        this.ws = ws;
        this.sessionId = sessionId;
        this.pty = null;
        this.lastActivity = Date.now();
    }

    start() {
        try {
            this.pty = pty.spawn(CONFIG.BINARY_PATH, [], {
                name: 'xterm-256color',
                cols: 120,
                rows: 40,
                cwd: path.dirname(CONFIG.BINARY_PATH),
                env: { TERM: 'xterm-256color', LANG: 'en_US.UTF-8' },
            });

            this.pty.onData((data) => {
                this.lastActivity = Date.now();
                if (this.ws.readyState === WebSocket.OPEN) {
                    this.ws.send(JSON.stringify({ type: 'output', data }));
                }
            });

            this.pty.onExit(({ exitCode }) => {
                if (this.ws.readyState === WebSocket.OPEN) {
                    this.ws.send(JSON.stringify({
                        type: 'exit',
                        message: '\r\n[Session ended. Click Restart to begin again.]\r\n'
                    }));
                }
                this.cleanup();
            });

            return true;
        } catch (error) {
            console.error('Failed to start session:', error);
            return false;
        }
    }

    write(data) {
        if (this.pty && data.length <= CONFIG.MAX_INPUT_LENGTH) {
            this.lastActivity = Date.now();
            this.pty.write(data);
        }
    }

    resize(cols, rows) {
        if (this.pty) {
            this.pty.resize(
                Math.min(Math.max(cols, 20), 500),
                Math.min(Math.max(rows, 10), 200)
            );
        }
    }

    cleanup() {
        if (this.pty) {
            try { this.pty.kill(); } catch (e) {}
            this.pty = null;
        }
        sessions.delete(this.sessionId);
    }
}

// WebSocket handler
wss.on('connection', (ws, req) => {
    if (sessions.size >= CONFIG.MAX_SESSIONS) {
        ws.close(4030, 'Server at capacity');
        return;
    }

    const sessionId = crypto.randomBytes(16).toString('hex');
    const session = new TerminalSession(ws, sessionId);
    sessions.set(sessionId, session);

    ws.send(JSON.stringify({ type: 'connected', sessionId }));

    if (!session.start()) {
        ws.close(4031, 'Terminal start failed');
        return;
    }

    ws.on('message', (message) => {
        try {
            const msg = JSON.parse(message.toString());
            switch (msg.type) {
                case 'input':
                    session.write(msg.data);
                    break;
                case 'resize':
                    session.resize(msg.cols, msg.rows);
                    break;
                case 'restart':
                    session.cleanup();
                    sessions.set(sessionId, session);
                    if (session.start()) {
                        ws.send(JSON.stringify({ type: 'restarted' }));
                    }
                    break;
            }
        } catch (e) {}
    });

    ws.on('close', () => session.cleanup());
});

// Session timeout check
setInterval(() => {
    const now = Date.now();
    sessions.forEach((session, id) => {
        if (now - session.lastActivity > CONFIG.SESSION_TIMEOUT) {
            session.ws.close(4032, 'Session timeout');
        }
    });
}, 60000);

server.listen(CONFIG.PORT, '0.0.0.0', () => {
    console.log(`Server running on port ${CONFIG.PORT}`);
});
```

---

## Frontend Terminal UI

### index.html (Minimal Complete Example)

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Web Terminal</title>
    <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/xterm@5.3.0/css/xterm.css">
    <script src="https://cdn.jsdelivr.net/npm/xterm@5.3.0/lib/xterm.min.js"></script>
    <script src="https://cdn.jsdelivr.net/npm/xterm-addon-fit@0.8.0/lib/xterm-addon-fit.min.js"></script>
    <style>
        * { margin: 0; padding: 0; box-sizing: border-box; }
        html, body { height: 100%; background: #1e1e1e; overflow: hidden; }
        .container {
            display: flex;
            flex-direction: column;
            height: 100vh;
            padding: 10px;
        }
        .header {
            display: flex;
            justify-content: space-between;
            align-items: center;
            padding: 10px;
            background: #2d2d2d;
            margin-bottom: 10px;
        }
        .title { color: #fff; font-family: monospace; }
        .btn {
            padding: 8px 16px;
            background: #0066cc;
            color: white;
            border: none;
            cursor: pointer;
            font-family: monospace;
        }
        .btn:hover { background: #0055aa; }
        .btn:disabled { opacity: 0.5; cursor: not-allowed; }
        #terminal { flex: 1; }
        .status { color: #888; font-family: monospace; font-size: 12px; }
    </style>
</head>
<body>
    <div class="container">
        <div class="header">
            <span class="title">Web Terminal</span>
            <div>
                <span class="status" id="status">Connecting...</span>
                <button class="btn" id="restartBtn" disabled>Restart</button>
            </div>
        </div>
        <div id="terminal"></div>
    </div>

    <script>
        const term = new Terminal({
            fontFamily: 'JetBrains Mono, monospace',
            fontSize: 14,
            cursorBlink: true,
            theme: {
                background: '#1e1e1e',
                foreground: '#d4d4d4',
                cursor: '#ffffff',
            }
        });

        const fitAddon = new FitAddon.FitAddon();
        term.loadAddon(fitAddon);
        term.open(document.getElementById('terminal'));
        fitAddon.fit();

        const statusEl = document.getElementById('status');
        const restartBtn = document.getElementById('restartBtn');
        let socket;

        function connect() {
            const protocol = location.protocol === 'https:' ? 'wss:' : 'ws:';
            socket = new WebSocket(`${protocol}//${location.host}/terminal`);

            socket.onopen = () => {
                statusEl.textContent = 'Connected';
                restartBtn.disabled = false;
            };

            socket.onmessage = (e) => {
                const msg = JSON.parse(e.data);
                switch (msg.type) {
                    case 'output':
                        term.write(msg.data);
                        break;
                    case 'restarted':
                        term.reset();
                        break;
                    case 'exit':
                        term.write(msg.message);
                        break;
                }
            };

            socket.onclose = () => {
                statusEl.textContent = 'Disconnected';
                setTimeout(connect, 2000);
            };
        }

        term.onData((data) => {
            if (socket?.readyState === WebSocket.OPEN) {
                socket.send(JSON.stringify({ type: 'input', data }));
            }
        });

        restartBtn.onclick = () => {
            term.reset();
            socket.send(JSON.stringify({ type: 'restart' }));
        };

        window.onresize = () => {
            fitAddon.fit();
            if (socket?.readyState === WebSocket.OPEN) {
                socket.send(JSON.stringify({
                    type: 'resize',
                    cols: term.cols,
                    rows: term.rows
                }));
            }
        };

        connect();
    </script>
</body>
</html>
```

---

## Docker Security Hardening

### Dockerfile

```dockerfile
# Stage 1: Build C++ application
FROM alpine:3.19 AS cpp-builder

RUN apk add --no-cache g++ musl-dev make

WORKDIR /build
COPY *.cpp *.hpp ./

RUN g++ -std=c++11 -static -O2 -Wall -Wextra \
    -fstack-protector-strong -D_FORTIFY_SOURCE=2 \
    main.cpp -o app && strip app && chmod 555 app


# Stage 2: Build Node.js server
FROM node:20-alpine AS node-builder

WORKDIR /build
COPY deploy/server/package*.json ./
RUN npm ci --only=production --ignore-scripts
COPY deploy/server/*.js ./


# Stage 3: Secure runtime
FROM node:20-alpine AS runtime

# Create non-root user
RUN addgroup -g 1001 -S appgroup \
    && adduser -u 1001 -S appuser -G appgroup \
    && mkdir -p /app/public \
    && chown -R appuser:appgroup /app

WORKDIR /app

# Install runtime dependencies for node-pty
RUN apk add --no-cache python3 make g++ libstdc++

# Copy built files
COPY --from=cpp-builder --chown=appuser:appgroup /build/app /app/app
COPY --from=node-builder --chown=appuser:appgroup /build/node_modules /app/node_modules
COPY --from=node-builder --chown=appuser:appgroup /build/*.js /app/
COPY --chown=appuser:appgroup deploy/public/ /app/public/

# Rebuild node-pty and cleanup
COPY deploy/server/package*.json /app/
RUN npm rebuild node-pty && npm cache clean --force \
    && apk del python3 make g++

ENV BINARY_PATH=/app/app NODE_ENV=production PORT=3000

USER appuser

HEALTHCHECK --interval=30s --timeout=10s --retries=3 \
    CMD wget --spider http://localhost:3000/health || exit 1

EXPOSE 3000
CMD ["node", "index.js"]
```

### docker-compose.yml

```yaml
services:
  app:
    build:
      context: ..
      dockerfile: deploy/Dockerfile
    container_name: my-terminal
    restart: unless-stopped

    environment:
      - NODE_ENV=production
      - PORT=3000
      - BINARY_PATH=/app/app
      - MAX_SESSIONS=50
      - SESSION_TIMEOUT=600000

    # Resource limits
    deploy:
      resources:
        limits:
          cpus: '1.0'
          memory: 512M

    # Security
    security_opt:
      - no-new-privileges:true
    cap_drop:
      - ALL
    cap_add:
      - CHOWN
      - SETUID
      - SETGID
    read_only: true
    tmpfs:
      - /tmp:size=64M,mode=1777

    # Health check
    healthcheck:
      test: ["CMD", "wget", "--spider", "http://localhost:3000/health"]
      interval: 30s
      timeout: 10s
      retries: 3

    # Network
    networks:
      - proxy
    expose:
      - "3000"

    # Logging
    logging:
      driver: "json-file"
      options:
        max-size: "10m"
        max-file: "3"

networks:
  proxy:
    external: true
```

---

## Production Deployment

### 1. VPS Setup (SSH)

```bash
# Generate deploy key
ssh-keygen -t ed25519 -C "myapp-deploy" -f ~/.ssh/myapp_deploy -N ""
cat ~/.ssh/myapp_deploy.pub
# Add to GitHub repo → Settings → Deploy keys

# Configure SSH alias
cat >> ~/.ssh/config << 'EOF'
Host github-myapp
    HostName github.com
    User git
    IdentityFile ~/.ssh/myapp_deploy
    IdentitiesOnly yes
EOF
```

### 2. Clone and Deploy

```bash
mkdir -p ~/docker/myapp && cd ~/docker/myapp
git clone git@github-myapp:user/repo.git .
git checkout deploy

docker network create proxy 2>/dev/null || true
cd deploy && docker-compose up -d --build
```

### 3. Nginx Proxy Manager Setup

| Setting | Value |
|---------|-------|
| Domain | `app.yourdomain.com` |
| Scheme | `http` |
| Forward Hostname | `container-name` |
| Forward Port | `3000` |
| Websocket Support | ON |
| SSL | Let's Encrypt |

### 4. Update Commands

```bash
cd ~/docker/myapp
git pull
cd deploy && docker-compose up -d --build
```

---

## Quick Reference

### Essential C++ Input Patterns

```cpp
// ALWAYS clear buffer after reading numbers before getline()
cin >> number;
limpiarBuffer();  // Clear the newline
getline(cin, text);

// ALWAYS check for EOF in loops
if (cin.eof()) return;

// ALWAYS validate ranges
if (input < min || input > max) { /* error */ }
```

### Docker Commands

```bash
docker-compose up -d --build    # Build and start
docker-compose logs -f          # View logs
docker-compose down             # Stop
docker exec -it container sh    # Shell into container
docker system prune -a          # Clean everything
```

### Troubleshooting

| Issue | Solution |
|-------|----------|
| "Cannot GET /" | Check static files path in server |
| "X-Forwarded-For" error | Add `app.set('trust proxy', 1)` |
| Input buffer issues | Call `limpiarBuffer()` after `cin >>` |
| WebSocket not connecting | Enable WebSocket in proxy |
| Container keeps restarting | Check `docker-compose logs` |

---

## Security Checklist

- [ ] Non-root user in container
- [ ] Read-only filesystem
- [ ] Resource limits (CPU, memory)
- [ ] No shell escape (direct binary execution)
- [ ] Rate limiting enabled
- [ ] Session timeouts configured
- [ ] Helmet security headers
- [ ] Input length limits
- [ ] Health checks enabled
- [ ] Logging configured

---

*Generated for Everywhere Airlines project - PED 02/2020 - UCA El Salvador*
