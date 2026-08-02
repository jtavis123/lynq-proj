#include "lynq/automation/CommandDispatchEngine.h"
#include "lynq/device/DeviceDatabase.h"

#include <cassert>
#include <string>

namespace {

class MemoryStore final : public lynq::device::IDeviceDatabaseStore {
public:
    lynq::Result<std::string> loadJson() override {
        return lynq::Result<std::string>::success(json);
    }

    lynq::Result<void> saveJson(
        const std::string& value) override {
        json = value;
        return lynq::Result<void>::success();
    }

    std::string json;
};

class FakeExecutor final
    : public lynq::automation::ILearnedCommandExecutor {
public:
    lynq::Result<void> execute(
        const std::string& nodeId,
        const std::string& commandId) override {
        lastNode = nodeId;
        lastCommand = commandId;
        calls++;
        return lynq::Result<void>::success();
    }

    std::string lastNode;
    std::string lastCommand;
    int calls{0};
};

} // namespace

int main() {
    using namespace lynq;

    MemoryStore store;
    device::DeviceDatabase database(store);

    device::DeviceRecord device;
    device.deviceId = "tv-living-room";
    device.name = "Living Room TV";
    device.roomId = "living-room";
    device.category = "television";
    device.favorite = true;
    device.commands.push_back({
        "bind-power",
        "tv-living-room",
        "Power",
        "learned-ir-power",
        "node-living-room",
        true
    });

    assert(database.upsert(device).ok());
    assert(database.save().ok());
    assert(store.json.find("Living Room TV") != std::string::npos);

    FakeExecutor executor;
    automation::CommandDispatchEngine dispatch(database, executor);

    const auto success = dispatch.dispatch({
        "req-1",
        "tv-living-room",
        "Power",
        2000
    }, 1000);

    assert(success.success);
    assert(executor.lastNode == "node-living-room");
    assert(executor.lastCommand == "learned-ir-power");

    const auto expired = dispatch.dispatch({
        "req-2",
        "tv-living-room",
        "Power",
        999
    }, 1000);

    assert(!expired.success);

    const auto missing = dispatch.dispatch({
        "req-3",
        "tv-living-room",
        "Volume Up",
        2000
    }, 1000);

    assert(!missing.success);
    return 0;
}
