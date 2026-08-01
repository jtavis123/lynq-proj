#pragma once

#include <cstdint>

namespace lynq::hub {

enum class BootState : std::uint8_t {
    PowerOn,
    BoardInit,
    ServicesInit,
    UiInit,
    Ready,
    Recovery
};

class BootStateMachine {
public:
    BootState state() const { return state_; }
    bool transitionTo(BootState next);

private:
    bool validTransition(BootState next) const;
    BootState state_{BootState::PowerOn};
};

}  // namespace lynq::hub
