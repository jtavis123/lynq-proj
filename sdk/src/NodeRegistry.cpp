#include "lynq/node/NodeRegistry.h"

#include <chrono>

namespace lynq::node {

void NodeRegistry::upsertAdvertisement(const NodeAdvertisement& advertisement) {
    std::lock_guard lock(mutex_);
    auto& record = records_[advertisement.identity.id];
    const bool wasTrusted = record.trusted;
    record.identity = advertisement.identity;
    record.endpoint = advertisement.endpoint;
    record.capabilities = advertisement.capabilities;
    record.state = wasTrusted ? NodeState::Online : NodeState::Discovered;
    record.lastSeen = std::chrono::steady_clock::now();
    record.trusted = wasTrusted;
}

bool NodeRegistry::applyHeartbeat(const Heartbeat& heartbeat) {
    std::lock_guard lock(mutex_);
    const auto it = records_.find(heartbeat.nodeId);
    if (it == records_.end()) return false;
    it->second.health = heartbeat.health;
    it->second.lastSeen = std::chrono::steady_clock::now();
    if (it->second.trusted) it->second.state = NodeState::Online;
    return true;
}

bool NodeRegistry::markTrusted(std::string_view nodeId, bool trusted) {
    std::lock_guard lock(mutex_);
    const auto it = records_.find(std::string(nodeId));
    if (it == records_.end()) return false;
    it->second.trusted = trusted;
    it->second.state = trusted ? NodeState::Online : NodeState::Discovered;
    return true;
}

bool NodeRegistry::setState(std::string_view nodeId, NodeState state) {
    std::lock_guard lock(mutex_);
    const auto it = records_.find(std::string(nodeId));
    if (it == records_.end()) return false;
    it->second.state = state;
    return true;
}

std::optional<NodeRecord> NodeRegistry::find(std::string_view nodeId) const {
    std::lock_guard lock(mutex_);
    const auto it = records_.find(std::string(nodeId));
    if (it == records_.end()) return std::nullopt;
    return it->second;
}

std::vector<NodeRecord> NodeRegistry::all() const {
    std::lock_guard lock(mutex_);
    std::vector<NodeRecord> result;
    result.reserve(records_.size());
    for (const auto& [_, record] : records_) result.push_back(record);
    return result;
}

std::size_t NodeRegistry::size() const {
    std::lock_guard lock(mutex_);
    return records_.size();
}

} // namespace lynq::node
