# Rev A Node Requirements

1. Each Node shall advertise a stable unique identifier.
2. Each Node shall declare the `rev-a-m5stack` hardware profile.
3. Pairing shall require user intent and a minimum six-character code.
4. Unpaired Nodes shall not be accepted as command targets.
5. Paired Nodes shall send periodic health heartbeats.
6. The Hub shall mark a Node offline when heartbeats exceed the timeout.
7. The Node shall report RF433 and IR readiness separately.
8. RF433 capture and replay shall be limited to validated fixed-code ASK/OOK devices.
9. IR capture and replay shall use bounded pulse buffers.
10. The Node shall support signed OTA and rollback before external pilot use.
11. Hardware GPIO assignments shall remain isolated in the AtomS3-Lite board layer.
12. Loss of a Node shall not prevent local Hub operation for other devices.
