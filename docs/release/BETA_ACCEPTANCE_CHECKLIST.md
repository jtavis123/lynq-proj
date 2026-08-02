# LYNQ v2.0.0-beta.1 Acceptance Checklist

## Hub

- [ ] Factory firmware backup completed
- [ ] Hub flashes without error
- [ ] Display colors and orientation correct
- [ ] Touch coordinates and navigation correct
- [ ] Wi-Fi reconnects after access-point restart
- [ ] BLE discovery starts successfully
- [ ] Settings persist after restart
- [ ] Local UI remains responsive during cloud loss

## Node

- [ ] Node flashes without error
- [ ] Node pairs successfully
- [ ] Heartbeat remains stable for 24 hours
- [ ] Offline state appears after heartbeat timeout
- [ ] Node reconnects without re-pairing
- [ ] IR capture and replay pass
- [ ] RF433 capture and replay pass

## Reliability

- [ ] Duplicate command ID executes only once
- [ ] Expired command does not execute
- [ ] Retry count remains bounded
- [ ] Failed execution appears in Activity
- [ ] Recovery procedure restores service

## Integrated demonstration

- [ ] Device learned
- [ ] Device command executed from Hub
- [ ] Scene executed
- [ ] Automation executed
- [ ] Simulated Alexa directive executed
- [ ] Acknowledgement recorded
- [ ] Activity history recorded
