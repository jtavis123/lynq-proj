#include "AtomS3LiteBoard.h"
#include "esp_log.h"

namespace lynq::rev_a {
namespace { constexpr char kTag[] = "AtomS3Lite"; }

bool AtomS3LiteBoard::initialize() {
    // Integration gate: use the official M5Stack AtomS3-Lite board package
    // to bind the RGB LED, front button, USB and Grove GPIO assignments.
    ESP_LOGI(kTag, "AtomS3-Lite board boundary initialized");
    return true;
}

void AtomS3LiteBoard::setStatusReady() { ESP_LOGI(kTag, "status=ready"); }
void AtomS3LiteBoard::setStatusPairing() { ESP_LOGI(kTag, "status=pairing"); }
void AtomS3LiteBoard::setStatusError() { ESP_LOGE(kTag, "status=error"); }
bool AtomS3LiteBoard::pairingButtonPressed() const { return false; }

} // namespace lynq::rev_a
