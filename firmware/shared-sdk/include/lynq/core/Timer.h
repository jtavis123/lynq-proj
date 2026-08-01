#pragma once

#include <atomic>
#include <chrono>
#include <functional>
#include <memory>
#include <mutex>
#include <thread>
#include <unordered_map>

namespace lynq {

class TimerService {
public:
    using TimerId = std::size_t;
    using Callback = std::function<void()>;

    ~TimerService();
    TimerId scheduleOnce(std::chrono::milliseconds delay, Callback callback);
    TimerId scheduleRepeating(std::chrono::milliseconds interval, Callback callback);
    bool cancel(TimerId id);
    void cancelAll();

private:
    struct TimerControl { std::atomic<bool> cancelled{false}; };
    TimerId schedule(std::chrono::milliseconds interval, Callback callback, bool repeating);

    std::mutex mutex_;
    std::unordered_map<TimerId, std::shared_ptr<TimerControl>> timers_;
    TimerId nextId_{1};
};

} // namespace lynq
