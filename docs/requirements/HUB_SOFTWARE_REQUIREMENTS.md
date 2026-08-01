# LYNQ Hub Software Requirements v0.2

## Mandatory v0.2 bring-up requirements
- HUB-BOOT-001: Firmware shall start through ESP-IDF `app_main`.
- HUB-BOOT-002: Boot state shall progress through board, services, UI and ready states.
- HUB-BOOT-003: Failure during initialization shall enter a defined recovery state.
- HUB-HAL-001: Display and touch hardware access shall remain inside `board_port`.
- HUB-UI-001: The first rendered product screen shall use approved LYNQ branding.
- HUB-UI-002: Primary navigation shall include Home, Devices, Scenes, Learn and Settings.
- HUB-OTA-001: Partitioning shall reserve two OTA application slots.
- HUB-ALEXA-001: Future Alexa actions shall enter the same Hub Command Bus used by local UI actions.

## Hardware-dependent hold point
The display and touch implementation cannot be accepted until verified on the ordered Waveshare unit.
