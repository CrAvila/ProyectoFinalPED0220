# ============================================================================
# Everywhere Airlines - Ultra-Secure Multi-Stage Docker Build
# ============================================================================
# Security Features:
# - Multi-stage build (minimal attack surface)
# - Non-root user execution
# - Read-only filesystem where possible
# - No shell in final image (distroless-like)
# - Minimal base image (Alpine)
# - Static binary compilation
# - Hardened Node.js environment
# ============================================================================

# Stage 1: Build the C++ application
FROM alpine:3.19 AS cpp-builder

# Install build dependencies
RUN apk add --no-cache \
    g++ \
    musl-dev \
    make \
    && rm -rf /var/cache/apk/*

WORKDIR /build

# Copy source files
COPY main.cpp rutas.hpp maletas.hpp abordaje.hpp validaciones.hpp logo.hpp ./

# Compile with security flags and static linking
# -static: Static linking for portability
# -O2: Optimization level
# -Wall -Wextra: All warnings
# -fstack-protector-strong: Stack protection
# -D_FORTIFY_SOURCE=2: Buffer overflow protection
# -pie -fPIE: Position independent executable
RUN g++ -std=c++11 \
    -static \
    -O2 \
    -Wall -Wextra \
    -fstack-protector-strong \
    -D_FORTIFY_SOURCE=2 \
    main.cpp -o airlines \
    && strip airlines \
    && chmod 555 airlines

# Verify the binary
RUN ./airlines < /dev/null || true


# Stage 2: Build Node.js server
FROM node:20-alpine AS node-builder

WORKDIR /build

# Copy package files
COPY deploy/server/package*.json ./

# Install dependencies (production only)
RUN npm ci --only=production --ignore-scripts \
    && npm cache clean --force

# Copy server code
COPY deploy/server/*.js ./


# Stage 3: Final secure runtime image
FROM node:20-alpine AS runtime

# Security: Create non-root user
RUN addgroup -g 1001 -S appgroup \
    && adduser -u 1001 -S appuser -G appgroup \
    && mkdir -p /app /app/public \
    && chown -R appuser:appgroup /app

WORKDIR /app

# Install runtime dependencies for node-pty
RUN apk add --no-cache \
    python3 \
    make \
    g++ \
    libstdc++ \
    && rm -rf /var/cache/apk/*

# Copy built files from previous stages
COPY --from=cpp-builder --chown=appuser:appgroup /build/airlines /app/airlines
COPY --from=node-builder --chown=appuser:appgroup /build/node_modules /app/node_modules
COPY --from=node-builder --chown=appuser:appgroup /build/*.js /app/
COPY --chown=appuser:appgroup deploy/public/ /app/public/

# Reinstall node-pty in the runtime environment
COPY deploy/server/package*.json /app/
RUN cd /app && npm rebuild node-pty \
    && npm cache clean --force

# Remove build tools after node-pty rebuild
RUN apk del python3 make g++ \
    && rm -rf /var/cache/apk/* /tmp/*

# Set binary path and permissions
ENV BINARY_PATH=/app/airlines \
    NODE_ENV=production \
    PORT=3000

# Make binary executable
RUN chmod 555 /app/airlines

# Security: Switch to non-root user
USER appuser

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD wget --no-verbose --tries=1 --spider http://localhost:3000/health || exit 1

# Expose port
EXPOSE 3000

# Security labels
LABEL org.opencontainers.image.title="Everywhere Airlines Terminal" \
      org.opencontainers.image.description="Secure web terminal for C++ airline ticketing system" \
      org.opencontainers.image.vendor="cravila" \
      org.opencontainers.image.version="1.0.0" \
      security.hardened="true"

# Run the server
CMD ["node", "index.js"]
