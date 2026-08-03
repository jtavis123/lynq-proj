#!/usr/bin/env python3
from __future__ import annotations

import argparse
import hashlib
import json
import re
import shutil
import subprocess
import sys
from datetime import datetime, timezone
from pathlib import Path

PORT_PATTERNS = (
    "USB JTAG/serial",
    "USB Serial Device",
    "CP210",
    "CH340",
    "ESP32",
)

def utc_now() -> str:
    return datetime.now(timezone.utc).isoformat()

def sha256(path: Path) -> str:
    digest = hashlib.sha256()
    with path.open("rb") as stream:
        for block in iter(lambda: stream.read(1024 * 1024), b""):
            digest.update(block)
    return digest.hexdigest()

def run_command(command: list[str]) -> subprocess.CompletedProcess:
    return subprocess.run(command, capture_output=True, text=True)

def list_ports() -> list[dict]:
    try:
        from serial.tools import list_ports
    except ImportError:
        return []

    result = []
    for port in list_ports.comports():
        description = port.description or ""
        probable = any(pattern.lower() in description.lower()
                       for pattern in PORT_PATTERNS)
        result.append({
            "device": port.device,
            "description": description,
            "hwid": port.hwid or "",
            "probableEspDevice": probable,
        })
    return result

def command_detect(args):
    ports = list_ports()
    print(json.dumps({"detectedAt": utc_now(), "ports": ports}, indent=2))
    return 0 if ports else 2

def command_verify(args):
    actual = sha256(args.artifact)
    print(json.dumps({
        "artifact": str(args.artifact),
        "sha256": actual,
        "expected": args.expected_sha256,
        "match": actual.lower() == args.expected_sha256.lower(),
    }, indent=2))
    return 0 if actual.lower() == args.expected_sha256.lower() else 1

def command_chip_info(args):
    command = [
        args.esptool, "--chip", "esp32s3",
        "--port", args.port, "chip_id"
    ]
    completed = run_command(command)
    record = {
        "timestamp": utc_now(),
        "command": command,
        "returnCode": completed.returncode,
        "stdout": completed.stdout,
        "stderr": completed.stderr,
    }
    args.output.write_text(json.dumps(record, indent=2) + "\n")
    print(args.output)
    return completed.returncode

def command_backup(args):
    args.output.parent.mkdir(parents=True, exist_ok=True)
    command = [
        args.esptool, "--chip", "esp32s3",
        "--port", args.port, "--baud", str(args.baud),
        "read_flash", "0x0", hex(args.size), str(args.output)
    ]
    completed = run_command(command)
    record = {
        "timestamp": utc_now(),
        "command": command,
        "returnCode": completed.returncode,
        "stdout": completed.stdout,
        "stderr": completed.stderr,
    }
    if completed.returncode == 0 and args.output.exists():
        record["sha256"] = sha256(args.output)
        record["sizeBytes"] = args.output.stat().st_size

    log = args.output.with_suffix(args.output.suffix + ".json")
    log.write_text(json.dumps(record, indent=2) + "\n")
    print(log)
    return completed.returncode

def command_capture_serial(args):
    try:
        import serial
    except ImportError:
        print("pyserial is required.", file=sys.stderr)
        return 2

    args.output.parent.mkdir(parents=True, exist_ok=True)
    with serial.Serial(args.port, args.baud, timeout=1) as connection, \
         args.output.open("w", encoding="utf-8") as log:
        started = datetime.now(timezone.utc)
        while (datetime.now(timezone.utc) - started).total_seconds() < args.seconds:
            line = connection.readline()
            if line:
                text = line.decode("utf-8", errors="replace").rstrip()
                log.write(f"{utc_now()} {text}\n")
                log.flush()
    print(args.output)
    return 0

def command_new_session(args):
    commissioning = Path(__file__).resolve().parents[1] / "commissioning" / "commission.py"
    if not commissioning.exists():
        print("Commissioning tool not found.", file=sys.stderr)
        return 2
    command = [
        sys.executable, str(commissioning), "new",
        "--session-id", args.session_id,
        "--article-id", args.article_id,
        "--operator", args.operator,
        "--hub-serial", args.hub_serial,
        "--output", str(args.output)
    ]
    for serial_number in args.node_serial:
        command.extend(["--node-serial", serial_number])
    return subprocess.call(command)

def command_package(args):
    package_tool = Path(__file__).resolve().parents[1] / "commissioning" / "package_evidence.py"
    report_tool = Path(__file__).resolve().parents[1] / "commissioning" / "generate_report.py"
    if not package_tool.exists() or not report_tool.exists():
        print("Commissioning report tools not found.", file=sys.stderr)
        return 2

    args.output_dir.mkdir(parents=True, exist_ok=True)
    report = args.output_dir / "commissioning-report.html"
    evidence = args.output_dir / "commissioning-evidence.zip"

    r1 = subprocess.call([sys.executable, str(report_tool),
                          str(args.session), str(report)])
    r2 = subprocess.call([sys.executable, str(package_tool),
                          str(args.session), str(evidence)])
    return 0 if r1 == 0 and r2 == 0 else 1

def build_parser():
    parser = argparse.ArgumentParser(description="LYNQ production bench console")
    sub = parser.add_subparsers(dest="command", required=True)

    detect = sub.add_parser("detect")
    detect.set_defaults(func=command_detect)

    verify = sub.add_parser("verify-artifact")
    verify.add_argument("artifact", type=Path)
    verify.add_argument("expected_sha256")
    verify.set_defaults(func=command_verify)

    chip = sub.add_parser("chip-info")
    chip.add_argument("--port", required=True)
    chip.add_argument("--esptool", default="esptool.py")
    chip.add_argument("--output", required=True, type=Path)
    chip.set_defaults(func=command_chip_info)

    backup = sub.add_parser("backup-flash")
    backup.add_argument("--port", required=True)
    backup.add_argument("--size", type=lambda x: int(x, 0), required=True)
    backup.add_argument("--baud", type=int, default=460800)
    backup.add_argument("--esptool", default="esptool.py")
    backup.add_argument("--output", required=True, type=Path)
    backup.set_defaults(func=command_backup)

    capture = sub.add_parser("capture-serial")
    capture.add_argument("--port", required=True)
    capture.add_argument("--baud", type=int, default=115200)
    capture.add_argument("--seconds", type=int, default=30)
    capture.add_argument("--output", required=True, type=Path)
    capture.set_defaults(func=command_capture_serial)

    session = sub.add_parser("new-session")
    session.add_argument("--session-id", required=True)
    session.add_argument("--article-id", required=True)
    session.add_argument("--operator", required=True)
    session.add_argument("--hub-serial", required=True)
    session.add_argument("--node-serial", action="append", default=[])
    session.add_argument("--output", required=True, type=Path)
    session.set_defaults(func=command_new_session)

    package = sub.add_parser("package-session")
    package.add_argument("session", type=Path)
    package.add_argument("--output-dir", required=True, type=Path)
    package.set_defaults(func=command_package)
    return parser

if __name__ == "__main__":
    arguments = build_parser().parse_args()
    raise SystemExit(arguments.func(arguments))
