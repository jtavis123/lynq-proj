# Deployment and Service Acceptance Test

## Installer

- Reject an incorrect setup token.
- Accept the correct token once.
- Reject token reuse.
- Verify localhost-only default binding.
- Confirm no credentials appear in logs.

## Hub OTA

- Reject modified artifact.
- Reject invalid signature.
- Reject unauthorized downgrade.
- Install valid image into inactive partition.
- Roll back after failed health check.
- Preserve configuration across successful update.

## Node OTA

- Reject wrong hardware profile.
- Update one Node while another remains operational.
- Recover after interrupted transfer.
- Confirm Node version and heartbeat after reboot.

## Backup and restore

- Create encrypted backup.
- Detect incorrect passphrase or corrupted payload.
- Restore into matching schema.
- Migrate one supported older schema.
- Create automatic pre-restore backup.

## Diagnostics and service

- Generate redacted support bundle.
- Capture controlled crash record.
- Confirm no Wi-Fi password or tokens appear.
- Expire technician session at its deadline.
- Verify read-only technician cannot change configuration.
- Verify privileged actions appear in the audit log.
