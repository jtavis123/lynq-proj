#include "NodeOneApp.h"

#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

namespace lynq::node_one {
namespace {
constexpr char kTag[] = "NodeOneApp";
}

NodeOneApp::NodeOneApp(NodeOneBoard& board) : board_(board) {}

bool NodeOneApp::initialize() {
    ESP_LOGI(kTag, "Initializing LYNQ Node One");
    if (!board_.initialize()) {
        ESP_LOGE(kTag, "Board initialization failed");
        return false;
    }

    board_.setStatus(NodeStatus::Booting);
    // Wi-Fi provisioning, secure Hub pairing, transport, RF/IR services,
    // battery monitoring and OTA are attached here in later releases.
    board_.setStatus(NodeStatus::Ready);
    return true;
}

void NodeOneApp::run() {
    ESP_LOGI(kTag, "Node One ready");
    while (true) {
        board_.service();
        vTaskDelay(pdMS_TO_TICKS(25));
    }
}

} // namespace lynq::node_one
