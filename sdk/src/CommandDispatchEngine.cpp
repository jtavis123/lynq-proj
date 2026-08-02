#include "lynq/automation/CommandDispatchEngine.h"

namespace lynq::automation {

CommandDispatchEngine::CommandDispatchEngine(
    const device::DeviceDatabase& database,
    ILearnedCommandExecutor& executor)
    : database_(database), executor_(executor) {}

DispatchResult CommandDispatchEngine::dispatch(
    const DispatchRequest& request,
    std::uint64_t nowEpochMs) {
    DispatchResult result;
    result.requestId = request.requestId;

    if (request.requestId.empty() ||
        request.deviceId.empty() ||
        request.commandName.empty()) {
        result.detail = "Request ID, device ID and command name are required.";
        return result;
    }

    if (request.expiresAtEpochMs != 0 &&
        request.expiresAtEpochMs <= nowEpochMs) {
        result.detail = "Command request expired.";
        return result;
    }

    const auto device = database_.find(request.deviceId);
    if (!device || !device->enabled) {
        result.detail = "Device is unavailable.";
        return result;
    }

    for (const auto& binding : device->commands) {
        if (!binding.enabled ||
            binding.commandName != request.commandName) {
            continue;
        }

        const auto executed = executor_.execute(
            binding.nodeId,
            binding.learnedCommandId);

        result.nodeId = binding.nodeId;
        result.learnedCommandId = binding.learnedCommandId;
        result.success = executed.ok();
        result.detail = executed.ok()
            ? "Command dispatched."
            : executed.message();
        return result;
    }

    result.detail = "Command binding was not found.";
    return result;
}

} // namespace lynq::automation
