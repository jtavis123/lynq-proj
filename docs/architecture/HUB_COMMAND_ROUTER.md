# Hub Command Router

The Hub Command Router is the single execution boundary for commands originating
from the touchscreen, automations, Alexa, the cloud API, or future mobile apps.

```text
Command source
  -> delivery validation
  -> endpoint lookup
  -> safety policy
  -> duplicate-command check
  -> Node / learned signal / relay / scene executor
  -> acknowledgement
```

## Endpoint bindings

Each user-facing endpoint is bound to one of:

- A learned RF or IR signal on a specific Node
- A relay output on a specific Node
- A Hub scene

The display name shown to Alexa or the user is separate from the internal target ID.

## Idempotency

A completed command ID is remembered and must not be executed twice. Repeated
delivery returns a successful duplicate result.

## Safety

The default policy denies remote execution of safety-sensitive endpoints. Products
such as garage doors, gates, locks and fireplaces require an explicit, reviewed
policy before Alexa or cloud control is enabled.
