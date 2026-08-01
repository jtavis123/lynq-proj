#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace lynq::command {

enum class SignalMedium {
    Rf,
    Ir
};

struct SignalCommand {
    std::string id;
    std::string name;
    std::string nodeId;
    SignalMedium medium{SignalMedium::Rf};
    std::uint32_t carrierFrequencyHz{0};
    std::uint32_t repeatCount{1};
    std::vector<std::uint32_t> pulseDurationsUs;
};

} // namespace lynq::command
