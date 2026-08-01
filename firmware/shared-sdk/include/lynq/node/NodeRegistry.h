#pragma once

#include <mutex>
#include <optional>
#include <string_view>
#include <unordered_map>
#include <vector>

#include "lynq/node/NodeTypes.h"

namespace lynq::node {

class NodeRegistry {
public:
    void upsertAdvertisement(const NodeAdvertisement& advertisement);
    bool applyHeartbeat(const Heartbeat& heartbeat);
    bool markTrusted(std::string_view nodeId, bool trusted);
    bool setState(std::string_view nodeId, NodeState state);
    [[nodiscard]] std::optional<NodeRecord> find(std::string_view nodeId) const;
    [[nodiscard]] std::vector<NodeRecord> all() const;
    [[nodiscard]] std::size_t size() const;

private:
    mutable std::mutex mutex_;
    std::unordered_map<std::string, NodeRecord> records_;
};

} // namespace lynq::node
