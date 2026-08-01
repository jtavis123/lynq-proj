#include "NodeOneApp.h"
#include "hardware/NodeOneBoard.h"

#include "esp_log.h"
#include "nvs_flash.h"

extern "C" void app_main() {
    esp_err_t result = nvs_flash_init();
    if (result == ESP_ERR_NVS_NO_FREE_PAGES ||
        result == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        result = nvs_flash_init();
    }
    ESP_ERROR_CHECK(result);

    static lynq::node_one::NodeOneBoard board;
    static lynq::node_one::NodeOneApp app(board);

    if (!app.initialize()) {
        ESP_LOGE("app_main", "Node One failed to initialize");
        return;
    }

    app.run();
}
