#pragma once

#include <string>
#include <vector>

namespace lynq::device {

struct DeviceCommandBinding {
    std::string bindingId;
    std::string deviceId;
    std::string commandName;
    std::string learnedCommandId;
    std::string nodeId;
    bool enabled{true};
};

struct DeviceRecord {
    std::string deviceId;
    std::string name;
    std::string roomId;
    std::string category;
    bool favorite{false};
    bool enabled{true};
    std::vector<DeviceCommandBinding> commands;
};

} // namespace lynq::device
