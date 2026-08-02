# Deployment and Service Integration Guide

## Installer workflow

1. Connect only the Hub by USB.
2. Start the local installer.
3. Enter the one-time token displayed locally.
4. Detect the connected ESP32-S3.
5. Read chip identity and flash size.
6. Back up the complete factory flash.
7. Verify and archive the backup.
8. Flash the approved Hub image.
9. Complete Wi-Fi and household setup.
10. Enroll Nodes one at a time.

## OTA release workflow

1. Build Hub and Node release images in CI.
2. Generate SHA-256 values.
3. Create a versioned release manifest.
4. Sign the manifest with the protected release key.
5. Publish artifacts to the controlled release channel.
6. Hub downloads, verifies and stages the update.
7. Hub updates Nodes sequentially.
8. Hub updates itself last.
9. Health checks confirm the release.
10. Roll back any device that fails its health deadline.

## Backup workflow

Back up before:

- Firmware updates
- Factory reset
- Large device-database changes
- Restoring another backup
- Replacing the Hub

Backup contents:

- Hub identity references
- Rooms, devices and learned-command metadata
- Node registry
- Scenes and automations
- User preferences
- Cloud-account references without reusable secrets

## Service mode workflow

1. User or administrator enables Service Mode locally.
2. Hub displays a short authorization code.
3. Technician enters the code.
4. Hub grants only the selected permissions.
5. Service banner remains visible.
6. Every action is recorded.
7. Session automatically expires.
