#include "lynq/device/DeviceRegistry.h"

#include <algorithm>
#include <utility>

namespace lynq::device {

Result<void> DeviceRegistry::upsert(DeviceRecord device) {
    if (device.id.empty() || device.name.empty() || device.endpointId.empty()) {
        return Result<void>::failure(
            ErrorCode::InvalidArgument,
            "Device ID, name and endpoint ID are required.");
    }
    devices_[device.id] = std::move(device);
    return Result<void>::success();
}

bool DeviceRegistry::remove(const std::string& deviceId) {
    return devices_.erase(deviceId) > 0;
}

std::optional<DeviceRecord> DeviceRegistry::find(const std::string& deviceId) const {
    const auto it = devices_.find(deviceId);
    if (it == devices_.end()) return std::nullopt;
    return it->second;
}

std::vector<DeviceRecord> DeviceRegistry::list() const {
    std::vector<DeviceRecord> result;
    result.reserve(devices_.size());
    for (const auto& [_, device] : devices_) result.push_back(device);
    std::sort(result.begin(), result.end(), [](const auto& a, const auto& b) {
        return a.name < b.name;
    });
    return result;
}

std::vector<DeviceRecord> DeviceRegistry::listByRoom(const std::string& roomId) const {
    std::vector<DeviceRecord> result;
    for (const auto& [_, device] : devices_) {
        if (device.roomId == roomId) result.push_back(device);
    }
    std::sort(result.begin(), result.end(), [](const auto& a, const auto& b) {
        return a.name < b.name;
    });
    return result;
}

std::vector<DeviceRecord> DeviceRegistry::listAlexaExposed() const {
    std::vector<DeviceRecord> result;
    for (const auto& [_, device] : devices_) {
        if (device.enabled && device.alexaExposed) result.push_back(device);
    }
    std::sort(result.begin(), result.end(), [](const auto& a, const auto& b) {
        return a.name < b.name;
    });
    return result;
}

std::size_t DeviceRegistry::size() const noexcept {
    return devices_.size();
}

} // namespace lynq::device
