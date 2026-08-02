#include "RevANodeApp.h"
#include "AtomS3LiteBoard.h"
#include "nvs_flash.h"
#include "esp_err.h"

extern "C" void app_main() {
    esp_err_t result = nvs_flash_init();
    if (result == ESP_ERR_NVS_NO_FREE_PAGES ||
        result == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        result = nvs_flash_init();
    }
    ESP_ERROR_CHECK(result);

    static lynq::rev_a::AtomS3LiteBoard board;
    static lynq::rev_a::RevANodeApp app(board);
    if (app.initialize()) app.run();
}
