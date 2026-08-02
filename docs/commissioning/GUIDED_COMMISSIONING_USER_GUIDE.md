# Guided Commissioning User Guide

## Create a session

```text
python tools/commissioning/commission.py new \
  --session-id SESSION-001 \
  --article-id FAI-0001 \
  --operator JT \
  --hub-serial LYNQ-HUB-REVA-000001 \
  --node-serial LYNQ-NODE-REVA-000001 \
  --output commissioning/SESSION-001/session.json
```

## Record a test

```text
python tools/commissioning/commission.py record-test \
  commissioning/SESSION-001/session.json \
  HUB-USB PASS --operator JT --notes "USB JTAG/serial COM5"
```

## Attach evidence

```text
python tools/commissioning/commission.py attach \
  commissioning/SESSION-001/session.json \
  photos/hub-label.jpg \
  --test-id HUB-USB \
  --description "Hub label and connected USB cable"
```

The tool copies evidence into the session folder and calculates SHA-256.

## Record a defect

```text
python tools/commissioning/commission.py add-defect \
  commissioning/SESSION-001/session.json \
  --defect-id DEF-001 --severity MEDIUM \
  --description "Touch X axis reversed" \
  --containment "Do not release board profile"
```

## Finalize

Finalization is blocked when any required test is failed, blocked, not run, or
when any recorded defect remains open. This prevents an incomplete article from
being marked complete.
