# Waveshare ESP32-S3 Touch LCD 4.3 Type-B BSP Gate

This directory is the only location where manufacturer-specific display, touch,
backlight and GPIO code may enter LYNQ Hub OS.

Before concrete driver code is frozen, import and archive the exact Waveshare
example project shipped for the board revision printed on the user's unit. Verify:

- LCD controller and RGB timing
- touch-controller model and I2C address
- backlight GPIO/polarity
- reset and power-enable pins
- flash and PSRAM sizes
- ESP-IDF version used by the manufacturer example

Do not copy pin mappings from a visually similar Waveshare board.
