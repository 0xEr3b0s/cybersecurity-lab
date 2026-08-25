# ft_otp — TOTP Authenticator

A C implementation of Time-based One-Time Password (TOTP) following RFC 4226/6238. Generates 6-digit codes matching Google Authenticator, with AES-256-CBC encrypted key storage.

---

## Features

- **TOTP generation**: 30-second rotating 6-digit codes
- **Encrypted storage**: Master key never stored in plaintext
- **Standards compliant**: Matches `oathtool` reference implementation
- **AES-256-CBC encryption**: OpenSSL-based with random IV per encrypt

---

## Usage

```bash
# Generate encrypted key file
./ft_otp -g key.hex    # Reads hex key, creates ft_otp.key

# Generate OTP code
./ft_otp -k ft_otp.key # Prints 6-digit code (changes every 30s)
```

**Key requirements:**
- Minimum 64 hexadecimal characters (32 bytes)
- Even length
- Valid hex only (0-9, a-f, A-F)

---

## Build

```bash
make          # Build executable
make debug    # With AddressSanitizer + UBSan
make clean    # Remove objects
make fclean   # Full rebuild
```

**Dependencies:** gcc, make, OpenSSL dev headers (`libssl-dev`)

---

## How It Works

1. **-g (store)**: Reads hex key → AES-256-CBC encrypt → saves to `ft_otp.key`
2. **-k (generate)**: Decrypts key → decodes hex → HMAC-SHA1 with time counter → dynamic truncation → 6 digits

**File format:** `[IV: 16 bytes][encrypted data]`

---

## Testing

```bash
# Generate test key
echo "3132333435363738393031323334353637383930313233343536373839303132" > key.hex

# Store and generate
./ft_otp -g key.hex
./ft_otp -k ft_otp.key     # Should match oathtool output

# Verify with reference tool
oathtool --totp "31323334..."  # Same code as ft_otp
```

---

## Files

```
ft_otp/
├── Makefile
├── include/
│   └── ft_otp.h      # Structs & prototypes
└── src/
    ├── main.c        # Entry point (-g/-k dispatch)
    ├── parsing.c     # Arg parsing + key validation
    ├── storage.c     # AES encrypt/decrypt
    ├── totp.c        # TOTP algorithm (HMAC + truncation)
    └── utils.c       # Error handling
```

---

## Security Note

The encryption key is embedded in the binary for this exercise. Production systems should use PBKDF2 to derive keys from user passwords instead.
