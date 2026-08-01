#pragma once

#include "lynq/command/SignalCommand.h"
#include "lynq/core/Result.h"

#include <chrono>
#include <functional>

namespace lynq::learning {

struct CaptureRequest {
    command::SignalMedium medium{command::SignalMedium::Rf};
    std::chrono::milliseconds timeout{15000};
};

struct CaptureResult {
    std::uint32_t carrierFrequencyHz{0};
    std::vector<std::uint32_t> pulseDurationsUs;
    int signalStrengthDbm{0};
};

class ILearningRadio {
public:
    using CaptureCallback = std::function<void(Result<CaptureResult>)>;

    virtual ~ILearningRadio() = default;
    virtual Result<void> initialize() = 0;
    virtual Result<void> beginCapture(const CaptureRequest& request,
                                      CaptureCallback callback) = 0;
    virtual Result<void> cancelCapture() = 0;
    virtual Result<void> transmit(const command::SignalCommand& command) = 0;
};

} // namespace lynq::learning
