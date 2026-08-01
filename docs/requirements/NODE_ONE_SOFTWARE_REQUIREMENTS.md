# Node One Software Requirements

## Required functions

1. Join the local Wi-Fi network using Hub-mediated provisioning.
2. Securely pair with one LYNQ Hub.
3. Advertise RF, IR, battery and OTA capabilities.
4. Send periodic health heartbeats.
5. Capture RF or IR timing data without blocking network health tasks.
6. Replay a stored command using timing-safe hardware drivers.
7. Cache commands assigned to the Node.
8. Support signed OTA updates with rollback.
9. Report battery state, signal strength, memory, uptime and errors.
10. Use a consistent status-LED language.

## Learning workflow

- Hub requests learning mode.
- Node indicates learning state.
- User presses the original remote.
- Node captures and validates the waveform.
- Node returns metadata and raw timing data.
- Hub names and stores the command.
- Node can immediately replay the capture for verification.

## Safety requirements

- Only one RF or IR capture session may run at a time.
- Transmit is disabled while capture is active.
- Capture must end on timeout or explicit cancellation.
- Maximum pulse count and capture duration must be bounded.
- Garage, gate and fireplace commands require explicit device classification
  before voice exposure.
