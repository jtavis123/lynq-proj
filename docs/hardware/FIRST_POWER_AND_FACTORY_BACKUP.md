# First Power and Factory Backup

## Hub

1. Disconnect all other ESP devices.
2. Connect the Hub using a known-good USB data cable.
3. Record the Windows COM port and exact USB descriptor.
4. Read the ESP32-S3 chip identity, flash size and MAC address.
5. Back up the complete factory flash before erase or programming.
6. Calculate and record SHA-256.
7. Store two copies in separate locations.
8. Verify the backup file can be read.
9. Only then flash LYNQ diagnostics.

## Node

For the first Node, power only the AtomS3 Lite and Port ABC assembly before
attaching RF/IR units. Confirm USB, chip identity, flash and basic GPIO access.
Disconnect power before attaching or moving Grove cables.
