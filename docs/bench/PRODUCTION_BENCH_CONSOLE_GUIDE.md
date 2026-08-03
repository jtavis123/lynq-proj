# Production Bench Console Guide

The Bench Console combines the release's commissioning, evidence and hardware
tools into one operator workflow.

## Prepare Windows

```text
cd C:\path\to\lynq-proj
python -m pip install -r tools\bench-console\requirements.txt
```

## Detect serial devices

```text
python tools\bench-console\bench_console.py detect
```

Disconnect other ESP devices so the Hub or Node can be identified reliably.

## Read chip identity

```text
python tools\bench-console\bench_console.py chip-info \
  --port COM5 \
  --output commissioning\SESSION-001\hub-chip-info.json
```

## Back up factory flash

The required flash size must be confirmed from the physical board before use.

```text
python tools\bench-console\bench_console.py backup-flash \
  --port COM5 \
  --size 0x1000000 \
  --output commissioning\SESSION-001\hub-factory-flash.bin
```

The console creates a JSON sidecar containing command output, file size and
SHA-256. Preserve both files.

## Verify a firmware artifact

```text
python tools\bench-console\bench_console.py verify-artifact \
  releases\hub.bin EXPECTED_SHA256
```

Never flash an artifact that fails verification.

## Capture serial logs

```text
python tools\bench-console\bench_console.py capture-serial \
  --port COM5 --seconds 60 \
  --output commissioning\SESSION-001\logs\hub-boot.log
```

## Start commissioning

```text
python tools\bench-console\bench_console.py new-session \
  --session-id SESSION-001 \
  --article-id FAI-0001 \
  --operator JT \
  --hub-serial LYNQ-HUB-REVA-000001 \
  --node-serial LYNQ-NODE-REVA-000001 \
  --output commissioning\SESSION-001\session.json
```

## Package the final evidence

```text
python tools\bench-console\bench_console.py package-session \
  commissioning\SESSION-001\session.json \
  --output-dir commissioning\SESSION-001\final
```
