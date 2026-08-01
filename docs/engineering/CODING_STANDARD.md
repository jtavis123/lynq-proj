# Coding Standard

- C++20 for the shared SDK where toolchain support permits
- ESP-IDF and FreeRTOS for embedded targets
- LVGL for the Hub UI
- No direct hardware access outside the HAL
- No business logic in screens or widgets
- Public APIs return `Result<T>` rather than raw booleans
- Public APIs require documentation
- Hardware-independent modules require tests where practical
- Avoid global mutable state
- Prefer explicit ownership and deterministic lifetime
