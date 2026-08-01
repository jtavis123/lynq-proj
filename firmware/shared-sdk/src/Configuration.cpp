#include "lynq/core/Configuration.h"

namespace lynq {

void Configuration::set(std::string key, ConfigValue value) {
    std::lock_guard lock(mutex_);
    values_.insert_or_assign(std::move(key), std::move(value));
}

bool Configuration::contains(std::string_view key) const {
    std::lock_guard lock(mutex_);
    return values_.contains(std::string(key));
}

bool Configuration::erase(std::string_view key) {
    std::lock_guard lock(mutex_);
    return values_.erase(std::string(key)) > 0;
}

} // namespace lynq
