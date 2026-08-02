# Device Learning Requirements

1. The wizard shall require a device and compatible Node before capture.
2. Capture shall have a bounded timeout and allow cancellation.
3. Captured data shall record transport, timing data, carrier information and fingerprint.
4. A command shall be replay-tested before saving.
5. Command names shall be validated and normalized.
6. Learned commands shall have stable IDs and creation timestamps.
7. The repository shall support lookup by command ID.
8. Rev A RF learning shall be limited to supported 433.92 MHz ASK/OOK fixed-code signals.
9. Rolling-code secrets shall not be stored or reproduced.
10. Hardware capture remains behind RF433 and IR adapter interfaces.
