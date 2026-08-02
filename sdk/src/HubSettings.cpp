#include "lynq/hub/HubSettings.h"
#include <utility>
namespace lynq::hub {
Result<void> HubSettingsService::initialize() { const auto loaded=store_.load(); if (!loaded.ok()) return Result<void>::failure(loaded.code(), loaded.message()); current_=loaded.value(); return Result<void>::success(); }
Result<void> HubSettingsService::update(HubSettings settings) { if (settings.hubName.empty() || settings.brightnessPercent>100) return Result<void>::failure(ErrorCode::InvalidArgument,"Invalid Hub settings."); const auto r=store_.save(settings); if (!r.ok()) return r; current_=std::move(settings); return Result<void>::success(); }
}
