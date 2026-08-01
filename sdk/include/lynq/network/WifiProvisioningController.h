#pragma once

#include <mutex>
#include <optional>
#include <vector>

#include "lynq/core/EventBus.h"
#include "lynq/network/IWifiService.h"

namespace lynq::network {

class WifiProvisioningController {
public:
    WifiProvisioningController(IWifiService& wifi, EventBus& events);

    Result<void> initialize();
    Result<std::vector<WifiNetwork>> refreshNetworks();
    Result<void> submitCredentials(WifiCredentials credentials);
    Result<void> disconnect();
    Result<void> forgetNetwork();

    [[nodiscard]] WifiStatus status() const;
    [[nodiscard]] std::vector<WifiNetwork> networks() const;

private:
    void onStatusChanged(const WifiStatus& status);

    IWifiService& wifi_;
    EventBus& events_;
    mutable std::mutex mutex_;
    WifiStatus status_;
    std::vector<WifiNetwork> networks_;
};

} // namespace lynq::network
