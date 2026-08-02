# Device Database and Automation Test Plan

## Host tests

- Add and update a device.
- Reject incomplete command bindings.
- Save versioned device JSON.
- Resolve a friendly command to the correct Node and learned-command ID.
- Reject expired requests.
- Reject unknown commands.
- Run a scene through the same dispatch path.

## Physical validation

1. Learn an IR or supported RF433 command.
2. Bind it to a device button.
3. Restart the Hub and confirm the binding remains.
4. Execute the button and verify Node replay.
5. Add the button to a Scene.
6. Run the Scene and verify the same replay path.
7. Schedule the Scene and verify one execution at the expected time.
8. Disconnect the Node and confirm a visible failure without duplicate replay.
