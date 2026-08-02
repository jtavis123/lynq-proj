#include "lynq/learning/LearningWizard.h"
#include <cassert>
#include <unordered_map>

class FakeCapture final : public lynq::learning::ISignalCapture {
public:
    lynq::Result<lynq::learning::CapturedSignal> capture(lynq::learning::SignalTransport transport, std::uint32_t) override {
        lynq::learning::CapturedSignal signal;
        signal.transport = transport;
        signal.encoding = transport == lynq::learning::SignalTransport::Infrared ? "raw-ir" : "raw-rf433";
        signal.timings = {9000, 4500, 560, 560};
        signal.carrierHz = transport == lynq::learning::SignalTransport::Infrared ? 38000 : 0;
        signal.fingerprint = "abc123";
        return lynq::Result<lynq::learning::CapturedSignal>::success(signal);
    }
    lynq::Result<void> replay(const lynq::learning::CapturedSignal&) override { replayed = true; return lynq::Result<void>::success(); }
    bool replayed{false};
};

class MemoryRepository final : public lynq::learning::ILearnedCommandRepository {
public:
    lynq::Result<void> save(const lynq::learning::LearnedCommand& command) override { values[command.id] = command; return lynq::Result<void>::success(); }
    std::optional<lynq::learning::LearnedCommand> find(const std::string& id) const override {
        auto it = values.find(id); if (it == values.end()) return std::nullopt; return it->second;
    }
    std::unordered_map<std::string, lynq::learning::LearnedCommand> values;
};

int main() {
    using namespace lynq::learning;
    FakeCapture capture;
    MemoryRepository repository;
    LearningWizard wizard(capture, repository);
    assert(wizard.selectDevice("tv-living-room").ok());
    assert(wizard.selectNode("node-1", SignalTransport::Infrared).ok());
    assert(wizard.beginCapture().ok());
    assert(wizard.session().step == WizardStep::Captured);
    assert(wizard.testReplay().ok());
    assert(capture.replayed);
    assert(wizard.setCommandName(" Power ").ok());
    const auto saved = wizard.save(123456);
    assert(saved.ok());
    assert(saved.value().name == "Power");
    assert(repository.find(saved.value().id).has_value());
    assert(wizard.session().step == WizardStep::Complete);
    return 0;
}
