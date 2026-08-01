#include "lynq/core/EventBus.h"

#include <algorithm>

namespace lynq {

EventBus::SubscriptionId EventBus::subscribe(std::string eventType, Handler handler) {
    std::lock_guard lock(mutex_);
    const auto id = nextId_++;
    subscribers_[std::move(eventType)].push_back(Subscription{id, std::move(handler)});
    return id;
}

bool EventBus::unsubscribe(std::string_view eventType, SubscriptionId id) {
    std::lock_guard lock(mutex_);
    auto it = subscribers_.find(std::string(eventType));
    if (it == subscribers_.end()) return false;
    auto& list = it->second;
    const auto oldSize = list.size();
    std::erase_if(list, [id](const Subscription& s) { return s.id == id; });
    if (list.empty()) subscribers_.erase(it);
    return list.size() != oldSize;
}

void EventBus::publish(const Event& event) const {
    std::vector<Subscription> copy;
    {
        std::lock_guard lock(mutex_);
        const auto it = subscribers_.find(event.type);
        if (it == subscribers_.end()) return;
        copy = it->second;
    }
    for (const auto& subscription : copy) subscription.handler(event);
}

std::size_t EventBus::subscriberCount(std::string_view eventType) const {
    std::lock_guard lock(mutex_);
    const auto it = subscribers_.find(std::string(eventType));
    return it == subscribers_.end() ? 0U : it->second.size();
}

} // namespace lynq
