#pragma once

#include "hardware/NodeOneBoard.h"

namespace lynq::node_one {

class NodeOneApp {
public:
    explicit NodeOneApp(NodeOneBoard& board);

    bool initialize();
    void run();

private:
    NodeOneBoard& board_;
};

} // namespace lynq::node_one
