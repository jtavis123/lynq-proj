#pragma once

#include "lynq/core/Result.h"
#include "lynq/service/DeploymentModels.h"

#include <functional>
#include <optional>
#include <string>
#include <unordered_map>

namespace lynq::service {

class IArtifactVerifier {
public:
    virtual ~IArtifactVerifier() = default;
    virtual Result<void> verify(
        const FirmwareArtifact& artifact) = 0;
};

class IUpdateInstaller {
public:
    virtual ~IUpdateInstaller() = default;
    virtual Result<void> installHub(
        const FirmwareArtifact& artifact) = 0;
    virtual Result<void> installNode(
        const std::string& nodeId,
        const FirmwareArtifact& artifact) = 0;
    virtual Result<void> rollbackHub() = 0;
};

class UpdateCoordinator {
public:
    UpdateCoordinator(
        IArtifactVerifier& verifier,
        IUpdateInstaller& installer);

    Result<void> begin(
        const UpdatePlan& plan,
        const std::string& currentHubVersion,
        bool externalPowerPresent);

    Result<void> reportHealthy(
        const std::string& planId);

    Result<void> reportUnhealthy(
        const std::string& planId,
        const std::string& reason);

    std::optional<UpdateStatus> status(
        const std::string& planId) const;

private:
    IArtifactVerifier& verifier_;
    IUpdateInstaller& installer_;
    std::unordered_map<std::string, UpdateStatus> statuses_;
};

} // namespace lynq::service
