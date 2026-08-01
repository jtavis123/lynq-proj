#include "lynq/learning/LearningController.h"

#include <utility>

namespace lynq::learning {

LearningController::LearningController(ILearningRadio& radio, EventBus& events)
    : radio_(radio), events_(events) {}

Result<void> LearningController::initialize() {
    return radio_.initialize();
}

Result<void> LearningController::start(const CaptureRequest& request,
                                       std::string commandId,
                                       std::string commandName,
                                       std::string nodeId,
                                       CompletionCallback callback) {
    if (state_ == LearningState::WaitingForSignal) {
        return Result<void>::failure(ErrorCode::Busy, "A learning session is already active.");
    }

    request_ = request;
    commandId_ = std::move(commandId);
    commandName_ = std::move(commandName);
    nodeId_ = std::move(nodeId);
    completion_ = std::move(callback);
    lastCapture_.reset();
    state_ = LearningState::WaitingForSignal;

    events_.publish({"learning.started", nodeId_, "{}"});

    const auto result = radio_.beginCapture(
        request_, [this](Result<CaptureResult> capture) { handleCapture(std::move(capture)); });

    if (!result.ok()) {
        state_ = LearningState::Failed;
        events_.publish({"learning.failed", nodeId_, result.message()});
        return result;
    }

    return Result<void>::success();
}

Result<void> LearningController::cancel() {
    if (state_ != LearningState::WaitingForSignal) {
        return Result<void>::failure(ErrorCode::InvalidArgument, "No active learning session.");
    }

    const auto result = radio_.cancelCapture();
    if (!result.ok()) {
        return result;
    }

    state_ = LearningState::Cancelled;
    events_.publish({"learning.cancelled", nodeId_, "{}"});
    if (completion_) {
        completion_(Result<command::SignalCommand>::failure(
            ErrorCode::Cancelled, "Learning session cancelled."));
    }
    return Result<void>::success();
}

Result<void> LearningController::replayLastCapture() {
    if (!lastCapture_) {
        return Result<void>::failure(ErrorCode::NotFound, "No learned command is available.");
    }

    events_.publish({"command.transmit.started", nodeId_, lastCapture_->id});
    const auto result = radio_.transmit(*lastCapture_);
    events_.publish({result.ok() ? "command.transmit.completed" : "command.transmit.failed",
                     nodeId_,
                     result.ok() ? lastCapture_->id : result.message()});
    return result;
}

LearningState LearningController::state() const noexcept {
    return state_;
}

const std::optional<command::SignalCommand>& LearningController::lastCapture() const noexcept {
    return lastCapture_;
}

void LearningController::handleCapture(Result<CaptureResult> result) {
    if (!result.ok()) {
        state_ = LearningState::Failed;
        events_.publish({"learning.failed", nodeId_, result.message()});
        if (completion_) {
            completion_(Result<command::SignalCommand>::failure(result.code(), result.message()));
        }
        return;
    }

    command::SignalCommand learned;
    learned.id = commandId_;
    learned.name = commandName_;
    learned.nodeId = nodeId_;
    learned.medium = request_.medium;
    learned.carrierFrequencyHz = result.value().carrierFrequencyHz;
    learned.pulseDurationsUs = result.value().pulseDurationsUs;

    lastCapture_ = learned;
    state_ = LearningState::Captured;
    events_.publish({"learning.captured", nodeId_, learned.id});

    if (completion_) {
        completion_(Result<command::SignalCommand>::success(std::move(learned)));
    }
}

} // namespace lynq::learning
