#pragma once
#include "lynq/core/Result.h"
#include <string>
namespace lynq::hub {
struct HubSettings { std::string hubName{"LYNQ Hub"}; std::string timezone{"America/Phoenix"}; unsigned brightnessPercent{80}; bool autoUpdate{true}; bool simulationMode{true}; };
class IHubSettingsStore { public: virtual ~IHubSettingsStore() = default; virtual Result<HubSettings> load() = 0; virtual Result<void> save(const HubSettings&) = 0; };
class HubSettingsService {
public:
 explicit HubSettingsService(IHubSettingsStore& store): store_(store) {}
 Result<void> initialize(); Result<void> update(HubSettings settings);
 [[nodiscard]] const HubSettings& current() const noexcept { return current_; }
private: IHubSettingsStore& store_; HubSettings current_;
};
}
