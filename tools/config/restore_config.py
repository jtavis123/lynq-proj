#!/usr/bin/env python3
import argparse
import hashlib
import json
from pathlib import Path

def xor_stream(data: bytes, key: bytes) -> bytes:
    return bytes(b ^ key[i % len(key)] for i, b in enumerate(data))

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("backup", type=Path)
    parser.add_argument("output", type=Path)
    parser.add_argument("--passphrase", required=True)
    args = parser.parse_args()

    envelope = json.loads(args.backup.read_text())
    salt = bytes.fromhex(envelope["salt"])
    key = hashlib.scrypt(
        args.passphrase.encode(),
        salt=salt, n=2**14, r=8, p=1, dklen=32
    )
    payload = xor_stream(bytes.fromhex(envelope["payload"]), key)
    digest = hashlib.sha256(payload).hexdigest()
    if digest != envelope["sha256"]:
        raise SystemExit("Backup integrity check failed.")
    args.output.write_bytes(payload)
    print(args.output)

if __name__ == "__main__":
    main()
