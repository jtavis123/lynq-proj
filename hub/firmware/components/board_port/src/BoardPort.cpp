#include "BoardPort.hpp"

#include "esp_log.h"
#include "esp_timer.h"

namespace lynq::hub {
namespace {
constexpr const char* kTag = "LYNQ_BOARD";
}

BoardPort& BoardPort::instance() {
    static BoardPort port;
    return port;
}

bool BoardPort::initialize() {
    ESP_LOGI(kTag, "Initializing Waveshare ESP32-S3-Touch-LCD-4.3B-BOX port");
    displayReady_ = initializeDisplay();
    touchReady_ = initializeTouch();
    return displayReady_ && touchReady_;
}

bool BoardPort::initializeDisplay() {
    // Integration point for Waveshare's official RGB LCD/LVGL BSP.
    // Kept isolated so the application layer does not depend on GPIOs,
    // timing values, panel revisions, or touch-controller details.
    ESP_LOGW(kTag, "Display BSP adapter pending physical-board validation");
    return true;
}

bool BoardPort::initializeTouch() {
    // Integration point for the official capacitive-touch driver.
    ESP_LOGW(kTag, "Touch BSP adapter pending physical-board validation");
    return true;
}

void BoardPort::service() {
    // Board-level periodic work belongs here.
}

std::uint64_t BoardPort::uptimeMilliseconds() const {
    return static_cast<std::uint64_t>(esp_timer_get_time() / 1000);
}

}  // namespace lynq::hub
