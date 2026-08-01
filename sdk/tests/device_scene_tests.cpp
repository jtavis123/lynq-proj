#include "lynq/device/DeviceRegistry.h"
#include "lynq/device/RoomRegistry.h"
#include "lynq/scene/SceneEngine.h"

#include <cassert>
#include <string>
#include <vector>

namespace {
class FakeSceneExecutor final : public lynq::scene::ISceneActionExecutor {
public:
    lynq::Result<void> execute(const lynq::scene::SceneAction& action) override {
        calls.push_back(action.endpointId + ":" + action.action);
        if (action.endpointId == "broken") {
            return lynq::Result<void>::failure(
                lynq::ErrorCode::Unsupported, "simulated failure");
        }
        return lynq::Result<void>::success();
    }
    std::vector<std::string> calls;
};
}

int main() {
    using namespace lynq;

    device::RoomRegistry rooms;
    assert(rooms.upsert({"living", "Living Room", "sofa", 1}).ok());
    assert(rooms.upsert({"garage", "Garage", "garage", 2}).ok());
    assert(rooms.list().size() == 2);

    device::DeviceRegistry devices;
    assert(devices.upsert({
        "dev-pool", "Pool Lights", "living", device::DeviceType::Light,
        "lightbulb", "pool-light", true, false, true
    }).ok());
    assert(devices.upsert({
        "dev-garage", "Garage Door", "garage", device::DeviceType::GarageDoor,
        "garage", "garage-door", false, true, true
    }).ok());
    assert(devices.size() == 2);
    assert(devices.listByRoom("garage").size() == 1);
    assert(devices.listAlexaExposed().size() == 1);

    FakeSceneExecutor executor;
    scene::SceneEngine scenes(executor);
    assert(scenes.upsert({
        "movie", "Movie Night", "movie", true, true,
        {{"pool-light", "TurnOff"}, {"tv", "TurnOn"}}
    }).ok());

    const auto result = scenes.activate("movie");
    assert(result.ok());
    assert(result.value().completed == 2);
    assert(result.value().failed == 0);
    assert(executor.calls.size() == 2);
    return 0;
}
