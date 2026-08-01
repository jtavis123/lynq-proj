# LYNQ Hub Wi-Fi Provisioning

## Purpose

The Hub requires a guided Wi-Fi setup flow before Node discovery, Alexa account linking, OTA updates, or remote services can operate.

## User flow

1. Hub boots and checks for a saved network profile.
2. If none exists, the Hub opens the Wi-Fi onboarding screen.
3. User scans for nearby networks.
4. User selects an SSID and enters the password using the touchscreen keyboard.
5. The Hub attempts the connection and reports progress.
6. Credentials are stored securely only after a successful connection.
7. The Hub reconnects automatically after reboot or a temporary outage.

## Required states

- Uninitialized
- Idle
- Scanning
- Connecting
- Connected
- Provisioning
- Reconnecting
- Failed

## Security rules

- Passwords must never appear in logs or event payloads.
- Credentials are stored using ESP-IDF NVS encryption when production security is enabled.
- Factory reset and "Forget Network" must erase stored credentials.
- Alexa integration remains separate from local Wi-Fi credentials.

## Hardware bring-up hold point

The portable controller and Hub adapter are included in v0.2.1-alpha. Actual ESP-IDF scan, event-loop, IP acquisition, NVS encryption, and reconnect behavior require validation on the physical Waveshare Hub.
