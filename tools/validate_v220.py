#!/usr/bin/env python3
from pathlib import Path
import sys
root=Path(__file__).resolve().parents[1]
req=['CHANGELOG_V2.2.0-beta.1.md','docs/integration/LYNQ_SYSTEM_INTEGRATION_GUIDE.md','docs/regulatory/REGULATORY_CERTIFICATION_MATRIX.md','docs/regulatory/CERTIFICATION_EVIDENCE_REGISTER.md','docs/regulatory/LABEL_AND_MARKING_CONTROL.md','docs/regulatory/PRECOMPLIANCE_TEST_PLAN.md','manufacturing/templates/FACTORY_TRAVELER.md','manufacturing/templates/DHR_TEMPLATE.json','tools/manufacturing/validate_dhr.py']
missing=[x for x in req if not (root/x).exists()]
if missing: print('FAIL',missing); sys.exit(1)
print('PASS: LYNQ v2.2.0-beta.1 package is valid')
