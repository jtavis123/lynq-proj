# Hub UI Architecture

The UI is divided into two layers:

1. **Portable application model**
   - routes
   - navigation history
   - dashboard data
   - status summaries
   - theme tokens

2. **ESP-IDF/LVGL adapter**
   - widgets
   - animations
   - touch events
   - display lifecycle
   - focus and modal handling

This separation allows host testing before the physical Hub arrives and prevents
business logic from becoming tied to LVGL object pointers.

## Core pages

- Home
- Rooms
- Devices
- Device Detail
- Scenes
- Scene Detail
- Automations
- Learn
- Settings
- Node Detail

## Performance targets

- Touch acknowledgement within 100 ms
- Primary navigation transition within 250 ms
- No blocking network or RF work on the UI task
- Dashboard refreshes through event-driven model updates
