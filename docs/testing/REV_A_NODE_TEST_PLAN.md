# Rev A Node Test Plan

## Host validation

- Announcement profile is correct.
- Invalid pairing codes are rejected.
- Heartbeats require pairing.
- Offline timeout changes Node status.
- Capability flags match installed modules.

## Physical validation

- AtomS3-Lite enumerates over USB.
- RGB status and front button work.
- Port A IR Unit receives and transmits a known command.
- Port B RF433T transmits a known fixed-code command.
- Port C RF433R captures the same remote consistently.
- Hub discovers and pairs the Node.
- Heartbeats remain stable for 24 hours.
- Power cycle preserves pairing.
- OTA rollback recovers from an invalid image.
