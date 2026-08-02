from pathlib import Path
import sys
required=[
 'docs/testing/FIRST_REAL_DEVICE_DEMO.md',
 'docs/testing/FIRST_REAL_DEVICE_ACCEPTANCE_CHECKLIST.md',
 'sdk/include/lynq/control/EndToEndControlSession.h',
 'node/firmware/components/control_endpoint/include/ControlEndpoint.h'
]
root=Path(sys.argv[1] if len(sys.argv)>1 else '.')
missing=[p for p in required if not (root/p).exists()]
if missing:
 print('Missing:',*missing,sep='\n- '); raise SystemExit(1)
print('v1.8.0 demo package complete')
