# Hub Command Router Simulator

The command-router host test validates:

- Learned-signal routing
- Scene activation
- Expiration handling
- Unknown endpoint rejection
- Duplicate-command suppression
- Default denial for remote safety-sensitive endpoints

Build and test from the repository root:

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```
