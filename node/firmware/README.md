# LYNQ Node One Firmware

This ESP-IDF project is the production firmware foundation for LYNQ Node One.

## Current scope

- ESP32-S3 project scaffold
- OTA-ready partitioning
- Node application lifecycle
- Isolated hardware abstraction
- Status-state foundation
- Shared SDK integration boundary

## Hardware validation gate

GPIO assignments and concrete RF/IR drivers are intentionally not frozen until the
exact off-the-shelf modules, USB-C power system and plug-in cable harnesses are
assembled and bench tested.

## Build

```bash
idf.py set-target esp32s3
idf.py build
idf.py flash monitor
```
