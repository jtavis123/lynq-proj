#!/usr/bin/env python3
import argparse, json, re, sys
from pathlib import Path

SHA = re.compile(r"^[0-9a-fA-F]{64}$")
REQUIRED_HUB = {
    "usb_enumeration", "chip_identity", "flash", "psram",
    "display", "touch", "wifi", "ble", "reboot"
}
REQUIRED_NODE = {
    "usb_enumeration", "chip_identity", "wifi", "ble",
    "pairing", "heartbeat", "rf433_receive", "rf433_transmit",
    "ir_receive", "ir_transmit", "reboot"
}

def passed_tests(tests, required):
    return [name for name in required if tests.get(name) != "PASS"]

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("record", type=Path)
    args = ap.parse_args()
    data = json.loads(args.record.read_text())
    errors = []

    backup = data.get("hub", {}).get("factoryFlashBackup", {})
    if not backup.get("verified"):
        errors.append("Factory flash backup is not verified.")
    if not SHA.match(backup.get("sha256", "")):
        errors.append("Factory flash backup SHA-256 is invalid.")

    missing = passed_tests(data.get("hub", {}).get("tests", {}), REQUIRED_HUB)
    if missing:
        errors.append("Hub tests not passed: " + ", ".join(sorted(missing)))

    for node in data.get("nodes", []):
        if not node.get("gpioProfileLocked"):
            errors.append(f"{node.get('nodeId','Node')} GPIO profile is not locked.")
        missing = passed_tests(node.get("tests", {}), REQUIRED_NODE)
        if missing:
            errors.append(
                f"{node.get('nodeId','Node')} tests not passed: " +
                ", ".join(sorted(missing))
            )

    dims = data.get("hub", {}).get("measuredDimensionsMm", {})
    if any(dims.get(k) in (None, 0, "") for k in ("width","height","depth")):
        errors.append("Hub measured dimensions are incomplete.")

    if data.get("disposition") != "ACCEPT":
        errors.append("First article disposition is not ACCEPT.")
    if not data.get("approvedBy"):
        errors.append("First article approval is missing.")

    if errors:
        print("FAIL: First article is incomplete.")
        for e in errors:
            print(" -", e)
        sys.exit(1)
    print("PASS: First article record is complete and accepted.")

if __name__ == "__main__":
    main()
