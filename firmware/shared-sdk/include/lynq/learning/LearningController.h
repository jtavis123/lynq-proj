#pragma once

#include "lynq/command/SignalCommand.h"
#include "lynq/core/EventBus.h"
#include "lynq/core/Result.h"
#include "lynq/learning/ILearningRadio.h"

#include <functional>
#include <optional>
#include <string>

namespace lynq::learning {

enum class LearningState {
    Idle,
    WaitingForSignal,
    Captured,
    Failed,
    Cancelled
};

class LearningController {
public:
    using CompletionCallback = std::function<void(Result<command::SignalCommand>)>;

    LearningController(ILearningRadio& radio, EventBus& events);

    Result<void> initialize();
    Result<void> start(const CaptureRequest& request,
                       std::string commandId,
                       std::string commandName,
                       std::string nodeId,
                       CompletionCallback callback);
    Result<void> cancel();
    Result<void> replayLastCapture();

    [[nodiscard]] LearningState state() const noexcept;
    [[nodiscard]] const std::optional<command::SignalCommand>& lastCapture() const noexcept;

private:
    void handleCapture(Result<CaptureResult> result);

    ILearningRadio& radio_;
    EventBus& events_;
    LearningState state_{LearningState::Idle};
    CaptureRequest request_{};
    std::string commandId_;
    std::string commandName_;
    std::string nodeId_;
    CompletionCallback completion_;
    std::optional<command::SignalCommand> lastCapture_;
};

} // namespace lynq::learning
