#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace lynq::network {

enum class WifiSecurity {
    Open,
    Wep,
    WpaPersonal,
    Wpa2Personal,
    Wpa3Personal,
    Unknown
};

enum class WifiState {
    Uninitialized,
    Idle,
    Scanning,
    Connecting,
    Connected,
    Provisioning,
    Reconnecting,
    Failed
};

struct WifiNetwork {
    std::string ssid;
    std::int32_t rssi{0};
    WifiSecurity security{WifiSecurity::Unknown};
    bool saved{false};
};

struct WifiCredentials {
    std::string ssid;
    std::string password;
};

struct WifiStatus {
    WifiState state{WifiState::Uninitialized};
    std::string ssid;
    std::string ipAddress;
    std::int32_t rssi{0};
    std::string lastError;
};

} // namespace lynq::network
