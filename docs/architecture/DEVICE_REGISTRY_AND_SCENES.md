# Device Registry and Scene Engine

The Device Registry is the shared user-facing model used by the Hub UI, Alexa,
mobile applications, automations and diagnostics.

## Device model

Each device contains:

- Stable device ID
- Friendly name
- Room assignment
- Device type and icon
- Internal command-router endpoint ID
- Alexa exposure setting
- Safety classification
- Enabled/disabled state

## Scene model

A scene contains a friendly name, icon and an ordered list of endpoint actions.
Scene actions execute through the same Hub Command Router used by Alexa and local
control, so safety and endpoint validation remain centralized.

## Persistence

The SDK exposes a storage interface. The Hub implementation will use versioned JSON
stored in NVS or a filesystem partition, with backup and restore added later.
