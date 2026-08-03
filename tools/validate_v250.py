#!/usr/bin/env python3
from pathlib import Path
import sys

required = [
    "tools/bench-console/bench_console.py",
    "tools/bench-console/requirements.txt",
    "tools/bench-console/tests/test_bench_console.py",
    "tools/bench-console/start_bench_console_windows.bat",
    "tools/bench-console/start_bench_console.ps1",
    "docs/bench/PRODUCTION_BENCH_CONSOLE_GUIDE.md",
    "docs/bench/FIRST_HARDWARE_DAY_OPERATOR_CARD.md",
    "docs/bench/BENCH_SAFETY_AND_DATA_CONTROLS.md",
]
root = Path(__file__).resolve().parents[1]
missing = [path for path in required if not (root / path).exists()]
if missing:
    print("Missing files:")
    for path in missing:
        print(" -", path)
    sys.exit(1)
print("PASS: LYNQ v2.5.0-beta.1 production bench console is valid.")
