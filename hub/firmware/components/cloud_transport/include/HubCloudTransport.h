#pragma once

#include "lynq/cloud/CommandDelivery.h"
#include "lynq/core/Result.h"

#include <functional>
#include <string>

namespace lynq::hub {

class HubCloudTransport {
public:
    using CommandCallback = std::function<void(const cloud::DeliveredCommand&)>;

    Result<void> initialize(std::string hubId);
    Result<void> connect();
    Result<void> disconnect();
    Result<void> sendHeartbeat();
    Result<void> acknowledge(const cloud::CommandAcknowledgement& acknowledgement);
    void setCommandCallback(CommandCallback callback);

    [[nodiscard]] bool connected() const noexcept;

private:
    std::string hubId_;
    bool connected_{false};
    CommandCallback commandCallback_;
};

} // namespace lynq::hub
