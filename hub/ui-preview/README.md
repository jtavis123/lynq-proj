# LYNQ Hub UI Preview Specification

Target: Waveshare ESP32-S3 4.3-inch capacitive touchscreen, 800x480.

## Design language

The interface combines Ring-like clarity with Tesla-like restraint:

- dark neutral background
- large, calm typography
- generous spacing
- rounded cards
- minimal borders
- one primary accent
- status shown through icon, label and color
- no dense desktop-style tables

## Primary navigation

Persistent bottom navigation:

1. Home
2. Devices
3. Scenes
4. Automations
5. Settings

Rooms and Learn are reached contextually:

- Rooms from Home or Devices
- Learn from Add Device and device menus

## Home screen

- Greeting and home name
- Connectivity strip for Wi-Fi, cloud and Alexa
- Favorite device cards
- Favorite scene cards
- Node or safety alerts
- Quick Add button

## Hardware-validation boundary

This release defines the application state, routes, data models, theme and LVGL
adapter boundary. Pixel rendering remains dependent on the official Waveshare
display/touch BSP and physical-board testing.
