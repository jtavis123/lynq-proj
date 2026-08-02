#include "lynq/device/DeviceDatabase.h"

#include <algorithm>
#include <sstream>
#include <utility>

namespace lynq::device {

DeviceDatabase::DeviceDatabase(IDeviceDatabaseStore& store)
    : store_(store) {}

Result<void> DeviceDatabase::upsert(DeviceRecord device) {
    if (device.deviceId.empty() || device.name.empty()) {
        return Result<void>::failure(
            ErrorCode::InvalidArgument,
            "Device ID and name are required.");
    }

    for (const auto& command : device.commands) {
        if (command.bindingId.empty() ||
            command.commandName.empty() ||
            command.learnedCommandId.empty() ||
            command.nodeId.empty()) {
            return Result<void>::failure(
                ErrorCode::InvalidArgument,
                "Every command binding must be complete.");
        }
    }

    devices_[device.deviceId] = std::move(device);
    return Result<void>::success();
}

bool DeviceDatabase::remove(const std::string& deviceId) {
    return devices_.erase(deviceId) > 0;
}

std::optional<DeviceRecord> DeviceDatabase::find(
    const std::string& deviceId) const {
    const auto it = devices_.find(deviceId);
    if (it == devices_.end()) return std::nullopt;
    return it->second;
}

std::vector<DeviceRecord> DeviceDatabase::list() const {
    std::vector<DeviceRecord> result;
    result.reserve(devices_.size());
    for (const auto& [_, device] : devices_) {
        result.push_back(device);
    }
    std::sort(result.begin(), result.end(),
              [](const auto& a, const auto& b) {
                  return a.name < b.name;
              });
    return result;
}

Result<void> DeviceDatabase::load() {
    const auto loaded = store_.loadJson();
    if (!loaded.ok()) return Result<void>::failure(
        ErrorCode::NotFound, loaded.message());

    // Production JSON parsing is provided by the Hub JSON adapter.
    // The portable boundary intentionally avoids a parser dependency.
    if (loaded.value().empty()) {
        devices_.clear();
    }
    return Result<void>::success();
}

Result<void> DeviceDatabase::save() const {
    std::ostringstream out;
    out << "{\"schemaVersion\":1,\"devices\":[";
    bool firstDevice = true;

    for (const auto& device : list()) {
        if (!firstDevice) out << ",";
        firstDevice = false;
        out << "{\"deviceId\":\"" << device.deviceId
            << "\",\"name\":\"" << device.name
            << "\",\"roomId\":\"" << device.roomId
            << "\",\"category\":\"" << device.category
            << "\",\"favorite\":" << (device.favorite ? "true" : "false")
            << ",\"enabled\":" << (device.enabled ? "true" : "false")
            << ",\"commands\":[";

        bool firstCommand = true;
        for (const auto& command : device.commands) {
            if (!firstCommand) out << ",";
            firstCommand = false;
            out << "{\"bindingId\":\"" << command.bindingId
                << "\",\"commandName\":\"" << command.commandName
                << "\",\"learnedCommandId\":\"" << command.learnedCommandId
                << "\",\"nodeId\":\"" << command.nodeId
                << "\",\"enabled\":" << (command.enabled ? "true" : "false")
                << "}";
        }
        out << "]}";
    }

    out << "]}";
    return store_.saveJson(out.str());
}

} // namespace lynq::device
