# Core SDK

The LYNQ Core SDK is hardware-independent and shared by the Hub, Nodes, simulator, and engineering tools.

## Modules in v0.1.1-alpha

- `Result<T>` and `ErrorCode`
- `Logger`
- `UUID`
- `Version`
- `EventBus`
- `Configuration`
- `StateMachine`
- `TimerService`

## Design notes

- Public APIs avoid exceptions for normal operational failures.
- Event callbacks execute outside the EventBus lock.
- Configuration supports typed runtime values; persistence will be added behind a storage adapter.
- State machines explicitly whitelist legal transitions.
- TimerService is a portable development implementation and will receive an ESP-IDF/FreeRTOS backend for embedded targets.
