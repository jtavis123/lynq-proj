# Persistent JSON Configuration

Hub configuration is stored as versioned JSON documents behind the portable
`JsonConfigurationStore` interface.

Expected documents:

- `rooms.json`
- `devices.json`
- `scenes.json`
- `automations.json`
- `hub-settings.json`
- `node-bindings.json`

The storage implementation must use atomic replacement, validation, backups and
schema migration before production use. Credentials and private keys are not
stored in these JSON documents.
