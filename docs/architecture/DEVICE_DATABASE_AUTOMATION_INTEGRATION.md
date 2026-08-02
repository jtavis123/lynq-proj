# Device Database and Automation Integration

The Device Database connects user-facing devices to learned RF or IR commands.

```text
Device
  -> friendly command binding
  -> learned command ID
  -> assigned Node
  -> Hub command dispatch
  -> Node replay
  -> execution result
```

Scenes and automations reference device IDs and friendly command names. They do
not contain raw RF or IR timing data. This keeps user configuration stable if a
command is relearned or moved to another Node.

## Persistence

The Hub stores versioned JSON documents for devices and command bindings.
Configuration writes must be atomic and must preserve the last known good copy.

## Execution

All device-button, scene, schedule, Alexa and remote commands use the same
dispatch path. Expired requests and unavailable devices are rejected before
contacting a Node.
