# Rev A Node Integration

Rev A connects the existing LYNQ Hub and command architecture to the locked
M5Stack prototype hardware.

## Hardware profile

- AtomS3-Lite controller
- Atomic Port ABC base
- Port A: IR Unit
- Port B: RF433T transmitter
- Port C: RF433R receiver

## Hub flow

1. Hub enters discovery mode.
2. Node advertises `rev-a-m5stack` and its capabilities.
3. User confirms the Node and enters/accepts a pairing code.
4. Hub records the paired Node identity.
5. Node sends periodic health heartbeats.
6. Hub marks the Node offline after the configured timeout.
7. Commands route only to paired, online Nodes with the required capability.

## Hardware limits

Rev A supports IR and 433.92 MHz ASK/OOK fixed-code devices. It does not claim
315, 868 or 915 MHz support and does not clone rolling-code security devices.
