# LYNQ v2.0.0-beta.1 Installation Guide

## 1. Repository preparation

1. Start from the repository containing releases v1.1.0 through v1.9.0.
2. Copy this update into the repository root.
3. Run the release validator:

```powershell
powershell -ExecutionPolicy Bypass -File tools/release/validate_beta_release.ps1 .
```

## 2. Hub preparation

1. Back up the factory firmware before flashing.
2. Install the supported ESP-IDF environment.
3. Confirm the exact Waveshare 4.3-inch Type-B BSP and board revision.
4. Build and flash the Hub project.
5. Verify display, touch, PSRAM, flash, Wi-Fi and BLE diagnostics.

## 3. Node preparation

1. Assemble the AtomS3-Lite, Atomic Port ABC, IR Unit, RF433T and RF433R using premade Grove cables.
2. Build and flash the Rev A Node firmware.
3. Verify status LED, pairing button, Wi-Fi/BLE and heartbeat reporting.

## 4. First integrated test

1. Pair the Node to the Hub.
2. Learn one non-safety-critical IR command.
3. Test replay and save it to a Device.
4. Execute the Device command from Home.
5. Add the command to a Scene and execute the Scene.
6. Confirm acknowledgement and Activity history.
7. Repeat with one supported fixed-code 433 MHz command.

## 5. Beta restrictions

Do not use the beta to control locks, gates, garage doors, fireplaces, heaters or other safety-sensitive equipment. Rev A RF support is limited to supported 433.92 MHz ASK/OOK fixed-code devices. Live Alexa operation still requires production cloud hosting, OAuth account linking and Amazon certification.
