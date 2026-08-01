#pragma once

#include <functional>
#include <vector>

#include "lynq/core/Result.h"
#include "lynq/network/WifiTypes.h"

namespace lynq::network {

class IWifiService {
public:
    using StatusCallback = std::function<void(const WifiStatus&)>;

    virtual ~IWifiService() = default;
    virtual Result<void> initialize() = 0;
    virtual Result<std::vector<WifiNetwork>> scan() = 0;
    virtual Result<void> connect(const WifiCredentials& credentials) = 0;
    virtual Result<void> disconnect() = 0;
    virtual Result<void> forgetNetwork() = 0;
    virtual WifiStatus status() const = 0;
    virtual void setStatusCallback(StatusCallback callback) = 0;
};

} // namespace lynq::network
