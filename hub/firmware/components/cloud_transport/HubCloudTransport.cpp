#include "HubCloudTransport.h"

namespace lynq::hub {

Result<void> HubCloudTransport::initialize(std::string hubId) {
    if (hubId.empty()) {
        return Result<void>::failure(ErrorCode::InvalidArgument, "Hub ID is required.");
    }
    hubId_ = std::move(hubId);
    return Result<void>::success();
}

Result<void> HubCloudTransport::connect() {
    if (hubId_.empty()) {
        return Result<void>::failure(ErrorCode::InvalidArgument,
                                     "Cloud transport must be initialized first.");
    }

    // Integration boundary for a mutually authenticated outbound TLS session.
    // The final transport can use AWS IoT Core MQTT/WebSockets or a dedicated
    // LYNQ WebSocket gateway without changing the command-delivery model.
    connected_ = true;
    return Result<void>::success();
}

Result<void> HubCloudTransport::disconnect() {
    connected_ = false;
    return Result<void>::success();
}

Result<void> HubCloudTransport::sendHeartbeat() {
    if (!connected_) {
        return Result<void>::failure(ErrorCode::NotConnected, "Cloud session is offline.");
    }
    return Result<void>::success();
}

Result<void> HubCloudTransport::acknowledge(
    const cloud::CommandAcknowledgement&) {
    if (!connected_) {
        return Result<void>::failure(ErrorCode::NotConnected, "Cloud session is offline.");
    }
    return Result<void>::success();
}

void HubCloudTransport::setCommandCallback(CommandCallback callback) {
    commandCallback_ = std::move(callback);
}

bool HubCloudTransport::connected() const noexcept {
    return connected_;
}

} // namespace lynq::hub
