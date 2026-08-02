#!/usr/bin/env python3
import json,re,sys
from pathlib import Path
p=Path(sys.argv[1]); d=json.loads(p.read_text())
errors=[]
if not re.match(r'^LYNQ-(HUB|NODE)-[A-Z0-9]+-\d{6}$',d.get('serialNumber','')): errors.append('invalid serial')
required={'VISUAL','POWER','USB','WIFI','BLE','PAIRING','OTA','BACKUP_RESTORE'}
if 'NODE' in d.get('serialNumber',''): required|={'RF433_RX','RF433_TX','IR_RX','IR_TX'}
ids={x.get('testId') for x in d.get('tests',[])}
if required-ids: errors.append('missing tests: '+','.join(sorted(required-ids)))
if not d.get('approvedBy'): errors.append('missing quality approver')
if errors:
 print('FAIL'); [print(' -',e) for e in errors]; sys.exit(1)
print('PASS: DHR structure is complete')
