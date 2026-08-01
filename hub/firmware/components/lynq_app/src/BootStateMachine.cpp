#include "BootStateMachine.hpp"

namespace lynq::hub {

bool BootStateMachine::validTransition(BootState next) const {
    if (next == BootState::Recovery) return true;
    switch (state_) {
        case BootState::PowerOn: return next == BootState::BoardInit;
        case BootState::BoardInit: return next == BootState::ServicesInit;
        case BootState::ServicesInit: return next == BootState::UiInit;
        case BootState::UiInit: return next == BootState::Ready;
        case BootState::Ready: return false;
        case BootState::Recovery: return next == BootState::PowerOn;
    }
    return false;
}

bool BootStateMachine::transitionTo(BootState next) {
    if (!validTransition(next)) return false;
    state_ = next;
    return true;
}

}  // namespace lynq::hub
