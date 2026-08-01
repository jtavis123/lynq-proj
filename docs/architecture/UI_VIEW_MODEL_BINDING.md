# UI View-Model Binding

The browser simulator and embedded LVGL implementation consume the same conceptual
application state:

- current page
- connectivity status
- devices
- scenes
- automations
- alerts

The simulator validates behavior and information hierarchy. The embedded Hub uses
the C++ `UiApplicationModel` and LVGL widgets. Visual behavior proven in the
simulator is then translated into the hardware renderer without moving command,
scene or automation logic into the UI layer.
