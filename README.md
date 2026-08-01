# LYNQ Platform

LYNQ is a local-first automation platform that modernizes existing RF and IR devices without requiring users to replace working equipment.

## Product family

- **LYNQ Hub** — touchscreen controller, automation engine, and Alexa integration point
- **LYNQ Node One** — universal RF/IR learning and replay node
- **LYNQ Node Mini** — compact node for simple installations
- **LYNQ Node Relay** — dry-contact relay controller
- **LYNQ Node Garage** — purpose-built garage and gate controller

## Core principles

- Local-first operation
- Alexa voice control routed through the LYNQ Hub
- No mandatory subscription for core operation
- Capability-based Node architecture
- Secure pairing and OTA updates
- Professional installer workflow
- Premium, consumer-friendly UI

## Repository layout

- `sdk/` shared hardware-independent C++ SDK
- `hub/` LYNQ Hub firmware and UI
- `node/` Node firmware
- `simulator/` desktop simulator
- `docs/` project requirements, architecture, protocol, and engineering records
- `hardware/` BOMs, schematics, and hardware references
- `manufacturing/` work instructions and factory test procedures
- `marketing/` datasheets, logos, and product assets
- `tools/` developer and release tools

## Build the SDK

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

## Status

**Release:** v0.1.0-alpha — Repository Foundation

The product definition and architecture are complete. SDK implementation and Hub hardware bring-up are active.

## Active milestone

Hub Bring-Up v0.2.0-alpha: ESP-IDF scaffold, board abstraction, boot lifecycle and hardware validation plan.

## Current engineering focus

- Wi-Fi provisioning foundation
- Persistent Hub settings
- Physical Waveshare display and touch bring-up
- Node discovery after network validation

## Current connectivity milestone

Node discovery, pairing, capability reporting, heartbeats, and offline detection are implemented as portable SDK services. Physical transport validation remains pending Node hardware.
