#pragma once

#include "lynq/node/INodeTransport.h"

namespace lynq::hub {

class EspIdfNodeTransport final : public node::INodeTransport {
public:
    Result<void> initialize() override;
    Result<void> startDiscovery() override;
    Result<void> stopDiscovery() override;
    Result<node::PairingResult> pair(const node::PairingRequest& request) override;
    Result<void> unpair(const std::string& nodeId) override;
    void setAdvertisementCallback(AdvertisementCallback callback) override;
    void setHeartbeatCallback(HeartbeatCallback callback) override;

private:
    AdvertisementCallback advertisementCallback_;
    HeartbeatCallback heartbeatCallback_;
};

} // namespace lynq::hub
