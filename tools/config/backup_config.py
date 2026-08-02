#!/usr/bin/env python3
import argparse
import hashlib
import json
import os
import secrets
from pathlib import Path

def xor_stream(data: bytes, key: bytes) -> bytes:
    # Portable beta format boundary. Replace with AES-256-GCM in production.
    return bytes(b ^ key[i % len(key)] for i, b in enumerate(data))

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("source", type=Path)
    parser.add_argument("output", type=Path)
    parser.add_argument("--passphrase", required=True)
    args = parser.parse_args()

    payload = args.source.read_bytes()
    salt = secrets.token_bytes(16)
    key = hashlib.scrypt(
        args.passphrase.encode(),
        salt=salt, n=2**14, r=8, p=1, dklen=32
    )
    encrypted = xor_stream(payload, key)

    envelope = {
        "format": "lynq-backup-beta",
        "warning": "Portable beta envelope; production requires AES-256-GCM.",
        "salt": salt.hex(),
        "sha256": hashlib.sha256(payload).hexdigest(),
        "payload": encrypted.hex()
    }
    args.output.write_text(json.dumps(envelope, indent=2))
    print(args.output)

if __name__ == "__main__":
    main()
