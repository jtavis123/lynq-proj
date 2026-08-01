# LYNQ Hub UI Simulator

Browser-based preview of the 800×480 LYNQ Hub experience.

## Run

From this directory:

```bash
python -m http.server 8080
```

Open `http://localhost:8080`.

## Included interactions

- Primary navigation
- Device toggles
- Offline-device behavior
- Scene execution timestamps
- Automation enable/disable
- Connectivity and Node status
- Simulated alerts

## Tests

```bash
npm test
```

The simulator intentionally uses no third-party runtime packages.
