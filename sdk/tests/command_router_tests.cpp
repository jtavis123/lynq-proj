#include "lynq/command/CommandRouter.h"

#include <cassert>
#include <string>

namespace {

class FakeNodeExecutor final : public lynq::command::INodeCommandExecutor {
public:
    lynq::Result<void> executeLearnedSignal(
        const std::string& nodeId,
        const std::string& signalId) override {
        lastNode = nodeId;
        lastTarget = signalId;
        callCount++;
        return lynq::Result<void>::success();
    }

    lynq::Result<void> setRelay(
        const std::string& nodeId,
        const std::string& relayId,
        bool enabled) override {
        lastNode = nodeId;
        lastTarget = relayId;
        relayEnabled = enabled;
        callCount++;
        return lynq::Result<void>::success();
    }

    std::string lastNode;
    std::string lastTarget;
    bool relayEnabled{false};
    int callCount{0};
};

class FakeSceneExecutor final : public lynq::command::ISceneExecutor {
public:
    lynq::Result<void> activateScene(
        const std::string& sceneId) override {
        lastScene = sceneId;
        callCount++;
        return lynq::Result<void>::success();
    }

    std::string lastScene;
    int callCount{0};
};

} // namespace

int main() {
    using namespace lynq::command;

    FakeNodeExecutor nodes;
    FakeSceneExecutor scenes;
    DefaultSafetyPolicy safety;
    CommandRouter router(nodes, scenes, safety);

    assert(router.registerEndpoint({
        "pool-light",
        EndpointKind::LearnedSignal,
        "node-pool",
        "signal-pool-light-on",
        false,
        true
    }).ok());

    assert(router.registerEndpoint({
        "garage-door",
        EndpointKind::Relay,
        "node-garage",
        "relay-1",
        true,
        true
    }).ok());

    assert(router.registerEndpoint({
        "movie-mode",
        EndpointKind::Scene,
        "",
        "scene-movie",
        false,
        true
    }).ok());

    auto local = router.route({
        "cmd-1",
        "pool-light",
        "TurnOn",
        {},
        CommandSource::LocalUi,
        2000
    }, 1000);

    assert(local.success);
    assert(nodes.lastNode == "node-pool");
    assert(nodes.lastTarget == "signal-pool-light-on");

    auto duplicate = router.route({
        "cmd-1",
        "pool-light",
        "TurnOn",
        {},
        CommandSource::Alexa,
        2000
    }, 1001);

    assert(duplicate.success);
    assert(duplicate.duplicate);
    assert(nodes.callCount == 1);

    auto unsafe = router.route({
        "cmd-2",
        "garage-door",
        "Open",
        {},
        CommandSource::Alexa,
        2000
    }, 1000);

    assert(!unsafe.success);
    assert(nodes.callCount == 1);

    auto scene = router.route({
        "cmd-3",
        "movie-mode",
        "Activate",
        {},
        CommandSource::Automation,
        2000
    }, 1000);

    assert(scene.success);
    assert(scenes.lastScene == "scene-movie");

    auto expired = router.route({
        "cmd-4",
        "pool-light",
        "TurnOn",
        {},
        CommandSource::CloudApi,
        999
    }, 1000);

    assert(!expired.success);

    auto missing = router.route({
        "cmd-5",
        "unknown",
        "TurnOn",
        {},
        CommandSource::LocalUi,
        2000
    }, 1000);

    assert(!missing.success);
    return 0;
}
