#pragma once

namespace lynq::node_one {

enum class NodeStatus {
    Booting,
    Ready,
    Pairing,
    Learning,
    Transmitting,
    Updating,
    Error
};

class NodeOneBoard {
public:
    bool initialize();
    void service();
    void setStatus(NodeStatus status);

private:
    NodeStatus status_{NodeStatus::Booting};
};

} // namespace lynq::node_one
