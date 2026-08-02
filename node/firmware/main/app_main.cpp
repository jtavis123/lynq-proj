#include "RevABoard.h"
#include "esp_chip_info.h"
#include "esp_log.h"

extern "C" void app_main(void) {
    static constexpr const char* TAG = "LYNQ_NODE";
    esp_chip_info_t info{};
    esp_chip_info(&info);
    ESP_LOGI(TAG, "LYNQ Rev A Node bring-up v1.7.0, cores=%d", info.cores);
    lynq::node::RevABoard board;
    const auto status = board.selfTest();
    ESP_LOGI(TAG, "board adapter loaded; physical pin validation pending");
    (void)status;
}
