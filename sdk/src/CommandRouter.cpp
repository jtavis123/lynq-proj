#include "lynq/command/CommandRouter.h"

#include <utility>

namespace lynq::command {

Result<void> DefaultSafetyPolicy::authorize(
    const CommandRequest& request,
    const EndpointBinding& binding) const {

    const bool remoteSource =
        request.source == CommandSource::Alexa ||
        request.source == CommandSource::CloudApi;

    if (remoteSource && !binding.remoteControlAllowed) {
        return Result<void>::failure(
            ErrorCode::AccessDenied,
            "Remote control is disabled for this endpoint.");
    }

    if (remoteSource && binding.safetySensitive) {
        return Result<void>::failure(
            ErrorCode::AccessDenied,
            "Safety-sensitive endpoint requires an explicit product policy.");
    }

    return Result<void>::success();
}

CommandRouter::CommandRouter(INodeCommandExecutor& nodeExecutor,
                             ISceneExecutor& sceneExecutor,
                             const ISafetyPolicy& safetyPolicy)
    : nodeExecutor_(nodeExecutor),
      sceneExecutor_(sceneExecutor),
      safetyPolicy_(safetyPolicy) {}

Result<void> CommandRouter::registerEndpoint(EndpointBinding binding) {
    if (binding.endpointId.empty() || binding.targetId.empty()) {
        return Result<void>::failure(
            ErrorCode::InvalidArgument,
            "Endpoint ID and target ID are required.");
    }

    if (binding.kind != EndpointKind::Scene && binding.nodeId.empty()) {
        return Result<void>::failure(
            ErrorCode::InvalidArgument,
            "Node ID is required for Node-backed endpoints.");
    }

    endpoints_[binding.endpointId] = std::move(binding);
    return Result<void>::success();
}

bool CommandRouter::removeEndpoint(const std::string& endpointId) {
    return endpoints_.erase(endpointId) > 0;
}

std::optional<EndpointBinding> CommandRouter::findEndpoint(
    const std::string& endpointId) const {
    const auto it = endpoints_.find(endpointId);
    if (it == endpoints_.end()) return std::nullopt;
    return it->second;
}

CommandResult CommandRouter::route(const CommandRequest& request,
                                   std::uint64_t nowEpochMs) {
    if (request.commandId.empty() || request.endpointId.empty()) {
        return {request.commandId, false, false,
                "Command ID and endpoint ID are required."};
    }

    if (completedCommandIds_.contains(request.commandId)) {
        return {request.commandId, true, true,
                "Command was already completed."};
    }

    if (request.expiresAtEpochMs != 0 &&
        request.expiresAtEpochMs <= nowEpochMs) {
        return {request.commandId, false, false,
                "Command has expired."};
    }

    const auto binding = findEndpoint(request.endpointId);
    if (!binding) {
        return {request.commandId, false, false,
                "Endpoint was not found."};
    }

    const auto authorization = safetyPolicy_.authorize(request, *binding);
    if (!authorization.ok()) {
        return {request.commandId, false, false,
                authorization.message()};
    }

    auto result = execute(request, *binding);
    if (result.success) {
        completedCommandIds_.insert(request.commandId);
    }
    return result;
}

CommandResult CommandRouter::execute(const CommandRequest& request,
                                     const EndpointBinding& binding) {
    Result<void> result = Result<void>::failure(
        ErrorCode::Unsupported, "Unsupported endpoint type.");

    switch (binding.kind) {
        case EndpointKind::LearnedSignal:
            result = nodeExecutor_.executeLearnedSignal(
                binding.nodeId, binding.targetId);
            break;

        case EndpointKind::Relay: {
            const bool enabled =
                request.action == "TurnOn" ||
                request.action == "Activate" ||
                request.action == "Open";
            result = nodeExecutor_.setRelay(
                binding.nodeId, binding.targetId, enabled);
            break;
        }

        case EndpointKind::Scene:
            result = sceneExecutor_.activateScene(binding.targetId);
            break;
    }

    return {
        request.commandId,
        result.ok(),
        false,
        result.ok() ? "Command completed." : result.message()
    };
}

} // namespace lynq::command
