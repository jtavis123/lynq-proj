# LYNQ Hub Firmware v0.2.0-alpha

Target hardware: **Waveshare ESP32-S3-Touch-LCD-4.3B-BOX**.

This release creates the real ESP-IDF firmware boundary and boot architecture. It intentionally isolates Waveshare-specific LCD and touch initialization in `board_port` until the physical unit is validated.

## Included

- ESP-IDF project and partition table
- ESP32-S3/PSRAM defaults
- `app_main` entry point
- Board abstraction layer
- Boot state machine
- Application lifecycle scaffold
- LYNQ splash and primary-navigation shell hooks
- OTA-ready dual-app partition layout

## Not yet complete

- Official Waveshare RGB LCD BSP merge
- Capacitive-touch controller merge and calibration
- LVGL object rendering
- Wi-Fi provisioning
- Persistent settings
- Node discovery

## Build after installing ESP-IDF 5.3

```bash
cd hub/firmware
idf.py set-target esp32s3
idf.py build
```

Do not flash this scaffold until the Waveshare factory demo and official BSP example have been validated on the physical Hub.
