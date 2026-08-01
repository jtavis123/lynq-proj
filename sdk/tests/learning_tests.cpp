#include "lynq/core/EventBus.h"
#include "lynq/learning/LearningController.h"

#include <cassert>
#include <utility>

namespace {

class FakeLearningRadio final : public lynq::learning::ILearningRadio {
public:
    lynq::Result<void> initialize() override {
        initialized = true;
        return lynq::Result<void>::success();
    }

    lynq::Result<void> beginCapture(const lynq::learning::CaptureRequest& request,
                                    CaptureCallback callback) override {
        active = true;
        lastRequest = request;
        callback_ = std::move(callback);
        return lynq::Result<void>::success();
    }

    lynq::Result<void> cancelCapture() override {
        active = false;
        return lynq::Result<void>::success();
    }

    lynq::Result<void> transmit(const lynq::command::SignalCommand& command) override {
        transmitted = command;
        return lynq::Result<void>::success();
    }

    void emit(lynq::learning::CaptureResult capture) {
        active = false;
        callback_(lynq::Result<lynq::learning::CaptureResult>::success(std::move(capture)));
    }

    bool initialized{false};
    bool active{false};
    lynq::learning::CaptureRequest lastRequest{};
    lynq::command::SignalCommand transmitted{};
    CaptureCallback callback_;
};

} // namespace

int main() {
    lynq::EventBus events;
    FakeLearningRadio radio;
    lynq::learning::LearningController controller(radio, events);

    assert(controller.initialize().ok());
    assert(radio.initialized);

    bool completed = false;
    lynq::command::SignalCommand learned;
    const auto startResult = controller.start(
        {lynq::command::SignalMedium::Rf, std::chrono::milliseconds(5000)},
        "cmd-001",
        "Garage Open",
        "node-001",
        [&](lynq::Result<lynq::command::SignalCommand> result) {
            assert(result.ok());
            learned = result.value();
            completed = true;
        });

    assert(startResult.ok());
    assert(controller.state() == lynq::learning::LearningState::WaitingForSignal);

    radio.emit({433920000, {350, 1050, 350, 1050, 350, 350}, -41});

    assert(completed);
    assert(controller.state() == lynq::learning::LearningState::Captured);
    assert(learned.id == "cmd-001");
    assert(learned.nodeId == "node-001");
    assert(learned.carrierFrequencyHz == 433920000);
    assert(!learned.pulseDurationsUs.empty());

    assert(controller.replayLastCapture().ok());
    assert(radio.transmitted.id == "cmd-001");
    return 0;
}
