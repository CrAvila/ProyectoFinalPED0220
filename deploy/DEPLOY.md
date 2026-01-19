# Everywhere Airlines - Deployment Guide

## Quick Deploy to ped.cravila.me

### Prerequisites
- Docker & Docker Compose installed
- Nginx Proxy Manager with external network `proxy`
- Domain `ped.cravila.me` pointing to your server

### 1. Deploy the Container

```bash
cd /home/cravila/WebstormProjects/ProyectoFinalPED0220/deploy

# Build and start
docker compose up -d --build

# Check logs
docker compose logs -f
```

### 2. Configure Nginx Proxy Manager

1. Open Nginx Proxy Manager dashboard
2. Add new **Proxy Host**:

| Setting | Value |
|---------|-------|
| Domain Names | `ped.cravila.me` |
| Scheme | `http` |
| Forward Hostname/IP | `airlines-terminal` |
| Forward Port | `3000` |
| Websockets Support | **ON** |
| Block Common Exploits | **ON** |

3. **SSL Tab**:
   - Request a new SSL Certificate
   - Force SSL: **ON**
   - HTTP/2 Support: **ON**

4. **Advanced Tab** (optional security headers):
```nginx
# Security Headers
add_header X-Content-Type-Options "nosniff" always;
add_header X-Frame-Options "DENY" always;
add_header X-XSS-Protection "1; mode=block" always;
add_header Referrer-Policy "strict-origin-when-cross-origin" always;
add_header Permissions-Policy "geolocation=(), microphone=(), camera=()" always;

# WebSocket Timeouts
proxy_read_timeout 3600s;
proxy_send_timeout 3600s;
```

### 3. Verify Deployment

```bash
# Check container health
docker compose ps

# Check application health
curl https://ped.cravila.me/health
```

Expected response:
```json
{"status":"healthy","sessions":0,"maxSessions":50,"uptime":...}
```

---

## Security Features

### Container Security
- **Non-root execution**: Runs as `appuser:appgroup` (UID 1001)
- **Read-only filesystem**: Only `/tmp` is writable
- **Dropped capabilities**: All capabilities dropped except required ones
- **No privilege escalation**: `no-new-privileges:true`
- **Resource limits**: CPU and memory limits enforced

### Application Security
- **No shell access**: Direct binary execution only (no shell escape)
- **Input sanitization**: All terminal input is sanitized
- **Rate limiting**: Connection rate limits per IP
- **Session limits**: Maximum 50 concurrent sessions
- **Session timeout**: Auto-disconnect after 10 minutes of inactivity
- **WebSocket validation**: All messages are validated

### Network Security
- **HTTPS only**: SSL/TLS enforced via Nginx Proxy Manager
- **Security headers**: Full set of HTTP security headers
- **WebSocket secure**: WSS protocol for terminal communication
- **CORS protection**: Restricted to allowed origins

---

## Management Commands

```bash
# View logs
docker compose logs -f

# Restart container
docker compose restart

# Stop and remove
docker compose down

# Rebuild and deploy
docker compose up -d --build --force-recreate

# Check resource usage
docker stats airlines-terminal

# Execute command in container (debugging)
docker compose exec airlines-terminal /bin/sh
```

---

## Environment Variables

| Variable | Default | Description |
|----------|---------|-------------|
| `PORT` | `3000` | Server port |
| `MAX_SESSIONS` | `50` | Maximum concurrent sessions |
| `SESSION_TIMEOUT` | `600000` | Session timeout in ms (10 min) |
| `ALLOWED_ORIGINS` | `*` | Comma-separated allowed CORS origins |
| `BINARY_PATH` | `/app/airlines` | Path to C++ binary |

---

## Troubleshooting

### Container won't start
```bash
docker compose logs airlines-terminal
```

### Connection refused
- Verify container is running: `docker compose ps`
- Check Nginx Proxy Manager settings
- Verify WebSocket support is enabled

### Terminal not responding
- Check session limit: `curl http://localhost:3000/health`
- Restart container: `docker compose restart`

### High memory usage
- Adjust `deploy.resources.limits.memory` in docker-compose.yml
- Reduce `MAX_SESSIONS` environment variable

---

## Architecture

```
[Client Browser]
       |
       | HTTPS + WSS
       v
[Nginx Proxy Manager]
       |
       | HTTP + WS (internal)
       v
[airlines-terminal container]
       |
       +-- Node.js Server (Express + WebSocket)
       |       |
       |       +-- Session Management
       |       +-- Rate Limiting
       |       +-- Input Sanitization
       |
       +-- C++ Binary (airlines)
               |
               +-- Airline Ticketing System
               +-- Graph-based Route Finding
               +-- Passenger Management
```

---

## Performance Tuning

For high-traffic deployments:

```yaml
# docker-compose.override.yml
services:
  airlines-terminal:
    environment:
      - MAX_SESSIONS=100
    deploy:
      resources:
        limits:
          cpus: '2.0'
          memory: 1G
```

---

## License

This project is part of the PED 02-2020 Final Project.

Created by cravila | [cravila.me](https://cravila.me)
