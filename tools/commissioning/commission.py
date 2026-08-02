#!/usr/bin/env python3
"""LYNQ guided commissioning session runner.

This tool records evidence; it does not automatically certify that hardware
passed. Operators must enter real observations and attach real evidence.
"""
from __future__ import annotations

import argparse
import hashlib
import json
import shutil
import sys
from datetime import datetime, timezone
from pathlib import Path
from typing import Any

TESTS = {
    "hub": [
        ("HUB-USB", "USB enumeration"),
        ("HUB-CHIP", "ESP32-S3 chip identity"),
        ("HUB-FLASH", "Flash capacity"),
        ("HUB-PSRAM", "PSRAM detection"),
        ("HUB-DISPLAY", "Display test pattern"),
        ("HUB-TOUCH", "Touch grid"),
        ("HUB-WIFI", "Wi-Fi"),
        ("HUB-BLE", "BLE"),
        ("HUB-REBOOT", "Reboot and persistence"),
    ],
    "node": [
        ("NODE-USB", "USB enumeration"),
        ("NODE-CHIP", "ESP32-S3 chip identity"),
        ("NODE-WIFI", "Wi-Fi"),
        ("NODE-BLE", "BLE"),
        ("NODE-PAIR", "Hub pairing"),
        ("NODE-HEARTBEAT", "Heartbeat"),
        ("NODE-RF-RX", "433 MHz receive"),
        ("NODE-RF-TX", "433 MHz transmit"),
        ("NODE-IR-RX", "IR receive"),
        ("NODE-IR-TX", "IR transmit"),
        ("NODE-REBOOT", "Reboot and reconnect"),
    ],
    "system": [
        ("SYS-LEARN", "Learn and save command"),
        ("SYS-EXECUTE-10", "Ten-command execution"),
        ("SYS-OFFLINE", "Local operation without internet"),
        ("SYS-BACKUP", "Configuration backup and restore"),
        ("SYS-OTA", "OTA and rollback"),
        ("SYS-SUPPORT", "Redacted support bundle"),
    ],
}

def now() -> str:
    return datetime.now(timezone.utc).isoformat()

def sha256(path: Path) -> str:
    h = hashlib.sha256()
    with path.open("rb") as f:
        for chunk in iter(lambda: f.read(1024 * 1024), b""):
            h.update(chunk)
    return h.hexdigest()

def load(path: Path) -> dict[str, Any]:
    return json.loads(path.read_text())

def save(path: Path, data: dict[str, Any]) -> None:
    path.write_text(json.dumps(data, indent=2) + "\n")

def new_session(args: argparse.Namespace) -> None:
    session = {
        "schemaVersion": 1,
        "release": "2.4.0-beta.1",
        "sessionId": args.session_id,
        "articleId": args.article_id,
        "operator": args.operator,
        "startedAt": now(),
        "completedAt": None,
        "status": "IN_PROGRESS",
        "devices": {
            "hub": {"serialNumber": args.hub_serial, "evidence": []},
            "nodes": [{"serialNumber": serial, "evidence": []}
                      for serial in args.node_serial]
        },
        "tests": [
            {
                "testId": test_id,
                "group": group,
                "name": name,
                "result": "NOT_RUN",
                "measurement": "",
                "limits": "",
                "notes": "",
                "operator": "",
                "timestamp": "",
                "evidence": [],
            }
            for group, items in TESTS.items()
            for test_id, name in items
        ],
        "defects": [],
        "approvals": [],
    }
    args.output.parent.mkdir(parents=True, exist_ok=True)
    save(args.output, session)
    print(args.output)

def record_test(args: argparse.Namespace) -> None:
    data = load(args.session)
    matches = [t for t in data["tests"] if t["testId"] == args.test_id]
    if not matches:
        raise SystemExit(f"Unknown test ID: {args.test_id}")
    test = matches[0]
    test.update({
        "result": args.result,
        "measurement": args.measurement or "",
        "limits": args.limits or "",
        "notes": args.notes or "",
        "operator": args.operator,
        "timestamp": now(),
    })
    save(args.session, data)
    print(f"{args.test_id}: {args.result}")

def attach(args: argparse.Namespace) -> None:
    data = load(args.session)
    if not args.file.exists():
        raise SystemExit(f"Evidence file not found: {args.file}")

    evidence_dir = args.session.parent / "evidence"
    evidence_dir.mkdir(exist_ok=True)
    destination = evidence_dir / args.file.name
    if destination.resolve() != args.file.resolve():
        shutil.copy2(args.file, destination)

    record = {
        "file": str(destination.relative_to(args.session.parent)),
        "sha256": sha256(destination),
        "description": args.description,
        "capturedAt": now(),
    }

    if args.test_id:
        matches = [t for t in data["tests"] if t["testId"] == args.test_id]
        if not matches:
            raise SystemExit(f"Unknown test ID: {args.test_id}")
        matches[0]["evidence"].append(record)
    else:
        data["devices"]["hub"]["evidence"].append(record)

    save(args.session, data)
    print(destination)

def add_defect(args: argparse.Namespace) -> None:
    data = load(args.session)
    data["defects"].append({
        "defectId": args.defect_id,
        "severity": args.severity,
        "description": args.description,
        "containment": args.containment,
        "status": "OPEN",
        "createdAt": now(),
    })
    save(args.session, data)
    print(args.defect_id)

def finalize(args: argparse.Namespace) -> None:
    data = load(args.session)
    failed = [t["testId"] for t in data["tests"] if t["result"] == "FAIL"]
    incomplete = [t["testId"] for t in data["tests"]
                  if t["result"] in ("NOT_RUN", "BLOCKED")]
    open_defects = [d["defectId"] for d in data["defects"]
                    if d["status"] == "OPEN"]

    if failed or incomplete or open_defects:
        print("Cannot finalize:")
        if failed: print(" Failed:", ", ".join(failed))
        if incomplete: print(" Incomplete:", ", ".join(incomplete))
        if open_defects: print(" Open defects:", ", ".join(open_defects))
        raise SystemExit(1)

    data["status"] = "COMPLETE"
    data["completedAt"] = now()
    data["approvals"].append({
        "role": "Commissioning approver",
        "name": args.approver,
        "timestamp": now(),
    })
    save(args.session, data)
    print("PASS: commissioning session finalized.")

def build_parser() -> argparse.ArgumentParser:
    p = argparse.ArgumentParser()
    sub = p.add_subparsers(dest="command", required=True)

    n = sub.add_parser("new")
    n.add_argument("--session-id", required=True)
    n.add_argument("--article-id", required=True)
    n.add_argument("--operator", required=True)
    n.add_argument("--hub-serial", required=True)
    n.add_argument("--node-serial", action="append", default=[])
    n.add_argument("--output", required=True, type=Path)
    n.set_defaults(func=new_session)

    r = sub.add_parser("record-test")
    r.add_argument("session", type=Path)
    r.add_argument("test_id")
    r.add_argument("result", choices=["PASS", "FAIL", "BLOCKED", "N/A"])
    r.add_argument("--measurement")
    r.add_argument("--limits")
    r.add_argument("--notes")
    r.add_argument("--operator", required=True)
    r.set_defaults(func=record_test)

    a = sub.add_parser("attach")
    a.add_argument("session", type=Path)
    a.add_argument("file", type=Path)
    a.add_argument("--test-id")
    a.add_argument("--description", required=True)
    a.set_defaults(func=attach)

    d = sub.add_parser("add-defect")
    d.add_argument("session", type=Path)
    d.add_argument("--defect-id", required=True)
    d.add_argument("--severity", choices=["LOW", "MEDIUM", "HIGH", "CRITICAL"],
                   required=True)
    d.add_argument("--description", required=True)
    d.add_argument("--containment", required=True)
    d.set_defaults(func=add_defect)

    f = sub.add_parser("finalize")
    f.add_argument("session", type=Path)
    f.add_argument("--approver", required=True)
    f.set_defaults(func=finalize)
    return p

if __name__ == "__main__":
    parser = build_parser()
    ns = parser.parse_args()
    ns.func(ns)
