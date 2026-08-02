#pragma once

#include "lynq/core/Result.h"

#include <cstdint>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

namespace lynq::node {

enum class RevACapability {
    Wifi,
    Ble,
    IrTransmit,
    IrReceive,
    Rf433Transmit,
    Rf433Receive,
    Ota
};

struct RevANodeAnnouncement {
    std::string nodeId;
    std::string displayName;
    std::string hardwareProfile{"rev-a-m5stack"};
    std::string firmwareVersion;
    std::vector<RevACapability> capabilities;
};

struct RevANodeHeartbeat {
    std::string nodeId;
    std::uint64_t observedAtEpochMs{0};
    std::uint64_t uptimeSeconds{0};
    int wifiRssiDbm{0};
    std::uint32_t freeHeapBytes{0};
    bool rf433Ready{false};
    bool irReady{false};
};

struct RevANodeStatus {
    RevANodeAnnouncement announcement;
    RevANodeHeartbeat heartbeat;
    bool paired{false};
    bool online{false};
};

class IRevANodeTransport {
public:
    virtual ~IRevANodeTransport() = default;
    virtual Result<void> beginDiscovery() = 0;
    virtual Result<void> stopDiscovery() = 0;
    virtual Result<void> requestPairing(const std::string& nodeId,
                                        const std::string& pairingCode) = 0;
    virtual Result<void> sendPing(const std::string& nodeId) = 0;
};

class RevANodeCoordinator {
public:
    explicit RevANodeCoordinator(IRevANodeTransport& transport,
                                 std::uint64_t offlineAfterMs = 45000);

    Result<void> startDiscovery();
    Result<void> stopDiscovery();
    Result<void> observeAnnouncement(RevANodeAnnouncement announcement);
    Result<void> pair(const std::string& nodeId,
                      const std::string& pairingCode);
    Result<void> ingestHeartbeat(RevANodeHeartbeat heartbeat);
    void evaluateOnlineState(std::uint64_t nowEpochMs);

    [[nodiscard]] std::optional<RevANodeStatus> find(
        const std::string& nodeId) const;
    [[nodiscard]] std::vector<RevANodeStatus> list() const;

private:
    IRevANodeTransport& transport_;
    std::uint64_t offlineAfterMs_;
    std::unordered_map<std::string, RevANodeStatus> nodes_;
};

} // namespace lynq::node
