#include "lynq/learning/LearningWizard.h"
#include <algorithm>
#include <cctype>
#include <sstream>
#include <utility>

namespace lynq::learning {

LearningWizard::LearningWizard(ISignalCapture& capture,
                               ILearnedCommandRepository& repository)
    : capture_(capture), repository_(repository) {}

Result<void> LearningWizard::selectDevice(std::string deviceId) {
    if (deviceId.empty()) return Result<void>::failure(ErrorCode::InvalidArgument, "Device ID is required.");
    session_.deviceId = std::move(deviceId);
    session_.step = WizardStep::SelectNode;
    return Result<void>::success();
}

Result<void> LearningWizard::selectNode(std::string nodeId,
                                        SignalTransport transport) {
    if (session_.deviceId.empty()) return Result<void>::failure(ErrorCode::InvalidArgument, "Select a device first.");
    if (nodeId.empty()) return Result<void>::failure(ErrorCode::InvalidArgument, "Node ID is required.");
    session_.nodeId = std::move(nodeId);
    transport_ = transport;
    session_.step = WizardStep::Ready;
    return Result<void>::success();
}

Result<void> LearningWizard::beginCapture(std::uint32_t timeoutMs) {
    if (session_.step != WizardStep::Ready) return Result<void>::failure(ErrorCode::Busy, "Wizard is not ready to capture.");
    session_.step = WizardStep::Capturing;
    const auto result = capture_.capture(transport_, timeoutMs);
    if (!result.ok()) {
        session_.step = WizardStep::Failed;
        session_.detail = result.message();
        return Result<void>::failure(result.code(), result.message());
    }
    session_.signal = result.value();
    session_.step = WizardStep::Captured;
    session_.detail = "Signal captured.";
    return Result<void>::success();
}

Result<void> LearningWizard::testReplay() {
    if (!session_.signal) return Result<void>::failure(ErrorCode::NotFound, "No captured signal is available.");
    session_.step = WizardStep::Testing;
    const auto result = capture_.replay(*session_.signal);
    if (!result.ok()) {
        session_.step = WizardStep::Failed;
        session_.detail = result.message();
        return result;
    }
    session_.step = WizardStep::NameCommand;
    session_.detail = "Replay completed. Confirm the device responded.";
    return Result<void>::success();
}

Result<void> LearningWizard::setCommandName(std::string name) {
    name = normalizeName(std::move(name));
    if (name.size() < 2 || name.size() > 40) {
        return Result<void>::failure(ErrorCode::InvalidArgument, "Command name must contain 2 to 40 characters.");
    }
    session_.commandName = std::move(name);
    return Result<void>::success();
}

Result<LearnedCommand> LearningWizard::save(std::uint64_t nowEpochMs) {
    if (session_.step != WizardStep::NameCommand || !session_.signal || session_.commandName.empty()) {
        return Result<LearnedCommand>::failure(ErrorCode::InvalidArgument, "Capture, test and name the command before saving.");
    }
    LearnedCommand command;
    command.id = makeId(session_, nowEpochMs);
    command.deviceId = session_.deviceId;
    command.nodeId = session_.nodeId;
    command.name = session_.commandName;
    command.signal = *session_.signal;
    command.createdAtEpochMs = nowEpochMs;
    const auto result = repository_.save(command);
    if (!result.ok()) return Result<LearnedCommand>::failure(result.code(), result.message());
    session_.step = WizardStep::Complete;
    session_.detail = "Command saved.";
    return Result<LearnedCommand>::success(command);
}

void LearningWizard::cancel() { session_.step = WizardStep::Cancelled; session_.detail = "Learning cancelled."; }
void LearningWizard::reset() { session_ = WizardSession{}; }
const WizardSession& LearningWizard::session() const noexcept { return session_; }

std::string LearningWizard::normalizeName(std::string value) {
    value.erase(value.begin(), std::find_if(value.begin(), value.end(), [](unsigned char c){ return !std::isspace(c); }));
    value.erase(std::find_if(value.rbegin(), value.rend(), [](unsigned char c){ return !std::isspace(c); }).base(), value.end());
    return value;
}

std::string LearningWizard::makeId(const WizardSession& session,
                                   std::uint64_t nowEpochMs) {
    std::ostringstream stream;
    stream << session.deviceId << '-' << nowEpochMs;
    return stream.str();
}

} // namespace lynq::learning
