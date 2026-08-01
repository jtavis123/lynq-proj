#include "HubWifiService.hpp"

#include "esp_log.h"

#include <utility>

namespace {
constexpr const char* kTag = "LYNQ_WIFI";
}

namespace lynq::hub {

Result<void> HubWifiService::initialize() {
    ESP_LOGI(kTag, "Initializing Hub Wi-Fi service boundary");
    updateStatus(network::WifiStatus{network::WifiState::Idle});
    return Result<void>::success();
}

Result<std::vector<network::WifiNetwork>> HubWifiService::scan() {
    ESP_LOGI(kTag, "Wi-Fi scan requested");
    updateStatus(network::WifiStatus{network::WifiState::Scanning});

    // The Waveshare/ESP-IDF scan call is connected during physical bring-up.
    // Returning an empty list is deliberate until radio validation is complete.
    updateStatus(network::WifiStatus{network::WifiState::Idle});
    return Result<std::vector<network::WifiNetwork>>::success({});
}

Result<void> HubWifiService::connect(const network::WifiCredentials& credentials) {
    if (credentials.ssid.empty()) {
        return Result<void>::failure(ErrorCode::InvalidArgument, "SSID is required");
    }
    pendingCredentials_ = credentials;
    ESP_LOGI(kTag, "Connection requested for SSID: %s", credentials.ssid.c_str());
    updateStatus(network::WifiStatus{network::WifiState::Connecting, credentials.ssid});

    // esp_wifi_set_config / esp_wifi_connect are wired during hardware bring-up.
    return Result<void>::success();
}

Result<void> HubWifiService::disconnect() {
    ESP_LOGI(kTag, "Disconnect requested");
    updateStatus(network::WifiStatus{network::WifiState::Idle});
    return Result<void>::success();
}

Result<void> HubWifiService::forgetNetwork() {
    pendingCredentials_.reset();
    ESP_LOGI(kTag, "Saved Wi-Fi profile cleared");
    updateStatus(network::WifiStatus{network::WifiState::Provisioning});
    return Result<void>::success();
}

network::WifiStatus HubWifiService::status() const {
    std::lock_guard lock(mutex_);
    return status_;
}

void HubWifiService::setStatusCallback(StatusCallback callback) {
    std::lock_guard lock(mutex_);
    callback_ = std::move(callback);
}

void HubWifiService::updateStatus(network::WifiStatus status) {
    StatusCallback callback;
    network::WifiStatus snapshot;
    {
        std::lock_guard lock(mutex_);
        status_ = std::move(status);
        snapshot = status_;
        callback = callback_;
    }
    if (callback) callback(snapshot);
}

} // namespace lynq::hub
