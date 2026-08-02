# First Real Device Control Architecture

```text
Hub Learning Wizard
  -> Node capture request
  -> IR/RF driver
  -> learned-command repository
  -> Device Database binding
  -> shared command dispatcher
  -> Node replay endpoint
  -> hardware replay driver
  -> acknowledgement
  -> Activity History
```

The session state machine makes the physical demonstration observable and prevents capture, save and replay operations from occurring out of order.
