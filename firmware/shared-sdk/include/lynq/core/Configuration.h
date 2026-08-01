#pragma once

#include <mutex>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>
#include <variant>

namespace lynq {

using ConfigValue = std::variant<bool, std::int64_t, double, std::string>;

class Configuration {
public:
    void set(std::string key, ConfigValue value);
    [[nodiscard]] bool contains(std::string_view key) const;
    bool erase(std::string_view key);

    template <typename T>
    [[nodiscard]] std::optional<T> get(std::string_view key) const {
        std::lock_guard lock(mutex_);
        const auto it = values_.find(std::string(key));
        if (it == values_.end()) return std::nullopt;
        if (const auto* value = std::get_if<T>(&it->second)) return *value;
        return std::nullopt;
    }

private:
    mutable std::mutex mutex_;
    std::unordered_map<std::string, ConfigValue> values_;
};

} // namespace lynq
