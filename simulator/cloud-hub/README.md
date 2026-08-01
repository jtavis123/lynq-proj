# Cloud-to-Hub Delivery Simulator

This simulator validates the command lifecycle without physical hardware:

1. Alexa or the cloud API creates a command.
2. The queue applies a unique command ID and expiration time.
3. An online Hub session receives the command.
4. The simulated Hub executes or rejects the command.
5. The Hub sends a success or failure acknowledgement.
6. Repeated command IDs are deduplicated.

Run the automated tests from `software/cloud/command-delivery`:

```bash
npm test
```
