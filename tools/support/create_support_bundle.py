#!/usr/bin/env python3
import argparse
import json
import re
import zipfile
from pathlib import Path

SENSITIVE = re.compile(
    r"(password|token|secret|credential|private.?key)",
    re.IGNORECASE
)

def redact(value):
    if isinstance(value, dict):
        return {
            key: "[REDACTED]" if SENSITIVE.search(key) else redact(item)
            for key, item in value.items()
        }
    if isinstance(value, list):
        return [redact(item) for item in value]
    return value

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("diagnostics", type=Path)
    parser.add_argument("output", type=Path)
    args = parser.parse_args()

    data = redact(json.loads(args.diagnostics.read_text()))
    with zipfile.ZipFile(args.output, "w", zipfile.ZIP_DEFLATED) as z:
        z.writestr("diagnostics-redacted.json",
                   json.dumps(data, indent=2))
        z.writestr("README.txt",
                   "LYNQ support bundle. Credentials and secrets are removed.")
    print(args.output)

if __name__ == "__main__":
    main()
