# Cybersecurity Piscine

> A comprehensive collection of cybersecurity projects covering network attacks, cryptography, ransomware simulation, SQL injection scanning, and web forensics.

---

## 📚 Projects Overview

This repository contains **7** cybersecurity exercises:

| Project | Language | Description | Status |
|---------|----------|-------------|--------|
| **[arachnida](./arachnida/)** | Python | Web scraper & EXIF metadata analyzer | ✅ Complete |
| **[ft_otp](./ft_otp/)** | C | TOTP authenticator (Google Authenticator clone) | ✅ Complete |
| **[stockholm](./stockholm/)** | C++ | WannCry-inspired ransomware simulation | ✅ Complete |
| **[inquisitor](./inquisitor/)** | C | ARP poisoning MITM attack tool | ✅ Complete |
| **[rev](./rev/)** | C | Reverse engineering buffer overflow challenges | ✅ Complete |
| **[ft_onion](./ft_onion/)** | Docker/Tor | Hidden .onion service (SSH + Nginx) | ✅ Complete |
| **[vaccine](./vaccine/)** | Rust | SQL injection scanner & database dumper | 🟡 Work in progress |

---

## 🛠️ Quick Start

Each project is self-contained with its own build system and documentation. Here's a quick test command for each:

```bash
# arachnida - Download images from a website
cd arachnida && python3 ex00/spider.py https://example.com

# ft_otp - Generate time-based OTP
cd ft_otp && make && echo "0123456789abcdef..." > key.hex && ./ft_otp -g key.hex && ./ft_otp -k ft_otp.key

# stockholm - Encrypt/decrypt files (educational)
cd stockholm && make && mkdir -p ~/infection && cp test.py ~/infection/ && ./stockholm mykey123

# inquisitor - ARP poisoning lab
cd inquisitor && make up && make run

# rev - Solve buffer overflow challenges
cd rev/easy && gcc source.c -o challenge && ./challenge

# ft_onion - Start Tor hidden service
cd ft_onion && docker compose up --build

# vaccine - SQL injection scanner
cd vaccine && make && ./vaccine "http://localhost/test.php?id=1"
```

---

## 📖 Project Summaries

### arachnida — Web Scraping & Metadata Analysis
- **ex00 (spider)**: Recursive web crawler that downloads images while staying on the same domain
- **ex01 (scorpion)**: EXIF metadata reader revealing hidden camera/GPS data
- **Libraries**: requests, BeautifulSoup4, Pillow

### ft_otp — Two-Factor Authentication Implementation
- Implements RFC 4226 (HOTP) and RFC 6238 (TOTP) from scratch
- AES-256-CBC encryption for secure key storage
- Generates 6-digit codes matching Google Authenticator

### stockholm — Ransomware Simulation
- WannCry-inspired file encryption using AES-256-CBC
- Targets specific file extensions in `~/infection`
- Fully reversible with correct key
- Atomic file operations prevent corruption

### inquisitor — ARP Poisoning MITM Attack
- Man-in-the-middle attack on local network
- Sniffs FTP traffic and extracts filenames
- Restores ARP tables gracefully on exit
- Docker-based lab environment for safe testing

### rev — Reverse Engineering Challenges
- **easy**: Simple buffer overflow protection demo
- **medium**: Complex key validation with bounds checking
- Teaches stack safety and input validation

### ft_onion — Tor Hidden Service
- Nginx web server only accessible via .onion address
- SSH administration over Tor (port 4242)
- Zero exposed ports on host network
- Docker containerized environment

### vaccine — SQL Injection Scanner (Rust)
- Automated SQL vulnerability detection
- Database fingerprinting (MySQL, SQLite)
- Schema extraction and data dumping
- **Status**: Phased development in progress

---

## ⚠️ Legal Disclaimer

**EDUCATIONAL PURPOSES ONLY**

These tools are designed for learning cybersecurity concepts in controlled environments:
- ✅ Use on your own networks and systems
- ✅ Test against authorized vulnerability labs (DVWA, bWAPP, local Docker)
- ❌ Never use against unauthorized targets
- ❌ Do not deploy in production environments

All projects follow responsible disclosure and ethical hacking principles.

---

## 🏗️ Repository Structure

```
cybersecurity-piscine/
├── arachnida/       # Python web scraping exercises
├── ft_onion/        # Tor hidden service setup
├── ft_otp/          # TOTP authenticator in C
├── inquisitor/      # ARP poisoning MITM tool
├── rev/             # Reverse engineering challenges
├── stockholm/       # Ransomware simulation
├── vaccine/         # SQL injection scanner (Rust)
└── README.md        # This file
```

---

## 📝 Notes

- Each subfolder contains its own detailed README with setup instructions
- Projects follow strict coding standards and restrictions
- Bug fixes applied: ARP frame correctness, buffer overflow protections, encryption security
- All projects compile and run without warnings

---


