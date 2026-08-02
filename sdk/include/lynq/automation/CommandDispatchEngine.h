#pragma once

#include "lynq/core/Result.h"
#include "lynq/device/DeviceDatabase.h"

#include <cstdint>
#include <string>
#include <vector>

namespace lynq::automation {

struct DispatchRequest {
    std::string requestId;
    std::string deviceId;
    std::string commandName;
    std::uint64_t expiresAtEpochMs{0};
};

struct DispatchResult {
    std::string requestId;
    bool success{false};
    std::string nodeId;
    std::string learnedCommandId;
    std::string detail;
};

class ILearnedCommandExecutor {
public:
    virtual ~ILearnedCommandExecutor() = default;
    virtual Result<void> execute(
        const std::string& nodeId,
        const std::string& learnedCommandId) = 0;
};

class CommandDispatchEngine {
public:
    CommandDispatchEngine(
        const device::DeviceDatabase& database,
        ILearnedCommandExecutor& executor);

    DispatchResult dispatch(
        const DispatchRequest& request,
        std::uint64_t nowEpochMs);

private:
    const device::DeviceDatabase& database_;
    ILearnedCommandExecutor& executor_;
};

} // namespace lynq::automation
