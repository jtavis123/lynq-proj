# LYNQ System Integration Guide

## Hub
1. Record serial number and hardware revision.
2. Back up the Waveshare factory flash before the first LYNQ flash.
3. Verify the approved Hub firmware SHA-256 and program it.
4. Validate display, touch, PSRAM, flash, USB, Wi-Fi and BLE.
5. Provision unique credentials; never use a universal default password.
6. Configure update channel and create a verified backup.

## Rev A Node
1. Insert M5Stack AtomS3 Lite C124 into Atomic Port ABC A130.
2. Connect IR Unit U002 to Port A.
3. Connect RF433T U114 to Port B.
4. Connect RF433R U113 to Port C.
5. Use approved factory Grove cables only.
6. Flash the approved Node image and verify its SHA-256.
7. Pair to one Hub; confirm heartbeat, RSSI, capabilities and OTA readiness.

## Network
Use WPA2/WPA3 with unique credentials. Do not expose management ports to the public internet. Confirm Hub-to-Node local control remains functional during internet loss.

## First controlled-device test
Use a non-safety-critical IR device or fixed-code 433.92 MHz ASK/OOK device. Capture, test and replay one command ten consecutive times. Do not use the beta on locks, gates, garage doors, fireplaces, heaters or life-safety equipment.
