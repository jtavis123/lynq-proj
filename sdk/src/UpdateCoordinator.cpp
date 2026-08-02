#include "lynq/service/UpdateCoordinator.h"

namespace lynq::service {

UpdateCoordinator::UpdateCoordinator(
    IArtifactVerifier& verifier,
    IUpdateInstaller& installer)
    : verifier_(verifier), installer_(installer) {}

Result<void> UpdateCoordinator::begin(
    const UpdatePlan& plan,
    const std::string& currentHubVersion,
    bool externalPowerPresent) {
    if (plan.planId.empty() ||
        plan.artifact.artifactId.empty() ||
        plan.artifact.version.empty()) {
        return Result<void>::failure(
            ErrorCode::InvalidArgument,
            "Update plan is incomplete.");
    }

    if (plan.requireExternalPower && !externalPowerPresent) {
        return Result<void>::failure(
            ErrorCode::InvalidArgument,
            "External power is required.");
    }

    if (!plan.allowDowngrade &&
        plan.artifact.target == UpdateTarget::Hub &&
        plan.artifact.version < currentHubVersion) {
        return Result<void>::failure(
            ErrorCode::Unsupported,
            "Firmware downgrade is blocked.");
    }

    statuses_[plan.planId] = {
        plan.planId,
        UpdateState::Verifying,
        20,
        "Verifying signed artifact."
    };

    const auto verified = verifier_.verify(plan.artifact);
    if (!verified.ok()) {
        statuses_[plan.planId] = {
            plan.planId,
            UpdateState::Failed,
            20,
            verified.message()
        };
        return verified;
    }

    statuses_[plan.planId] = {
        plan.planId,
        UpdateState::Installing,
        60,
        "Installing firmware."
    };

    Result<void> installed = Result<void>::success();
    if (plan.artifact.target == UpdateTarget::Hub) {
        installed = installer_.installHub(plan.artifact);
    } else {
        for (const auto& nodeId : plan.nodeIds) {
            installed = installer_.installNode(
                nodeId, plan.artifact);
            if (!installed.ok()) break;
        }
    }

    if (!installed.ok()) {
        statuses_[plan.planId] = {
            plan.planId,
            UpdateState::Failed,
            60,
            installed.message()
        };
        return installed;
    }

    statuses_[plan.planId] = {
        plan.planId,
        UpdateState::AwaitingHealthCheck,
        90,
        "Waiting for post-update health confirmation."
    };

    return Result<void>::success();
}

Result<void> UpdateCoordinator::reportHealthy(
    const std::string& planId) {
    auto it = statuses_.find(planId);
    if (it == statuses_.end()) {
        return Result<void>::failure(
            ErrorCode::NotFound,
            "Update plan was not found.");
    }

    it->second = {
        planId,
        UpdateState::Completed,
        100,
        "Update completed and passed health check."
    };
    return Result<void>::success();
}

Result<void> UpdateCoordinator::reportUnhealthy(
    const std::string& planId,
    const std::string& reason) {
    auto it = statuses_.find(planId);
    if (it == statuses_.end()) {
        return Result<void>::failure(
            ErrorCode::NotFound,
            "Update plan was not found.");
    }

    const auto rollback = installer_.rollbackHub();
    it->second = {
        planId,
        rollback.ok()
            ? UpdateState::RolledBack
            : UpdateState::Failed,
        100,
        rollback.ok()
            ? "Health check failed; previous image restored: " + reason
            : "Health check and rollback failed: " + reason
    };

    return rollback;
}

std::optional<UpdateStatus> UpdateCoordinator::status(
    const std::string& planId) const {
    const auto it = statuses_.find(planId);
    if (it == statuses_.end()) return std::nullopt;
    return it->second;
}

} // namespace lynq::service
