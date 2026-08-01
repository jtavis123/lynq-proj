#include "LvglUiPort.h"

#include "esp_log.h"

namespace lynq::hub {
namespace {
constexpr char kTag[] = "LYNQ_LVGL";
}

bool LvglUiPort::initialize() {
    // Attach LVGL to the Waveshare display and touch drivers during physical
    // bring-up. Theme tokens and page models are ready now.
    ESP_LOGI(kTag, "LVGL UI port initialized");
    ready_ = true;
    return true;
}

void LvglUiPort::buildApplicationShell(
    const ui::UiApplicationModel& model) {
    if (!ready_) return;

    ESP_LOGI(kTag,
             "Build shell with %u primary navigation entries",
             static_cast<unsigned>(model.primaryNavigation().size()));

    // Planned 800x480 shell:
    // - top status bar
    // - scrollable content surface
    // - persistent bottom navigation
    // - modal overlay layer
}

void LvglUiPort::refreshHome(
    const ui::HomeDashboardModel& home) {
    if (!ready_) return;

    ESP_LOGI(kTag,
             "Refresh Home: %u favorites, %u scenes, %u alerts",
             static_cast<unsigned>(home.favorites.size()),
             static_cast<unsigned>(home.scenes.size()),
             static_cast<unsigned>(home.alerts.size()));
}

} // namespace lynq::hub
