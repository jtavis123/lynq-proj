#include "lynq/core/Configuration.h"
#include "lynq/core/EventBus.h"
#include "lynq/core/Logger.h"
#include "lynq/core/Result.h"
#include "lynq/core/StateMachine.h"
#include "lynq/core/Timer.h"
#include "lynq/core/UUID.h"
#include "lynq/core/Version.h"

#include <atomic>
#include <cassert>
#include <chrono>
#include <memory>
#include <string>
#include <thread>
#include <vector>

namespace {
class MemorySink final : public lynq::LogSink {
public:
    void write(lynq::LogLevel, std::string_view module, std::string_view message) override {
        entries.emplace_back(std::string(module) + ":" + std::string(message));
    }
    std::vector<std::string> entries;
};

enum class TestState { Idle, Ready, Error };
}

int main() {
    const auto ok = lynq::Result<int>::success(42);
    assert(ok.ok() && ok.value() == 42);
    const auto failure = lynq::Result<int>::failure(lynq::ErrorCode::Timeout, "timeout");
    assert(!failure.ok() && failure.code() == lynq::ErrorCode::Timeout);

    const auto id = lynq::UUID::random();
    const auto parsed = lynq::UUID::parse(id.toString());
    assert(parsed.has_value() && parsed.value() == id);
    assert(lynq::kSdkVersion.toString() == "0.1.1-alpha");

    lynq::Logger logger;
    auto sink = std::make_shared<MemorySink>();
    logger.addSink(sink);
    logger.info("test", "message");
    assert(sink->entries.size() == 1 && sink->entries.front() == "test:message");

    lynq::EventBus bus;
    int eventCount = 0;
    const auto sub = bus.subscribe("node.online", [&](const lynq::Event& e) {
        assert(e.source == "node-1");
        ++eventCount;
    });
    bus.publish({"node.online", "node-1", "{}"});
    assert(eventCount == 1 && bus.subscriberCount("node.online") == 1);
    assert(bus.unsubscribe("node.online", sub));

    lynq::Configuration config;
    config.set("heartbeat_ms", std::int64_t{30000});
    config.set("dark_mode", true);
    assert(config.get<std::int64_t>("heartbeat_ms").value() == 30000);
    assert(config.get<bool>("dark_mode").value());
    assert(config.erase("dark_mode"));

    bool actionCalled = false;
    lynq::StateMachine<TestState> machine(TestState::Idle);
    machine.allow(TestState::Idle, TestState::Ready, {}, [&] { actionCalled = true; });
    assert(machine.transitionTo(TestState::Ready));
    assert(machine.current() == TestState::Ready && actionCalled);
    assert(!machine.transitionTo(TestState::Error));

    std::atomic<bool> fired{false};
    lynq::TimerService timers;
    timers.scheduleOnce(std::chrono::milliseconds(10), [&] { fired.store(true); });
    std::this_thread::sleep_for(std::chrono::milliseconds(40));
    assert(fired.load());

    return 0;
}
