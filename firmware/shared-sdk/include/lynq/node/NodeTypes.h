#pragma once

#include <chrono>
#include <cstdint>
#include <string>
#include <vector>

namespace lynq::node {

enum class NodeState {
    Unknown,
    Discovered,
    Pairing,
    Online,
    Offline,
    Updating,
    Error
};

enum class Capability {
    Rf315Tx,
    Rf315Rx,
    Rf433Tx,
    Rf433Rx,
    IrTx,
    IrRx,
    Relay,
    DigitalInput,
    Battery,
    Temperature,
    Ota
};

struct NodeIdentity {
    std::string id;
    std::string model;
    std::string firmwareVersion;
    std::string hardwareVersion;
};

struct NodeEndpoint {
    std::string address;
    std::uint16_t port{0};
};

struct NodeAdvertisement {
    NodeIdentity identity;
    NodeEndpoint endpoint;
    std::vector<Capability> capabilities;
    std::string pairingNonce;
};

struct NodeHealth {
    std::int32_t wifiRssi{0};
    double temperatureC{0.0};
    double batteryPercent{0.0};
    std::uint64_t uptimeSeconds{0};
    std::uint32_t freeHeapBytes{0};
    std::uint32_t restartCount{0};
    std::string lastError;
};

struct NodeRecord {
    NodeIdentity identity;
    NodeEndpoint endpoint;
    std::vector<Capability> capabilities;
    NodeState state{NodeState::Unknown};
    NodeHealth health;
    std::chrono::steady_clock::time_point lastSeen{};
    bool trusted{false};
};

struct PairingRequest {
    std::string nodeId;
    std::string pairingNonce;
    std::string confirmationCode;
};

struct PairingResult {
    std::string nodeId;
    bool paired{false};
    std::string credentialId;
    std::string error;
};

struct Heartbeat {
    std::string nodeId;
    NodeHealth health;
};

} // namespace lynq::node
