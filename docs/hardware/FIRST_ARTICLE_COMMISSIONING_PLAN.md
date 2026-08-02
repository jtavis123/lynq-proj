# First Article Commissioning Plan

## Gate 1 — Hub diagnostics
- USB enumeration
- ESP32-S3 identity
- Flash and PSRAM
- Display test pattern
- Touch grid test
- Wi-Fi scan and connection
- BLE scan/advertising
- Reboot and persistence

## Gate 2 — Node staged assembly
- AtomS3 Lite seated in Port ABC
- Port A: IR Unit
- Port B: RF433T
- Port C: RF433R
- No pinched or sharply bent cables
- USB-C accessible
- RF antenna areas unobstructed

## Gate 3 — Node diagnostics
- USB and chip identity
- Wi-Fi and BLE
- Pairing and heartbeat
- RF433 receive using known fixed-code remote
- RF433 replay to a non-safety-critical target
- IR receive and replay
- Reboot and reconnect

## Gate 4 — Integrated test
- Hub shows Node online
- Learn one command
- Save it to a device
- Execute ten times
- Disconnect internet and repeat locally
- Run backup and restore
- Stage a non-destructive update/rollback test

## Gate 5 — First article disposition
Record defects, corrective actions, measurements and photographs. Mark ACCEPT
only when every required test passes or an approved deviation exists.
