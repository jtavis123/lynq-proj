# LYNQ Deployment and Service Platform

## Scope

This subsystem makes installation, upgrades, backup, diagnostics and service
repeatable without weakening local-first operation.

## Components

1. **Secure local web installer**
   - Binds to localhost by default.
   - Uses a one-time setup token.
   - Disables browser caching.
   - Applies restrictive browser security headers.
   - Never logs the setup token.

2. **Hub OTA**
   - Signed manifest and SHA-256 verification.
   - Anti-downgrade policy.
   - A/B firmware partitions.
   - Post-boot health check.
   - Automatic rollback after failed health confirmation.

3. **Hub-managed Node updates**
   - Hub verifies the Node image before distribution.
   - Hardware profile must match.
   - Nodes update individually, not simultaneously.
   - Hub records progress and final acknowledgement.

4. **Configuration backup and restore**
   - Versioned manifest.
   - Integrity digest.
   - Encrypted export.
   - Restore validation before applying changes.
   - Automatic pre-restore snapshot.

5. **Diagnostics and support**
   - Hardware inventory.
   - Firmware and partition status.
   - Network state without credentials.
   - Node health and last heartbeat.
   - Update history.
   - Redacted support bundle.

6. **Crash reporting**
   - Reset reason and compact panic summary.
   - Stack fingerprint rather than sensitive memory dumps.
   - Local retention limit.
   - Explicit opt-in before cloud upload.

7. **Technician service mode**
   - Time-limited session.
   - Separate read, update and configuration-write permissions.
   - Visible banner while active.
   - Automatic expiration and manual revocation.
   - Audit record for every privileged action.
