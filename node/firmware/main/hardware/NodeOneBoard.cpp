#include "NodeOneBoard.h"

#include "esp_log.h"

namespace lynq::node_one {
namespace {
constexpr char kTag[] = "NodeOneBoard";
}

bool NodeOneBoard::initialize() {
    ESP_LOGI(kTag, "Node One hardware abstraction initialized");
    // Concrete GPIO assignments remain isolated here until the exact
    // off-the-shelf Node One modules and cable harnesses are bench-validated.
    return true;
}

void NodeOneBoard::service() {
    // Service non-blocking board-level work.
}

void NodeOneBoard::setStatus(NodeStatus status) {
    status_ = status;
    ESP_LOGI(kTag, "Status changed to %d", static_cast<int>(status_));
}

} // namespace lynq::node_one
