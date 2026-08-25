# rev — Reverse Engineering Challenges

Buffer overflow protection exercises teaching stack safety, input validation, and secure coding practices.

---

## Challenges

### easy (source.c)
Simple string validation with buffer overflow prevention.

**Goal**: Find the correct key (`__stack_check`) without overflowing the 64-byte buffer.

**Security lesson**: Using `scanf("%63s", buff)` limits input to prevent overflow on a 64-byte array.

### medium (source.c)
Complex validation requiring careful parsing of hex-encoded data.

**Goal**: Input starts with `00`, followed by hex triplets that decode to spell "delabere".

**Security lessons**:
- Buffer size limits (`%23s`)
- Array bounds checking
- Null termination guarantees
- Loop exit conditions

---

## Quick Test

```bash
# Easy challenge
cd rev/easy
gcc source.c -o easy && ./easy
# Enter: __stack_check

# Medium challenge  
cd ../medium
gcc source.c -o medium && ./medium
# Enter: 00... (hex encoding of "delabere")
```

---

## Files

```
rev/
├── easy/
│   └── source.c    # Simple buffer overflow demo
└── medium/
    └── source.c    # Complex validation with bounds checking
```

---

## Security Features Demonstrated

| File | Protection | Technique |
|------|------------|-----------|
| easy/source.c | Buffer overflow | Width-limited scanf (`%63s`) |
| medium/source.c | Multiple protections | Bounds checks, array limits, null termination |

Both programs gracefully reject malformed input without crashing.
