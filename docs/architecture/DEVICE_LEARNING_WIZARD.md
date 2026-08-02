# Device Learning Wizard

The learning wizard hides protocol details from the user and enforces a safe sequence:

1. Select or create a device.
2. Select a compatible Node.
3. Choose IR or supported 433.92 MHz fixed-code RF.
4. Capture the original remote command.
5. Replay it immediately for validation.
6. Give the command a friendly name.
7. Save it to the learned-command repository.

A failed replay is not saved as a verified command. Rolling-code signals may be detected but are not cloned.
