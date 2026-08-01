#include "lynq/node/NodeManager.h"

namespace lynq::node {

NodeManager::NodeManager(INodeTransport& transport, NodeRegistry& registry, EventBus& events)
    : transport_(transport), registry_(registry), events_(events) {}

Result<void> NodeManager::initialize() {
    transport_.setAdvertisementCallback([this](const NodeAdvertisement& advertisement) {
        onAdvertisement(advertisement);
    });
    transport_.setHeartbeatCallback([this](const Heartbeat& heartbeat) {
        onHeartbeat(heartbeat);
    });
    return transport_.initialize();
}

Result<void> NodeManager::startDiscovery() {
    events_.publish({"node.discovery.started", "NodeManager", {}});
    return transport_.startDiscovery();
}

Result<void> NodeManager::stopDiscovery() {
    const auto result = transport_.stopDiscovery();
    if (result.ok()) events_.publish({"node.discovery.stopped", "NodeManager", {}});
    return result;
}

Result<PairingResult> NodeManager::pair(const PairingRequest& request) {
    registry_.setState(request.nodeId, NodeState::Pairing);
    events_.publish({"node.pairing.started", "NodeManager", request.nodeId});
    auto result = transport_.pair(request);
    if (!result.ok()) {
        registry_.setState(request.nodeId, NodeState::Error);
        events_.publish({"node.pairing.failed", "NodeManager", request.nodeId});
        return result;
    }
    registry_.markTrusted(request.nodeId, result.value().paired);
    events_.publish({result.value().paired ? "node.paired" : "node.pairing.failed",
                     "NodeManager", request.nodeId});
    return result;
}

Result<void> NodeManager::unpair(const std::string& nodeId) {
    const auto result = transport_.unpair(nodeId);
    if (result.ok()) {
        registry_.markTrusted(nodeId, false);
        events_.publish({"node.unpaired", "NodeManager", nodeId});
    }
    return result;
}

std::size_t NodeManager::markStaleNodesOffline(std::chrono::steady_clock::time_point now,
                                               std::chrono::seconds timeout) {
    std::size_t changed = 0;
    for (const auto& node : registry_.all()) {
        if (!node.trusted || node.state == NodeState::Offline) continue;
        if (node.lastSeen.time_since_epoch().count() == 0) continue;
        if (now - node.lastSeen > timeout && registry_.setState(node.identity.id, NodeState::Offline)) {
            ++changed;
            events_.publish({"node.offline", "NodeManager", node.identity.id});
        }
    }
    return changed;
}

std::vector<NodeRecord> NodeManager::nodes() const { return registry_.all(); }

void NodeManager::onAdvertisement(const NodeAdvertisement& advertisement) {
    const bool existed = registry_.find(advertisement.identity.id).has_value();
    registry_.upsertAdvertisement(advertisement);
    events_.publish({existed ? "node.updated" : "node.discovered",
                     "NodeManager", advertisement.identity.id});
}

void NodeManager::onHeartbeat(const Heartbeat& heartbeat) {
    if (!registry_.applyHeartbeat(heartbeat)) return;
    events_.publish({"node.heartbeat", "NodeManager", heartbeat.nodeId});
}

} // namespace lynq::node
