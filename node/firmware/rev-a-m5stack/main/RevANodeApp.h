#pragma once
#include "AtomS3LiteBoard.h"

namespace lynq::rev_a {
class RevANodeApp {
public:
    explicit RevANodeApp(AtomS3LiteBoard& board);
    bool initialize();
    void run();
private:
    AtomS3LiteBoard& board_;
};
}
