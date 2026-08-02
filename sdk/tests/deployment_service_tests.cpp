#include "lynq/service/ServiceSessionManager.h"
#include "lynq/service/UpdateCoordinator.h"

#include <cassert>
#include <string>

namespace {

class Verifier final
    : public lynq::service::IArtifactVerifier {
public:
    lynq::Result<void> verify(
        const lynq::service::FirmwareArtifact& artifact) override {
        if (artifact.sha256 == "good" &&
            artifact.signature == "signed") {
            return lynq::Result<void>::success();
        }
        return lynq::Result<void>::failure(
            lynq::ErrorCode::Unauthorized,
            "Signature or digest is invalid.");
    }
};

class Installer final
    : public lynq::service::IUpdateInstaller {
public:
    lynq::Result<void> installHub(
        const lynq::service::FirmwareArtifact&) override {
        hubInstalls++;
        return lynq::Result<void>::success();
    }

    lynq::Result<void> installNode(
        const std::string&,
        const lynq::service::FirmwareArtifact&) override {
        nodeInstalls++;
        return lynq::Result<void>::success();
    }

    lynq::Result<void> rollbackHub() override {
        rollbacks++;
        return lynq::Result<void>::success();
    }

    int hubInstalls{0};
    int nodeInstalls{0};
    int rollbacks{0};
};

} // namespace

int main() {
    using namespace lynq;
    using namespace lynq::service;

    ServiceSessionManager sessions;
    assert(sessions.create({
        "session-1", "tech-1", 1000, 2000,
        true, true, false
    }).ok());
    assert(sessions.authorize("session-1", 1500).has_value());
    assert(!sessions.authorize("session-1", 2000).has_value());

    Verifier verifier;
    Installer installer;
    UpdateCoordinator coordinator(verifier, installer);

    UpdatePlan hubPlan;
    hubPlan.planId = "plan-hub";
    hubPlan.artifact = {
        "hub-image",
        UpdateTarget::Hub,
        "waveshare-43b",
        "2.1.0-beta.1",
        "/updates/hub.bin",
        "good",
        "signed",
        1024
    };

    assert(coordinator.begin(
        hubPlan, "2.0.0-beta.1", true).ok());
    assert(installer.hubInstalls == 1);
    assert(coordinator.reportHealthy("plan-hub").ok());
    assert(coordinator.status("plan-hub")->state ==
           UpdateState::Completed);

    UpdatePlan nodePlan;
    nodePlan.planId = "plan-node";
    nodePlan.artifact = {
        "node-image",
        UpdateTarget::Node,
        "rev-a-m5stack",
        "2.1.0-beta.1",
        "/updates/node.bin",
        "good",
        "signed",
        512
    };
    nodePlan.nodeIds = {"node-1", "node-2"};

    assert(coordinator.begin(
        nodePlan, "2.0.0-beta.1", true).ok());
    assert(installer.nodeInstalls == 2);
    return 0;
}
