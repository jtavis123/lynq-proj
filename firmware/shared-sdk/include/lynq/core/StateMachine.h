#pragma once

#include <functional>
#include <optional>
#include <unordered_map>
#include <utility>

namespace lynq {

template <typename State>
class StateMachine {
public:
    using Guard = std::function<bool()>;
    using Action = std::function<void()>;

    explicit StateMachine(State initialState) : current_(initialState) {}

    void allow(State from, State to, Guard guard = {}, Action action = {}) {
        transitions_[Key{from, to}] = Transition{std::move(guard), std::move(action)};
    }

    [[nodiscard]] State current() const noexcept { return current_; }

    bool transitionTo(State next) {
        const auto it = transitions_.find(Key{current_, next});
        if (it == transitions_.end()) return false;
        if (it->second.guard && !it->second.guard()) return false;
        if (it->second.action) it->second.action();
        current_ = next;
        return true;
    }

private:
    struct Key {
        State from;
        State to;
        bool operator==(const Key&) const = default;
    };

    struct KeyHash {
        std::size_t operator()(const Key& key) const noexcept {
            const auto h1 = std::hash<State>{}(key.from);
            const auto h2 = std::hash<State>{}(key.to);
            return h1 ^ (h2 << 1U);
        }
    };

    struct Transition { Guard guard; Action action; };
    State current_;
    std::unordered_map<Key, Transition, KeyHash> transitions_;
};

} // namespace lynq
