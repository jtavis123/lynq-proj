#include "HubCommandRouter.h"

namespace lynq::hub {

HubCommandRouter::HubCommandRouter(command::CommandRouter& router)
    : router_(router) {}

cloud::CommandAcknowledgement HubCommandRouter::handleCloudCommand(
    const cloud::DeliveredCommand& command,
    std::uint64_t nowEpochMs) {

    command::CommandRequest request;
    request.commandId = command.commandId;
    request.endpointId = command.endpointId;
    request.action = command.action;
    request.parameters = command.parameters;
    request.source = command::CommandSource::CloudApi;
    request.expiresAtEpochMs = command.expiresAtEpochMs;

    const auto result = router_.route(request, nowEpochMs);

    cloud::CommandAcknowledgement acknowledgement;
    acknowledgement.commandId = command.commandId;
    acknowledgement.success = result.success;
    acknowledgement.detail = result.detail;
    acknowledgement.completedAtEpochMs = nowEpochMs;
    return acknowledgement;
}

} // namespace lynq::hub
