# LYNQ v0.3.0-alpha Update Manifest

## Added

- Node identity, capability, endpoint, health, pairing and heartbeat models
- `INodeTransport` abstraction
- Thread-safe `NodeRegistry`
- `NodeManager` discovery, pairing, heartbeat and offline logic
- ESP-IDF Node transport boundary
- Node connectivity requirements and event definitions
- Host-side Node lifecycle tests

## Hardware-dependent work deferred

- mDNS/UDP implementation
- encrypted local transport
- NVS credential storage
- physical Node One pairing and heartbeat validation
