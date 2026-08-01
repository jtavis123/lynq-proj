#include "lynq/core/Timer.h"

namespace lynq {

TimerService::~TimerService() { cancelAll(); }

TimerService::TimerId TimerService::scheduleOnce(std::chrono::milliseconds delay, Callback callback) {
    return schedule(delay, std::move(callback), false);
}

TimerService::TimerId TimerService::scheduleRepeating(std::chrono::milliseconds interval, Callback callback) {
    return schedule(interval, std::move(callback), true);
}

TimerService::TimerId TimerService::schedule(std::chrono::milliseconds interval, Callback callback, bool repeating) {
    const auto control = std::make_shared<TimerControl>();
    TimerId id;
    {
        std::lock_guard lock(mutex_);
        id = nextId_++;
        timers_[id] = control;
    }

    std::thread([this, id, control, interval, callback = std::move(callback), repeating]() mutable {
        do {
            std::this_thread::sleep_for(interval);
            if (control->cancelled.load()) break;
            callback();
        } while (repeating && !control->cancelled.load());

        std::lock_guard lock(mutex_);
        timers_.erase(id);
    }).detach();
    return id;
}

bool TimerService::cancel(TimerId id) {
    std::lock_guard lock(mutex_);
    const auto it = timers_.find(id);
    if (it == timers_.end()) return false;
    it->second->cancelled.store(true);
    timers_.erase(it);
    return true;
}

void TimerService::cancelAll() {
    std::lock_guard lock(mutex_);
    for (auto& [_, timer] : timers_) timer->cancelled.store(true);
    timers_.clear();
}

} // namespace lynq
