#pragma once

#include "lynq/core/Result.h"

#include <cstdint>
#include <map>
#include <optional>
#include <string>
#include <unordered_map>
#include <unordered_set>

namespace lynq::command {

enum class CommandSource {
    LocalUi,
    Automation,
    Alexa,
    CloudApi
};

enum class EndpointKind {
    LearnedSignal,
    Relay,
    Scene
};

struct CommandRequest {
    std::string commandId;
    std::string endpointId;
    std::string action;
    std::map<std::string, std::string> parameters;
    CommandSource source{CommandSource::LocalUi};
    std::uint64_t expiresAtEpochMs{0};
};

struct EndpointBinding {
    std::string endpointId;
    EndpointKind kind{EndpointKind::LearnedSignal};
    std::string nodeId;
    std::string targetId;
    bool safetySensitive{false};
    bool remoteControlAllowed{true};
};

struct CommandResult {
    std::string commandId;
    bool success{false};
    bool duplicate{false};
    std::string detail;
};

class INodeCommandExecutor {
public:
    virtual ~INodeCommandExecutor() = default;
    virtual Result<void> executeLearnedSignal(const std::string& nodeId,
                                              const std::string& signalId) = 0;
    virtual Result<void> setRelay(const std::string& nodeId,
                                  const std::string& relayId,
                                  bool enabled) = 0;
};

class ISceneExecutor {
public:
    virtual ~ISceneExecutor() = default;
    virtual Result<void> activateScene(const std::string& sceneId) = 0;
};

class ISafetyPolicy {
public:
    virtual ~ISafetyPolicy() = default;
    virtual Result<void> authorize(const CommandRequest& request,
                                   const EndpointBinding& binding) const = 0;
};

class DefaultSafetyPolicy final : public ISafetyPolicy {
public:
    Result<void> authorize(const CommandRequest& request,
                           const EndpointBinding& binding) const override;
};

class CommandRouter {
public:
    CommandRouter(INodeCommandExecutor& nodeExecutor,
                  ISceneExecutor& sceneExecutor,
                  const ISafetyPolicy& safetyPolicy);

    Result<void> registerEndpoint(EndpointBinding binding);
    bool removeEndpoint(const std::string& endpointId);
    std::optional<EndpointBinding> findEndpoint(const std::string& endpointId) const;

    CommandResult route(const CommandRequest& request,
                        std::uint64_t nowEpochMs);

private:
    CommandResult execute(const CommandRequest& request,
                          const EndpointBinding& binding);

    INodeCommandExecutor& nodeExecutor_;
    ISceneExecutor& sceneExecutor_;
    const ISafetyPolicy& safetyPolicy_;
    std::unordered_map<std::string, EndpointBinding> endpoints_;
    std::unordered_set<std::string> completedCommandIds_;
};

} // namespace lynq::command
