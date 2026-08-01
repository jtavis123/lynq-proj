#include "HubUiController.h"

#include "esp_log.h"

namespace lynq::hub {
namespace {
constexpr char kTag[] = "LYNQ_UI";
}

HubUiController::HubUiController(ui::UiApplicationModel& model)
    : model_(model) {}

bool HubUiController::initialize() {
    ESP_LOGI(kTag, "Initializing LYNQ touchscreen application");
    initialized_ = true;
    render();
    return true;
}

void HubUiController::render() {
    if (!initialized_) return;

    // The concrete LVGL object tree is created by LvglUiPort.
    // This controller deliberately depends only on the portable UI model.
    ESP_LOGI(kTag, "Render page %d",
             static_cast<int>(model_.currentRoute().page));
}

void HubUiController::onPrimaryNavigation(ui::PageId page) {
    if (model_.navigate(page).ok()) render();
}

void HubUiController::onBack() {
    if (model_.goBack()) render();
}

} // namespace lynq::hub
