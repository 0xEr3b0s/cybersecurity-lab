# ft_onion — Tor Hidden Service

A Nginx web server and SSH daemon accessible **only** through Tor as a v3 .onion service. Zero exposed ports on the host network.

---

## Architecture

Three daemons run inside a single Docker container:

1. **Nginx**: Serves static HTML on `127.0.0.1:80`
2. **Tor**: Creates v3 hidden service, forwards .onion traffic to localhost
3. **OpenSSH**: Listens on port `4242` for admin access

**Key principle**: Nothing is exposed to the host. Tor makes outbound connections only — no firewall rules needed.

---

## Quick Start

```bash
# Build and start
docker compose up --build

# Get your .onion address
docker compose exec onion cat /var/lib/tor/hidden_service/hostname
```

Visit the address in Tor Browser, or use:
```bash
# Test via CLI
torsocks curl http://your-address.onion

# SSH access over Tor
torsocks ssh -p 4242 user@your-address.onion
```

---

## Files

```
ft_onion/
├── Dockerfile              # Container setup
├── docker-compose.yml      # Service orchestration
├── srcs/
│   ├── index.html          # Static page content
│   ├── nginx.conf          # Web server config (localhost only)
│   ├── sshd_config         # SSH hardened config (port 4242)
│   └── torrc               # Hidden service definition
├── tools/
│   └── entrypoint.sh       # Startup script
└── README.md
```

---

## Security Features

- No ports published to host network
- SSH key-only authentication (passwords disabled)
- Root login disabled
- Non-standard SSH port (4242)
- Onion private keys excluded from git

---

## Cleanup

```bash
docker compose down        # Stop containers
docker compose down -v     # Remove volumes (regenerates onion keys)
```
