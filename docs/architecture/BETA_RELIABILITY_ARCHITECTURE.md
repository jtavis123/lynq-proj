# Beta Reliability Architecture

v1.9.0 adds a reliability layer around every local, Scene, automation, cloud and Alexa command.

- Stable command IDs provide idempotency.
- Duplicate commands are suppressed while running and after success.
- Failed commands may retry under a bounded exponential-backoff policy.
- Expiration always overrides retry.
- Every transition creates an execution audit record.
- Hub health combines Wi-Fi, cloud, Node, storage and OTA state into one diagnostic score.

No retry may bypass the safety-policy layer or replay a command already confirmed successful.
