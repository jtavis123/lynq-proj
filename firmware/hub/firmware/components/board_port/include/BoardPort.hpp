#pragma once

#include <cstdint>

namespace lynq::hub {

class BoardPort {
public:
    static BoardPort& instance();

    bool initialize();
    void service();
    std::uint64_t uptimeMilliseconds() const;

    bool displayReady() const { return displayReady_; }
    bool touchReady() const { return touchReady_; }

private:
    BoardPort() = default;

    bool initializeDisplay();
    bool initializeTouch();

    bool displayReady_{false};
    bool touchReady_{false};
};

}  // namespace lynq::hub
