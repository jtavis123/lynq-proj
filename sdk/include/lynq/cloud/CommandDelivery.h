#pragma once

#include <cstdint>
#include <map>
#include <string>

namespace lynq::cloud {

enum class DeliveryState {
    Queued,
    Delivering,
    Completed,
    Failed,
    Expired
};

struct DeliveredCommand {
    std::string commandId;
    std::string correlationId;
    std::string hubId;
    std::string endpointId;
    std::string action;
    std::map<std::string, std::string> parameters;
    std::uint64_t createdAtEpochMs{0};
    std::uint64_t expiresAtEpochMs{0};
    std::uint32_t attempt{0};
};

struct CommandAcknowledgement {
    std::string commandId;
    bool success{false};
    std::string detail;
    std::uint64_t completedAtEpochMs{0};
};

} // namespace lynq::cloud
