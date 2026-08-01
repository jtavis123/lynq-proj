#pragma once

#include <chrono>
#include <string>
#include <vector>

#include "lynq/core/EventBus.h"
#include "lynq/core/Result.h"
#include "lynq/node/INodeTransport.h"
#include "lynq/node/NodeRegistry.h"

namespace lynq::node {

class NodeManager {
public:
    NodeManager(INodeTransport& transport, NodeRegistry& registry, EventBus& events);

    Result<void> initialize();
    Result<void> startDiscovery();
    Result<void> stopDiscovery();
    Result<PairingResult> pair(const PairingRequest& request);
    Result<void> unpair(const std::string& nodeId);
    std::size_t markStaleNodesOffline(std::chrono::steady_clock::time_point now,
                                      std::chrono::seconds timeout);

    [[nodiscard]] std::vector<NodeRecord> nodes() const;

private:
    void onAdvertisement(const NodeAdvertisement& advertisement);
    void onHeartbeat(const Heartbeat& heartbeat);

    INodeTransport& transport_;
    NodeRegistry& registry_;
    EventBus& events_;
};

} // namespace lynq::node
