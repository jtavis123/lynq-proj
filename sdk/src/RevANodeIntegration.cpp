#include "lynq/node/RevANodeIntegration.h"

#include <algorithm>
#include <utility>

namespace lynq::node {

RevANodeCoordinator::RevANodeCoordinator(
    IRevANodeTransport& transport,
    std::uint64_t offlineAfterMs)
    : transport_(transport), offlineAfterMs_(offlineAfterMs) {}

Result<void> RevANodeCoordinator::startDiscovery() {
    return transport_.beginDiscovery();
}

Result<void> RevANodeCoordinator::stopDiscovery() {
    return transport_.stopDiscovery();
}

Result<void> RevANodeCoordinator::observeAnnouncement(
    RevANodeAnnouncement announcement) {
    if (announcement.nodeId.empty() || announcement.displayName.empty()) {
        return Result<void>::failure(
            ErrorCode::InvalidArgument,
            "Node ID and display name are required.");
    }
    if (announcement.hardwareProfile != "rev-a-m5stack") {
        return Result<void>::failure(
            ErrorCode::Unsupported,
            "Unsupported Node hardware profile.");
    }

    auto& status = nodes_[announcement.nodeId];
    const bool paired = status.paired;
    const auto heartbeat = status.heartbeat;
    status.announcement = std::move(announcement);
    status.paired = paired;
    status.heartbeat = heartbeat;
    return Result<void>::success();
}

Result<void> RevANodeCoordinator::pair(
    const std::string& nodeId,
    const std::string& pairingCode) {
    const auto it = nodes_.find(nodeId);
    if (it == nodes_.end()) {
        return Result<void>::failure(
            ErrorCode::NotFound, "Node has not been discovered.");
    }
    if (pairingCode.size() < 6) {
        return Result<void>::failure(
            ErrorCode::InvalidArgument,
            "Pairing code must contain at least six characters.");
    }

    const auto result = transport_.requestPairing(nodeId, pairingCode);
    if (!result.ok()) return result;
    it->second.paired = true;
    return Result<void>::success();
}

Result<void> RevANodeCoordinator::ingestHeartbeat(
    RevANodeHeartbeat heartbeat) {
    const auto it = nodes_.find(heartbeat.nodeId);
    if (it == nodes_.end()) {
        return Result<void>::failure(
            ErrorCode::NotFound,
            "Heartbeat received from an unknown Node.");
    }
    if (!it->second.paired) {
        return Result<void>::failure(
            ErrorCode::AccessDenied,
            "Heartbeat received from an unpaired Node.");
    }

    it->second.heartbeat = std::move(heartbeat);
    it->second.online = true;
    return Result<void>::success();
}

void RevANodeCoordinator::evaluateOnlineState(
    std::uint64_t nowEpochMs) {
    for (auto& [_, status] : nodes_) {
        if (!status.paired || status.heartbeat.observedAtEpochMs == 0) {
            status.online = false;
            continue;
        }
        status.online = nowEpochMs >= status.heartbeat.observedAtEpochMs &&
            nowEpochMs - status.heartbeat.observedAtEpochMs <= offlineAfterMs_;
    }
}

std::optional<RevANodeStatus> RevANodeCoordinator::find(
    const std::string& nodeId) const {
    const auto it = nodes_.find(nodeId);
    if (it == nodes_.end()) return std::nullopt;
    return it->second;
}

std::vector<RevANodeStatus> RevANodeCoordinator::list() const {
    std::vector<RevANodeStatus> result;
    result.reserve(nodes_.size());
    for (const auto& [_, status] : nodes_) result.push_back(status);
    std::sort(result.begin(), result.end(), [](const auto& a, const auto& b) {
        return a.announcement.displayName < b.announcement.displayName;
    });
    return result;
}

} // namespace lynq::node
