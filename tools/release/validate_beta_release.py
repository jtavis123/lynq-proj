#!/usr/bin/env python3
import json
import sys
from pathlib import Path

repo = Path(sys.argv[1] if len(sys.argv) > 1 else ".").resolve()
manifest_path = repo / "release" / "RELEASE_MANIFEST.json"
if not manifest_path.exists():
    print("FAIL: release/RELEASE_MANIFEST.json is missing")
    sys.exit(1)
manifest = json.loads(manifest_path.read_text(encoding="utf-8"))
errors = []
for name in manifest["requiredChangelogs"]:
    if not (repo / name).exists():
        errors.append(f"missing changelog: {name}")
for area in manifest["requiredAreas"]:
    if not (repo / area).exists():
        errors.append(f"missing repository area: {area}")
version = repo / "config" / "LYNQ_VERSION.json"
if not version.exists():
    errors.append("missing config/LYNQ_VERSION.json")
else:
    data = json.loads(version.read_text(encoding="utf-8"))
    if data.get("version") != manifest["release"]:
        errors.append("version and release manifest do not match")
if errors:
    print("BETA RELEASE VALIDATION FAILED")
    for error in errors:
        print(f"- {error}")
    sys.exit(1)
print(f"PASS: LYNQ {manifest['release']} integrated release structure is valid")
