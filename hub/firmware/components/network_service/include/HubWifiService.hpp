#pragma once

#include <mutex>
#include <optional>

#include "lynq/network/IWifiService.h"

namespace lynq::hub {

// ESP-IDF adapter boundary for Hub Wi-Fi. The hardware-specific implementation
// is intentionally isolated here so the provisioning controller remains portable.
class HubWifiService final : public network::IWifiService {
public:
    Result<void> initialize() override;
    Result<std::vector<network::WifiNetwork>> scan() override;
    Result<void> connect(const network::WifiCredentials& credentials) override;
    Result<void> disconnect() override;
    Result<void> forgetNetwork() override;
    network::WifiStatus status() const override;
    void setStatusCallback(StatusCallback callback) override;

private:
    void updateStatus(network::WifiStatus status);

    mutable std::mutex mutex_;
    network::WifiStatus status_;
    StatusCallback callback_;
    std::optional<network::WifiCredentials> pendingCredentials_;
};

} // namespace lynq::hub
