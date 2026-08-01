# Cloud-to-Hub Command Delivery

## Goals

- The Hub always initiates the outbound cloud connection.
- No inbound port forwarding is required.
- Commands are uniquely identified and idempotent.
- Commands expire quickly to prevent stale actions.
- The Hub acknowledges success or failure.
- Local RF/IR execution remains local after a valid command reaches the Hub.

## Lifecycle

```text
Alexa Lambda
  -> LYNQ command API
  -> command queue
  -> authenticated Hub session
  -> Hub command router
  -> Node
  -> RF/IR/relay action
  -> acknowledgement
  -> Alexa response / activity record
```

## Delivery rules

- A `commandId` must be globally unique.
- Duplicate IDs return the original record and are not executed twice.
- Commands have a short TTL.
- Offline Hubs retain commands only until TTL expiration.
- The Hub must reject commands addressed to another Hub.
- Safety-sensitive commands may require an additional local policy check.
