#pragma once
#include <cstdint>
#include <string>
#include <vector>
namespace lynq::reliability {
struct HealthInput { bool wifi{false}; bool cloud{false}; std::uint32_t onlineNodes{0}; std::uint32_t offlineNodes{0}; bool storageHealthy{true}; bool otaHealthy{true}; };
struct HealthScore { std::uint32_t score{0}; std::string label; std::vector<std::string> issues; };
class SystemHealthScore { public: static HealthScore calculate(const HealthInput& input); };
}
