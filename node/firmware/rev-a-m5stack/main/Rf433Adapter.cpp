#include "esp_log.h"
namespace { constexpr char kTag[] = "RF433"; }
extern "C" void lynq_rev_a_rf433_integration_gate() {
    // Bind RF433T output and RF433R pulse capture to RMT-capable GPIOs after
    // confirming the official Atomic Port ABC pin map on the received hardware.
    ESP_LOGI(kTag, "RF433 adapter integration gate");
}
