#include "HardwareDiagnostics.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_heap_caps.h"
#include "esp_psram.h"

namespace lynq::hub {
HardwareReport HardwareDiagnostics::run() const {
    HardwareReport report;
    esp_chip_info_t info{};
    esp_chip_info(&info);
    report.chipModel = "ESP32-S3";
    report.coreCount = info.cores;
    std::uint32_t flash = 0;
    esp_flash_get_size(nullptr, &flash);
    report.flashBytes = flash;
    report.psramBytes = static_cast<std::uint32_t>(esp_psram_get_size());
    report.freeHeapBytes = static_cast<std::uint32_t>(heap_caps_get_free_size(MALLOC_CAP_8BIT));
    report.minimumMemoryPassed = report.flashBytes >= 8U * 1024U * 1024U && report.psramBytes > 0;
    return report;
}
}
