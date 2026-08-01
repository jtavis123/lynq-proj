#pragma once

#include "lynq/command/CommandRouter.h"
#include "lynq/cloud/CommandDelivery.h"
#include "lynq/core/Result.h"

namespace lynq::hub {

class HubCommandRouter {
public:
    explicit HubCommandRouter(command::CommandRouter& router);

    cloud::CommandAcknowledgement handleCloudCommand(
        const cloud::DeliveredCommand& command,
        std::uint64_t nowEpochMs);

private:
    command::CommandRouter& router_;
};

} // namespace lynq::hub
