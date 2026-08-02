# LYNQ Recovery Guide

1. Preserve serial logs and the latest activity/audit records.
2. Restart only the failed service when possible.
3. If the Hub cannot boot normally, enter Factory Mode and run storage, display and network tests.
4. Restore the last known good configuration before erasing storage.
5. Roll back OTA only to a signed known-good image.
6. For a Node that repeatedly disconnects, verify power, cable seating, Wi-Fi RSSI and firmware before replacing hardware.
7. Never repeatedly replay a safety-sensitive command during diagnosis.
