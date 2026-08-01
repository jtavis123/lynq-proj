#include "EspIdfNodeTransport.h"

namespace lynq::hub {

Result<void> EspIdfNodeTransport::initialize() {
    // Hardware integration point: mDNS/UDP discovery and secure local transport.
    return Result<void>::success();
}

Result<void> EspIdfNodeTransport::startDiscovery() {
    return Result<void>::failure(ErrorCode::Unsupported,
                                 "ESP-IDF Node discovery transport awaits hardware integration");
}

Result<void> EspIdfNodeTransport::stopDiscovery() { return Result<void>::success(); }

Result<node::PairingResult> EspIdfNodeTransport::pair(const node::PairingRequest&) {
    return Result<node::PairingResult>::failure(
        ErrorCode::Unsupported, "Secure Node pairing awaits hardware integration");
}

Result<void> EspIdfNodeTransport::unpair(const std::string&) {
    return Result<void>::failure(ErrorCode::Unsupported,
                                 "Node credential storage awaits hardware integration");
}

void EspIdfNodeTransport::setAdvertisementCallback(AdvertisementCallback callback) {
    advertisementCallback_ = std::move(callback);
}

void EspIdfNodeTransport::setHeartbeatCallback(HeartbeatCallback callback) {
    heartbeatCallback_ = std::move(callback);
}

} // namespace lynq::hub
