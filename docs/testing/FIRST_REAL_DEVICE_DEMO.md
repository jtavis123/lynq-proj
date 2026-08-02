# First Real Device Demo

## Objective

Prove the full physical LYNQ path with one safe device and one command.

## Recommended first target

Use a non-safety-critical IR device such as a television or sound bar. Use RF433 only with a supported fixed-code device you own and are authorized to control.

## Procedure

1. Flash the Hub diagnostics build and confirm display, touch, Wi-Fi and storage.
2. Flash one AtomS3-Lite Node and confirm USB logs, Wi-Fi/BLE, button and status LED.
3. Connect the IR Unit or RF433 units using the locked Grove harness layout.
4. Pair the Node to the Hub and verify heartbeat and capability reporting.
5. Create a device on the Hub.
6. Start Learn, press the original remote once, and verify a capture fingerprint appears.
7. Test replay and observe the real device respond.
8. Save the command and bind it to a device button.
9. Execute the device button from the Hub.
10. Verify Node acknowledgement and a successful Activity History entry.

Do not use garage doors, gates, locks, fireplaces, heaters or other safety-sensitive equipment for the first demonstration.
