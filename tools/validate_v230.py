#!/usr/bin/env python3
from pathlib import Path
import sys

required = [
 "hardware/first-article/FIRST_ARTICLE_RECORD_TEMPLATE.json",
 "tools/hardware/validate_first_article.py",
 "docs/hardware/HARDWARE_ARRIVAL_AND_RECEIVING_GUIDE.md",
 "docs/hardware/FIRST_POWER_AND_FACTORY_BACKUP.md",
 "docs/hardware/BOARD_PROFILE_LOCK_PROCEDURE.md",
 "docs/hardware/FIRST_ARTICLE_COMMISSIONING_PLAN.md",
 "docs/hardware/MECHANICAL_FIT_AND_MEASUREMENT_RECORD.md",
 "docs/testing/FIRST_ARTICLE_ACCEPTANCE_CHECKLIST.md",
 "docs/quality/DEFECT_AND_DEVIATION_TEMPLATE.md"
]
root = Path(__file__).resolve().parents[1]
missing = [p for p in required if not (root/p).exists()]
if missing:
    print("Missing files:")
    for p in missing: print(" -", p)
    sys.exit(1)
print("PASS: LYNQ v2.3.0-beta.1 first-article package is valid.")
