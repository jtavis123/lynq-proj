#pragma once

#include "lynq/core/Result.h"

#include <cstdint>
#include <functional>
#include <vector>

namespace lynq::node {

struct PulseCapture {
    std::vector<std::uint32_t> durationsUs;
    int signalStrength{0};
};

class IRevARf433 {
public:
    using CaptureCallback = std::function<void(Result<PulseCapture>)>;
    virtual ~IRevARf433() = default;
    virtual Result<void> initialize() = 0;
    virtual Result<void> beginCapture(CaptureCallback callback) = 0;
    virtual Result<void> cancelCapture() = 0;
    virtual Result<void> transmit(const std::vector<std::uint32_t>& durationsUs,
                                  std::uint32_t repeats) = 0;
};

class IRevAIr {
public:
    using CaptureCallback = std::function<void(Result<PulseCapture>)>;
    virtual ~IRevAIr() = default;
    virtual Result<void> initialize() = 0;
    virtual Result<void> beginCapture(CaptureCallback callback) = 0;
    virtual Result<void> cancelCapture() = 0;
    virtual Result<void> transmit(const std::vector<std::uint32_t>& durationsUs,
                                  std::uint32_t carrierHz,
                                  std::uint32_t repeats) = 0;
};

} // namespace lynq::node
