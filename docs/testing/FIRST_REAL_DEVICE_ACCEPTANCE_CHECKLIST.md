# First Real Device Acceptance Checklist

- [ ] Hub boots without reset loop.
- [ ] Display and touch pass diagnostics.
- [ ] Node pairs and remains online for 30 minutes.
- [ ] Node capability report matches connected IR/RF modules.
- [ ] Capture starts and times out cleanly when no signal is received.
- [ ] One real command is captured.
- [ ] Test replay controls the intended device exactly once.
- [ ] Learned command survives Hub restart.
- [ ] Device button routes to the correct Node.
- [ ] Node returns success or failure acknowledgement.
- [ ] Hub records Activity History.
- [ ] Offline Node produces a visible failure and no false success.
- [ ] Expired or duplicate request does not replay unexpectedly.
