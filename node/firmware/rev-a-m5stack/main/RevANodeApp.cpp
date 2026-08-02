#include "RevANodeApp.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

namespace lynq::rev_a {
namespace { constexpr char kTag[] = "RevANodeApp"; }

RevANodeApp::RevANodeApp(AtomS3LiteBoard& board) : board_(board) {}

bool RevANodeApp::initialize() {
    if (!board_.initialize()) return false;
    // Next physical integration steps:
    // 1. Wi-Fi/BLE provisioning
    // 2. Hub discovery and secure pairing
    // 3. Port A IR Unit driver
    // 4. Port B RF433T driver
    // 5. Port C RF433R driver
    // 6. heartbeat and OTA tasks
    board_.setStatusReady();
    return true;
}

void RevANodeApp::run() {
    while (true) {
        if (board_.pairingButtonPressed()) board_.setStatusPairing();
        vTaskDelay(pdMS_TO_TICKS(25));
    }
}
}
