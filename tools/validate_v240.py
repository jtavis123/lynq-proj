#!/usr/bin/env python3
from pathlib import Path
import sys

required = [
    "tools/commissioning/commission.py",
    "tools/commissioning/generate_report.py",
    "tools/commissioning/package_evidence.py",
    "tools/commissioning/tests/test_commissioning.py",
    "docs/commissioning/GUIDED_COMMISSIONING_USER_GUIDE.md",
    "docs/commissioning/EVIDENCE_CAPTURE_STANDARD.md",
    "docs/commissioning/BENCH_DAY_QUICK_SEQUENCE.md",
    "docs/commissioning/COMMISSIONING_EXIT_CRITERIA.md",
]
root = Path(__file__).resolve().parents[1]
missing = [p for p in required if not (root / p).exists()]
if missing:
    print("Missing required files:")
    for p in missing:
        print(" -", p)
    sys.exit(1)
print("PASS: LYNQ v2.4.0-beta.1 guided commissioning package is valid.")
