#include "HardwareDiagnostics.h"
#include "esp_log.h"

extern "C" void app_main(void) {
    static constexpr const char* TAG = "LYNQ_HUB";
    ESP_LOGI(TAG, "LYNQ Hub physical bring-up v1.7.0");

    lynq::hub::HardwareDiagnostics diagnostics;
    const auto report = diagnostics.run();

    ESP_LOGI(TAG, "chip=%s cores=%d flash=%uMB psram=%uKB",
             report.chipModel.c_str(), report.coreCount,
             report.flashBytes / (1024U * 1024U),
             report.psramBytes / 1024U);

    if (!report.minimumMemoryPassed) {
        ESP_LOGE(TAG, "Memory validation failed; display bring-up is blocked.");
        return;
    }

    ESP_LOGI(TAG, "Base hardware diagnostics passed.");
    ESP_LOGW(TAG, "LCD/touch initialization remains gated on the exact Waveshare Type-B BSP example.");
}
