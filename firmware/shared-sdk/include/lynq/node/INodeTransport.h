#pragma once

#include <functional>
#include <vector>

#include "lynq/core/Result.h"
#include "lynq/node/NodeTypes.h"

namespace lynq::node {

class INodeTransport {
public:
    using AdvertisementCallback = std::function<void(const NodeAdvertisement&)>;
    using HeartbeatCallback = std::function<void(const Heartbeat&)>;

    virtual ~INodeTransport() = default;
    virtual Result<void> initialize() = 0;
    virtual Result<void> startDiscovery() = 0;
    virtual Result<void> stopDiscovery() = 0;
    virtual Result<PairingResult> pair(const PairingRequest& request) = 0;
    virtual Result<void> unpair(const std::string& nodeId) = 0;
    virtual void setAdvertisementCallback(AdvertisementCallback callback) = 0;
    virtual void setHeartbeatCallback(HeartbeatCallback callback) = 0;
};

} // namespace lynq::node
