#pragma once
#include "lynq/core/Result.h"
#include <cstdint>
#include <optional>
#include <string>
#include <vector>

namespace lynq::learning {

enum class SignalTransport { Infrared, Rf433 };
enum class WizardStep { SelectDevice, SelectNode, Ready, Capturing, Captured, Testing, NameCommand, Complete, Failed, Cancelled };

struct CapturedSignal {
    SignalTransport transport{SignalTransport::Infrared};
    std::string encoding;
    std::vector<std::uint32_t> timings;
    std::uint32_t carrierHz{0};
    std::string fingerprint;
};

struct LearnedCommand {
    std::string id;
    std::string deviceId;
    std::string nodeId;
    std::string name;
    CapturedSignal signal;
    std::uint64_t createdAtEpochMs{0};
};

class ISignalCapture {
public:
    virtual ~ISignalCapture() = default;
    virtual Result<CapturedSignal> capture(SignalTransport transport,
                                            std::uint32_t timeoutMs) = 0;
    virtual Result<void> replay(const CapturedSignal& signal) = 0;
};

class ILearnedCommandRepository {
public:
    virtual ~ILearnedCommandRepository() = default;
    virtual Result<void> save(const LearnedCommand& command) = 0;
    virtual std::optional<LearnedCommand> find(const std::string& id) const = 0;
};

struct WizardSession {
    WizardStep step{WizardStep::SelectDevice};
    std::string deviceId;
    std::string nodeId;
    std::string commandName;
    std::optional<CapturedSignal> signal;
    std::string detail;
};

class LearningWizard {
public:
    LearningWizard(ISignalCapture& capture,
                   ILearnedCommandRepository& repository);

    Result<void> selectDevice(std::string deviceId);
    Result<void> selectNode(std::string nodeId,
                            SignalTransport transport);
    Result<void> beginCapture(std::uint32_t timeoutMs = 15000);
    Result<void> testReplay();
    Result<void> setCommandName(std::string name);
    Result<LearnedCommand> save(std::uint64_t nowEpochMs);
    void cancel();
    void reset();

    [[nodiscard]] const WizardSession& session() const noexcept;

private:
    static std::string normalizeName(std::string value);
    static std::string makeId(const WizardSession& session,
                              std::uint64_t nowEpochMs);

    ISignalCapture& capture_;
    ILearnedCommandRepository& repository_;
    WizardSession session_;
    SignalTransport transport_{SignalTransport::Infrared};
};

} // namespace lynq::learning
