# Pre-Beta Regression Checklist

## Hub
- Cold boot 20 consecutive times.
- Verify display, touch, Wi-Fi, storage and PSRAM.
- Verify local control with cloud disconnected.
- Verify configuration survives restart and interrupted writes.

## Node
- Pair, restart and reconnect both Rev A Nodes.
- Verify heartbeat, offline detection and capability reporting.
- Run 100 IR replays and 100 supported RF433 replays.
- Verify duplicate command suppression.

## End-to-end
- Learn, test, save and replay one IR command.
- Learn, test, save and replay one fixed-code RF433 command.
- Execute the same commands manually, from a Scene and from an automation.
- Simulate Alexa/cloud delivery and acknowledgement.
- Disconnect and reconnect Hub and Node during execution.
- Confirm expired commands never replay.

## Release gate
- No critical defects open.
- All automated tests pass.
- Factory backup exists for each hardware type.
- Known limitations are documented.
