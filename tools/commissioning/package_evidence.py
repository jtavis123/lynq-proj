#!/usr/bin/env python3
import argparse, hashlib, json, zipfile
from pathlib import Path

def digest(path):
    h = hashlib.sha256()
    with path.open("rb") as f:
        for block in iter(lambda: f.read(1024*1024), b""):
            h.update(block)
    return h.hexdigest()

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("session", type=Path)
    ap.add_argument("output", type=Path)
    args = ap.parse_args()

    base = args.session.parent
    files = [args.session]
    evidence = base / "evidence"
    if evidence.exists():
        files.extend(p for p in evidence.rglob("*") if p.is_file())

    manifest = {
        "session": args.session.name,
        "files": [
            {"path": str(p.relative_to(base)), "sha256": digest(p)}
            for p in files
        ]
    }
    with zipfile.ZipFile(args.output, "w", zipfile.ZIP_DEFLATED) as z:
        for p in files:
            z.write(p, p.relative_to(base))
        z.writestr("EVIDENCE_MANIFEST.json",
                   json.dumps(manifest, indent=2) + "\n")
    print(args.output)

if __name__ == "__main__":
    main()
