# System Architecture

```text
Alexa / Mobile / Touchscreen / Schedules
                  |
             Command Bus
                  |
             LYNQ Hub
                  |
       Secure local network protocol
                  |
              LYNQ Nodes
                  |
              RF / IR / Relay
```

The Hub is authoritative for users, rooms, devices, scenes, schedules, and configuration. Nodes perform timing-sensitive RF/IR work and maintain a local cache of assigned commands.
