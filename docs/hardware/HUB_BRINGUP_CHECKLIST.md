# LYNQ Hub Hardware Bring-Up Checklist

## Target
Waveshare ESP32-S3-Touch-LCD-4.3B-BOX, 800x480 capacitive touch.

## Stage 1 - Receiving inspection
- Photograph box label, model, SKU and board revision.
- Confirm enclosure, display glass and USB-C connector are undamaged.
- Record serial or lot markings.

## Stage 2 - Factory validation
- Power the unit using a known-good USB-C supply.
- Run the factory image before replacing it.
- Confirm LCD, backlight, touch across all corners, Wi-Fi and any onboard audio.
- Record display orientation and touch-coordinate orientation.

## Stage 3 - Development environment
- Install ESP-IDF 5.3.
- Build and flash the official Waveshare LVGL porting example.
- Preserve a copy of the working example and sdkconfig.

## Stage 4 - LYNQ integration
- Copy only the verified LCD/touch initialization into `board_port`.
- Confirm 800x480 orientation.
- Confirm touch mapping and multi-touch behavior if supported.
- Verify PSRAM and flash sizes.
- Render the LYNQ splash screen.
- Navigate among Home, Devices, Scenes, Learn and Settings.

## Acceptance criteria
- No boot loop or watchdog reset.
- Touch targets align within acceptable tolerance across the panel.
- UI remains responsive for 30 minutes.
- Heap remains stable during navigation.
- Reboot returns to LYNQ without manual intervention.
