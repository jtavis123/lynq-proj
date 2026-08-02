#pragma once
#include <cstdint>
#include <string>

namespace lynq::hub {
struct HardwareReport {
    std::string chipModel;
    int coreCount{0};
    std::uint32_t flashBytes{0};
    std::uint32_t psramBytes{0};
    std::uint32_t freeHeapBytes{0};
    bool minimumMemoryPassed{false};
};
class HardwareDiagnostics {
public:
    HardwareReport run() const;
};
}
