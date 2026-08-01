# Hub Cloud Transport Security

## Required controls

- TLS 1.2 or newer.
- Hub-specific credentials provisioned during manufacturing or onboarding.
- Credential rotation and revocation.
- Outbound-only Hub connections.
- Short-lived cloud authorization for user-originated commands.
- Strict Hub and endpoint ownership validation.
- Command IDs, timestamps and expiration enforcement.
- Replay protection and idempotency.
- Redacted logs: never log access tokens, Wi-Fi passwords, private keys or complete certificates.
- Signed Hub and Node OTA packages.

## Safety-sensitive endpoints

Garage doors, gates, locks, fireplaces and similar endpoints must be explicitly
classified. Voice exposure and remote execution require product-specific policy,
audit logging and user-visible configuration.
