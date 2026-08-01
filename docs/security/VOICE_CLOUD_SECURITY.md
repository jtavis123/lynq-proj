# Voice and Cloud Security

- Smart-home account linking uses OAuth 2.0 authorization-code grant.
- PKCE with S256 is supported by the authorization service.
- Alexa access tokens are validated for every directive.
- Hub connections are outbound-only and mutually authenticated.
- Commands carry unique message IDs and expire quickly.
- Duplicate message IDs are rejected.
- Hub, Node and command ownership are checked before execution.
- Secrets and signing keys are stored in managed secret stores, never Git.
- Garage, gate, lock, fireplace and other safety-sensitive classes require additional policy controls and must not be exposed as unrestricted generic power devices.
- Logs must not contain tokens, passwords, learned waveform payloads or customer-identifying data beyond approved identifiers.
