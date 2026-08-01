#pragma once

#include "lynq/core/Result.h"

#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

namespace lynq::device {

enum class DeviceType {
    Light,
    Switch,
    Fan,
    GarageDoor,
    Gate,
    Fireplace,
    Shade,
    Pump,
    AudioVideo,
    Scene,
    Other
};

struct DeviceRecord {
    std::string id;
    std::string name;
    std::string roomId;
    DeviceType type{DeviceType::Other};
    std::string icon;
    std::string endpointId;
    bool alexaExposed{false};
    bool safetySensitive{false};
    bool enabled{true};
};

class DeviceRegistry {
public:
    Result<void> upsert(DeviceRecord device);
    bool remove(const std::string& deviceId);
    std::optional<DeviceRecord> find(const std::string& deviceId) const;
    std::vector<DeviceRecord> list() const;
    std::vector<DeviceRecord> listByRoom(const std::string& roomId) const;
    std::vector<DeviceRecord> listAlexaExposed() const;
    [[nodiscard]] std::size_t size() const noexcept;

private:
    std::unordered_map<std::string, DeviceRecord> devices_;
};

} // namespace lynq::device
