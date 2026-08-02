# Rev A AtomS3-Lite Node Bring-Up

## Hardware

- AtomS3-Lite
- Atomic Port ABC
- RF433T
- RF433R
- IR Unit
- Three premade Grove cables

## Sequence

1. Flash the AtomS3-Lite before inserting it into the Port ABC carrier.
2. Verify USB serial, RGB LED and button.
3. Power down and assemble Port ABC and Grove modules.
4. Verify the exact Port ABC pin mapping from the official documentation and received hardware.
5. Enable one module at a time: IR, RF433T, RF433R.
6. Verify Node discovery, pairing and heartbeat.
7. Capture and replay one known IR command.
8. Capture and replay one known fixed-code 433.92 MHz ASK/OOK command.

## Pass criteria

- No overheating or brownout.
- Node remains online for 24 hours.
- IR capture/replay succeeds 20 consecutive times.
- RF433 replay succeeds at the target installation distance.
