#pragma once
#include <cstdint>
#include <string>
namespace lynq::hub {
struct DiagnosticsSnapshot { std::string firmwareVersion{"1.1.0-alpha"}; std::string boardProfile{"waveshare-esp32-s3-touch-lcd-4.3b"}; std::uint64_t uptimeSeconds{0}; std::uint32_t freeHeapBytes{0}; std::uint32_t freePsramBytes{0}; std::uint32_t flashBytes{0}; int wifiRssiDbm{0}; bool displayReady{false}; bool touchReady{false}; bool wifiReady{false}; bool bleReady{false}; unsigned onlineNodes{0}; unsigned activeAlerts{0}; };
}
