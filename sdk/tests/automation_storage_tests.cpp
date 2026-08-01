#include "lynq/automation/AutomationScheduler.h"
#include "lynq/storage/JsonConfigurationStore.h"

#include <cassert>
#include <string>
#include <unordered_map>

namespace {

class FakeSceneExecutor final
    : public lynq::automation::IAutomationActionExecutor {
public:
    lynq::Result<void> activateScene(
        const std::string& sceneId) override {
        lastScene = sceneId;
        calls++;
        return lynq::Result<void>::success();
    }

    std::string lastScene;
    int calls{0};
};

class MemoryTextStorage final : public lynq::storage::ITextStorage {
public:
    lynq::Result<std::string> read(std::string_view key) override {
        const auto it = values.find(std::string(key));
        if (it == values.end()) {
            return lynq::Result<std::string>::failure(
                lynq::ErrorCode::NotFound, "Missing document.");
        }
        return lynq::Result<std::string>::success(it->second);
    }

    lynq::Result<void> write(
        std::string_view key,
        std::string_view value) override {
        values[std::string(key)] = std::string(value);
        return lynq::Result<void>::success();
    }

    lynq::Result<void> remove(std::string_view key) override {
        values.erase(std::string(key));
        return lynq::Result<void>::success();
    }

    std::unordered_map<std::string, std::string> values;
};

} // namespace

int main() {
    using namespace lynq::automation;

    FakeSceneExecutor scenes;
    AutomationScheduler scheduler(scenes);

    assert(scheduler.upsert({
        "rule-morning",
        "Good Morning",
        true,
        "scene-morning",
        {TriggerType::TimeOfDay, 7, 30, 0, "", ""},
        0
    }).ok());

    auto first = scheduler.evaluate({
        1000, 7, 30, 360, 1080, std::nullopt, std::nullopt
    });
    assert(first.size() == 1);
    assert(scenes.lastScene == "scene-morning");

    auto duplicateMinute = scheduler.evaluate({
        1000, 7, 30, 360, 1080, std::nullopt, std::nullopt
    });
    assert(duplicateMinute.empty());
    assert(scenes.calls == 1);

    assert(scheduler.upsert({
        "rule-sunset",
        "Patio at Sunset",
        true,
        "scene-patio",
        {TriggerType::SunsetOffset, 0, 0, -10, "", ""},
        0
    }).ok());

    auto sunset = scheduler.evaluate({
        1001, 17, 50, 360, 1080, std::nullopt, std::nullopt
    });
    assert(sunset.size() == 1);
    assert(scenes.lastScene == "scene-patio");

    assert(scheduler.upsert({
        "rule-door",
        "Entry Welcome",
        true,
        "scene-entry",
        {TriggerType::DeviceEvent, 0, 0, 0,
         "front-door", "opened"},
        0
    }).ok());

    auto event = scheduler.evaluate({
        1002, 18, 0, 360, 1080,
        std::string("front-door"), std::string("opened")
    });
    assert(event.size() == 1);
    assert(scenes.lastScene == "scene-entry");

    MemoryTextStorage memory;
    lynq::storage::JsonConfigurationStore store(memory);
    assert(store.save("devices", R"({"version":1,"devices":[]})").ok());
    const auto loaded = store.load("devices");
    assert(loaded.ok());
    assert(loaded.value().find("\"version\":1") != std::string::npos);
    assert(!store.save("bad", "not-json").ok());
    assert(store.erase("devices").ok());

    return 0;
}
