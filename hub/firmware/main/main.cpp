#include "LynqApp.hpp"
#include "BoardPort.hpp"
#include "esp_log.h"

namespace {
constexpr const char* kTag = "LYNQ_MAIN";
}

extern "C" void app_main(void) {
    ESP_LOGI(kTag, "Starting LYNQ Hub firmware v0.2.0-alpha");

    auto& board = lynq::hub::BoardPort::instance();
    if (!board.initialize()) {
        ESP_LOGE(kTag, "Board initialization failed");
        return;
    }

    lynq::hub::LynqApp app(board);
    app.run();
}
