#pragma once

#include <cstddef>
#include <functional>
#include <mutex>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace lynq {

struct Event {
    std::string type;
    std::string source;
    std::string payload;
};

class EventBus {
public:
    using Handler = std::function<void(const Event&)>;
    using SubscriptionId = std::size_t;

    SubscriptionId subscribe(std::string eventType, Handler handler);
    bool unsubscribe(std::string_view eventType, SubscriptionId id);
    void publish(const Event& event) const;
    [[nodiscard]] std::size_t subscriberCount(std::string_view eventType) const;

private:
    struct Subscription {
        SubscriptionId id;
        Handler handler;
    };

    mutable std::mutex mutex_;
    std::unordered_map<std::string, std::vector<Subscription>> subscribers_;
    SubscriptionId nextId_{1};
};

} // namespace lynq
