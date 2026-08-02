from pathlib import Path
required=[
 'sdk/include/lynq/reliability/CommandReliability.h',
 'sdk/include/lynq/reliability/SystemHealthScore.h',
 'sdk/src/CommandReliability.cpp','sdk/src/SystemHealthScore.cpp',
 'sdk/tests/reliability_tests.cpp','docs/testing/PRE_BETA_REGRESSION_CHECKLIST.md'
]
root=Path(__file__).resolve().parents[1]
missing=[p for p in required if not (root/p).exists()]
if missing: raise SystemExit('Missing: '+', '.join(missing))
print('LYNQ v1.9.0 beta package validation passed.')
