# inquisitor — ARP Poisoning MITM Tool

A network attack tool that performs man-in-the-middle attacks via ARP cache poisoning, sniffing FTP traffic to extract filenames in real-time.

---

## Overview

`inquisitor` intercepts traffic between two hosts on a LAN by poisoning their ARP caches. While the attack runs, it monitors the FTP control channel and displays file transfer names. On exit (Ctrl+C), it automatically restores the victims' ARP tables.

**Core components:**
- Argument parsing & validation (IPv4, MAC addresses)
- Network interface discovery
- Full-duplex ARP poisoning (bidirectional)
- ARP table restoration on cleanup
- libpcap-based packet sniffing
- FTP protocol filtering (port 21)

---

## Usage

```bash
./inquisitor <IP-src> <MAC-src> <IP-target> <MAC-target> [-v]
```

| Argument | Description |
|----------|-------------|
| `IP-src` | First victim IP (e.g., FTP server) |
| `MAC-src` | First victim MAC address |
| `IP-target` | Second victim IP (e.g., FTP client) |
| `MAC-target` | Second victim MAC address |
| `-v` | Verbose mode (shows all FTP traffic) |

**Requires root privileges** for raw socket access (`AF_PACKET`).

---

## Docker Lab (Recommended)

Safe, isolated testing environment with pre-configured clients and servers:

```bash
# Start lab + compile inside attacker container
make up

# Terminal 1: Launch attack
make run

# Terminal 2: Trigger FTP transfers
make test

# Stop lab
make down
```

**Lab topology:**
- Server (192.168.0.2): vsftpd FTP server with test files
- Client (192.168.0.3): FTP client for testing
- Attacker (192.168.0.4): Runs `inquisitor`

---

## How It Works

### 1. ARP Poisoning Loop
Sends forged ARP replies every second:
```
To Client: "SERVER_IP is at ATTACKER_MAC"
To Server: "CLIENT_IP is at ATTACKER_MAC"
```
Both victims route traffic through the attacker.

### 2. FTP Sniffing
Captures packets on port 21, parses FTP commands:
- Shows `STOR filename` (uploads)
- Shows `RETR filename` (downloads)
- Verbose mode shows `USER`, `PASS`, etc.

### 3. Cleanup
On SIGINT (Ctrl+C), sends legitimate ARP replies to restore correct mappings before exiting.

---

## Makefile Targets

```bash
make          # Local build (needs libpcap-dev)
make debug    # Build with sanitizers
make up       # Start Docker lab
make run      # Launch attack in lab
make test     # FTP upload/download test
make down     # Stop lab
make logs     # View container logs
```

---

## Project Structure

```
inquisitor/
├── Makefile              # Build + Docker orchestration
├── docker-compose.yml    # 3-container lab setup
├── attacker/
│   └── Dockerfile        # Attacker environment
├── data/                 # FTP server files
├── libft/                # extended C library (string, memory, printf)
├── include/
│   ├── inquisitor.h      # Config struct
│   ├── parsing.h         # Argument validation
│   ├── poisoning.h       # ARP frame building
│   ├── sniffing.h        # PCAP interface
│   ├── signals.h         # Signal handling
│   └── utils.h           # Error/cleanup helpers
├── src/
│   ├── main.c            # Main: parse → poison loop → restore
│   ├── parsing.c         # Args, IPv4/MAC validation, interface discovery
│   ├── poisoning.c       # ARP frames, raw injection, restoration
│   ├── signals.c         # SIGINT handler
│   ├── sniffing.c        # FTP packet capture
│   └── utils.c           # Error handling, resource cleanup
└── tests/                # Python test suite for validation
```

---

## Bug Fixes Applied

1. **send_arp_frame()**: Fixed destination MAC to use frame's `eth.dst_mac` instead of hardcoded config value (enables bidirectional poisoning)
2. **restore_arp()**: Corrected ARP sender MAC assignments to properly restore victim IP→MAC mappings
3. **Missing include**: Added `<string.h>` for `memcpy()`

---

## Files Submitted

| File | Purpose |
|------|---------|
| `main.c` | Entry point, main poisoning loop |
| `parsing.c` | Argument parsing and validation |
| `poisoning.c` | ARP frame construction and injection |
| `sniffing.c` | FTP traffic monitoring |
| `signals.c` | Graceful shutdown handler |
| `utils.c` | Error handling utilities |

Supporting files (libft, Docker, tests) included for reproducibility.

---

## ⚠️ Legal Disclaimer

**EDUCATIONAL USE ONLY**. Test exclusively on:
- ✅ Your own network
- ✅ Authorized labs (this Docker environment)
- ❌ Never against unauthorized networks

---


