# Changelog

## 0.3.0-alpha - Node Connectivity Foundation

- Added Node identity, capability, health, pairing and heartbeat models.
- Added transport-independent Node discovery and pairing interface.
- Added thread-safe Node registry and Hub-side Node manager.
- Added heartbeat processing and offline timeout detection.
- Added ESP-IDF Node transport boundary and Node connectivity requirements.
- Added host-side Node lifecycle tests.

## 0.2.1-alpha - Wi-Fi Provisioning Foundation

- Added portable Wi-Fi data types and service interface.
- Added Wi-Fi provisioning controller with EventBus integration.
- Added ESP-IDF Hub Wi-Fi adapter boundary.
- Added provisioning workflow and security requirements.
- Added host-side provisioning tests.


## 0.2.0-alpha - Hub Bring-Up Foundation

- Added ESP-IDF Hub firmware project.
- Added ESP32-S3/PSRAM configuration defaults.
- Added OTA-ready partition table.
- Added isolated Waveshare board port.
- Added Hub boot state machine and application lifecycle.
- Added splash and navigation shell hooks.
- Added Hub bring-up checklist and software requirements.

## 0.1.1-alpha - Core SDK Expansion

- Added thread-safe EventBus with subscription management.
- Added typed Configuration store.
- Added reusable StateMachine template.
- Added portable TimerService abstraction.
- Expanded unit tests and SDK documentation.

All notable changes to the LYNQ Platform are documented here.

## [0.1.0-alpha] - 2026-08-01

### Added
- Professional monorepo foundation
- Initial shared SDK core
- Result and ErrorCode types
- Logger with pluggable sinks
- UUID and Version utilities
- Unit tests and CMake build
- GitHub Actions CI workflow
- Project Bible, architecture, protocol, roadmap, and coding standards