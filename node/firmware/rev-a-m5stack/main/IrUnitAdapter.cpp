#include "esp_log.h"
namespace { constexpr char kTag[] = "IRUnit"; }
extern "C" void lynq_rev_a_ir_integration_gate() {
    // Bind IR receive/transmit to ESP-IDF RMT after loading the official M5Stack
    // IR Unit example and validating polarity on physical hardware.
    ESP_LOGI(kTag, "IR Unit adapter integration gate");
}
