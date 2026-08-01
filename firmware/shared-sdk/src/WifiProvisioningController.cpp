#include "lynq/network/WifiProvisioningController.h"

#include <utility>

namespace lynq::network {

WifiProvisioningController::WifiProvisioningController(IWifiService& wifi, EventBus& events)
    : wifi_(wifi), events_(events) {
    wifi_.setStatusCallback([this](const WifiStatus& status) { onStatusChanged(status); });
}

Result<void> WifiProvisioningController::initialize() {
    auto result = wifi_.initialize();
    if (!result.ok()) return result;
    onStatusChanged(wifi_.status());
    return Result<void>::success();
}

Result<std::vector<WifiNetwork>> WifiProvisioningController::refreshNetworks() {
    auto result = wifi_.scan();
    if (!result.ok()) return result;
    {
        std::lock_guard lock(mutex_);
        networks_ = result.value();
    }
    events_.publish(Event{"wifi.scan.completed", "WifiProvisioningController", std::to_string(result.value().size())});
    return result;
}

Result<void> WifiProvisioningController::submitCredentials(WifiCredentials credentials) {
    if (credentials.ssid.empty()) {
        return Result<void>::failure(ErrorCode::InvalidArgument, "SSID is required");
    }
    events_.publish(Event{"wifi.connect.requested", "WifiProvisioningController", credentials.ssid});
    return wifi_.connect(credentials);
}

Result<void> WifiProvisioningController::disconnect() {
    return wifi_.disconnect();
}

Result<void> WifiProvisioningController::forgetNetwork() {
    auto result = wifi_.forgetNetwork();
    if (result.ok()) {
        events_.publish(Event{"wifi.network.forgotten", "WifiProvisioningController", {}});
    }
    return result;
}

WifiStatus WifiProvisioningController::status() const {
    std::lock_guard lock(mutex_);
    return status_;
}

std::vector<WifiNetwork> WifiProvisioningController::networks() const {
    std::lock_guard lock(mutex_);
    return networks_;
}

void WifiProvisioningController::onStatusChanged(const WifiStatus& status) {
    {
        std::lock_guard lock(mutex_);
        status_ = status;
    }
    events_.publish(Event{"wifi.status.changed", "WifiProvisioningController", status.ssid});
}

} // namespace lynq::network
