#pragma once

#include <string>

namespace lynq::cloud {

enum class CloudAction { Activate, Deactivate };

struct CloudCommand {
    std::string userId;
    std::string endpointId;
    std::string hubId;
    std::string nodeId;
    std::string commandId;
    std::string deviceClass;
    CloudAction action{CloudAction::Activate};
    std::string messageId;
    std::string correlationToken;
};

struct CloudCommandResult {
    bool accepted{false};
    std::string errorType;
    std::string message;
};

} // namespace lynq::cloud
