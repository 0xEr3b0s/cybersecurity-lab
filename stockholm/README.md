# stockholm — Ransomware Simulation

A WannCry-inspired ransomware simulation for educational purposes. Encrypts files in `~/infection` using AES-256-CBC, fully reversible with the correct key.

---

## Features

- **AES-256-CBC encryption**: OpenSSL-based with random IV per file
- **WannCry extensions**: Targets same file types as original ransomware
- **Atomic operations**: Temp files + rename prevent corruption
- **Idempotent**: Already encrypted files (`.ft`) are skipped
- **Full decryption**: `--reverse` mode restores all files

---

## Usage

```bash
# Encrypt files in ~/infection
./stockholm mykey123

# Decrypt files  
./stockholm --reverse mykey123

# Silent mode (no progress output)
./stockholm --silent mykey123

# Help and version
./stockholm --help
./stockholm --version
```

**Key requirements:** Minimum 16 characters.

---

## Build

```bash
cd stockholm
mkdir -p build && cd build
cmake ..
make
```

**Dependencies:** C++17 compiler, OpenSSL dev libraries

---

## How It Works

### Encryption Mode
1. Recursively scans `~/infection` for target extensions
2. Skips already `.ft` files (idempotency)
3. Encrypts each file with random IV + AES-256-CBC
4. Writes to `.tmp`, renames to `.ft`, removes original

### Decryption Mode  
1. Finds all `.ft` files in `~/infection`
2. Reads IV from file header (first 16 bytes)
3. Decrypts with same key derivation
4. Restores original filename, removes `.ft`

---

## Security Features

- **Random IV**: Each encryption produces different ciphertext
- **Key derivation**: SHA-256 hash of embedded password (educational limitation)
- **Atomic writes**: No partial files on interruption
- **Memory clearing**: `memset()` zeroizes keys after use

**Note:** The embedded key is a known weakness. Production systems use PBKDF2 with user passwords.

---

## Test Setup

```bash
# Create test directory
mkdir -p ~/infection

# Add test files
echo "secret data" > ~/infection/test.txt
cp stockholm/test.py ~/infection/

# Encrypt
./stockholm mykey123
ls ~/infection/  # Shows .ft files only

# Decrypt
./stockholm --reverse mykey123
ls ~/infection/  # Original files restored
```

---

## Files

```
stockholm/
├── include/
│   ├── Cipher.hpp        # Encryption class
│   ├── Discovering.hpp   # File scanner
│   ├── Parser.hpp        # Argument parser
│   ├── Utils.hpp         # Common utilities
│   └── extensions.hpp    # WannCry file list
├── src/
│   ├── main.cpp          # Entry point
│   ├── Cipher.cpp        # AES encrypt/decrypt impl
│   ├── Discovering.cpp   # Recursive file scanning
│   ├── Parser.cpp        # CLI argument handling
│   └── Utils.cpp         # Helper functions
├── test.py               # Test setup script
└── README.md            # This file
```

---

## ⚠️ Legal Disclaimer

**STRICTLY EDUCATIONAL**. Use only in:
- ✅ Your own controlled environment
- ✅ Authorized training scenarios
- ❌ Never on production systems or other people's files

This is a simulation for learning cryptographic concepts and malware behavior analysis.

---


