# arachnida — Web Scraping & Metadata Analysis

Python-based cybersecurity exercises covering HTTP crawling and image metadata extraction.

---

## Projects

### ex00: spider.py
Recursive web crawler that downloads images from websites while respecting domain boundaries.

**Features:**
- Extracts all `<img>` tags from HTML pages
- Recursive mode with configurable depth limit
- Stays within the same domain
- Deduplicates URLs and handles fragments
- Atomic file writes prevent corruption
- Filters by image extension AND Content-Type header

**Usage:**
```bash
python3 ex00/spider.py [-rlp] URL
# -r: recursive mode
# -l N: max depth (default 5)
# -p PATH: output directory (default ./data/)
```

### ex01: scorpion.py
EXIF metadata reader revealing hidden information in images.

**Features:**
- Reads filesystem metadata (size, timestamps)
- Extracts and displays EXIF data (camera, GPS, dates)
- Handles multiple image files
- Clean box-formatted output

**Usage:**
```bash
python3 ex01/scorpion.py IMAGE1.jpg IMAGE2.png ...
```

---

## Setup

```bash
cd arachnida
python3 -m venv .venv
source .venv/bin/activate
pip install requests beautifulsoup4 Pillow
```

---

## Security Note

EXIF data can reveal sensitive information:
- Exact GPS coordinates
- Camera model and settings
- Creation/modification dates
- Software used for editing

This makes metadata analysis crucial for OSINT (Open Source Intelligence) operations.

---

## Files

```
arachnida/
├── ex00/
│   └── spider.py      # Web crawler
├── ex01/
│   └── scorpion.py    # EXIF reader
├── .gitignore
└── README.md          # This file
```
