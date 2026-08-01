# LYNQ Node Connectivity

## Scope

This release defines the hardware-independent Hub-side foundation for finding, pairing, monitoring, and unpairing LYNQ Nodes.

## Discovery

The production transport will use local-network discovery, initially mDNS and/or authenticated UDP announcements. Discovery advertisements include Node identity, endpoint, firmware, hardware revision, capabilities, and a short-lived pairing nonce.

## Pairing

A discovered Node remains untrusted until the user confirms a pairing code on the Hub. Pairing must establish a unique long-term credential for that Hub/Node relationship. Pairing credentials must not be transmitted in plaintext or logged.

## Heartbeats

Trusted Nodes periodically send heartbeats containing Wi-Fi RSSI, uptime, free heap, restart count, optional temperature, optional battery level, and the latest error. The Hub marks a Node offline when its heartbeat age exceeds the configured timeout.

## Event names

- `node.discovery.started`
- `node.discovery.stopped`
- `node.discovered`
- `node.updated`
- `node.pairing.started`
- `node.paired`
- `node.pairing.failed`
- `node.unpaired`
- `node.heartbeat`
- `node.offline`

## Hardware integration remaining

- mDNS/UDP discovery implementation
- authenticated encrypted command channel
- secure credential storage in NVS
- pairing-code user interface
- heartbeat scheduler on Node One
- reconnection and credential rotation tests
