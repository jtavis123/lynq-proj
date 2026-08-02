#pragma once
#include <cstdint>

namespace lynq::node {
struct RevABoardStatus {
    bool rgbLedPassed{false};
    bool buttonPassed{false};
    bool groveBusReady{false};
    bool irReady{false};
    bool rf433TxReady{false};
    bool rf433RxReady{false};
};
class RevABoard {
public:
    RevABoardStatus selfTest();
};
}
