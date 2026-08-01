# Learning Engine Architecture

The portable learning engine is separated from hardware-specific radio drivers.

```text
Hub Learn UI
    |
LYNQ Protocol
    |
Node LearningController
    |
ILearningRadio
    |
ESP-IDF RF/IR Driver
```

`LearningController` owns workflow state, events, cancellation and command
construction. `ILearningRadio` owns timing-sensitive capture and replay.

Initial events:

- `learning.started`
- `learning.captured`
- `learning.failed`
- `learning.cancelled`
- `command.transmit.started`
- `command.transmit.completed`
- `command.transmit.failed`
