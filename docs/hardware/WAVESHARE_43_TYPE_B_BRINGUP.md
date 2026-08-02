# Waveshare ESP32-S3 4.3-inch Type-B Bring-Up

## Purpose

Validate the processor, flash, PSRAM, USB serial, display, touch and backlight on the exact physical Hub.

## Safety rule

Do not copy GPIO values from another Waveshare 4.3-inch model. Import the manufacturer example package for the exact Type-B board revision before enabling LCD, touch or backlight drivers.

## Sequence

1. Photograph the front, back, labels and connector area.
2. Record the board revision and factory demo behavior.
3. Identify both USB connectors and use the documented programming port.
4. Record the Windows COM port.
5. Back up the factory firmware before erasing flash.
6. Run the base diagnostic firmware.
7. Confirm ESP32-S3, flash size and PSRAM.
8. Import the exact Waveshare BSP/example dependencies.
9. Bring up backlight at low brightness.
10. Display solid red, green, blue, white and black patterns.
11. Verify touch coordinates at all four corners and center.
12. Launch the LYNQ splash and v1.6.0 UI shell.

## Pass criteria

- Reliable USB connection and serial logging.
- Flash and PSRAM match the purchased board.
- No spontaneous reset for 30 minutes.
- Correct 800x480 orientation.
- Touch error below 15 pixels at validation points.
- Brightness adjustment works without flicker.
