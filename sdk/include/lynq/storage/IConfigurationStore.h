#pragma once

#include "lynq/core/Result.h"

#include <optional>
#include <string>

namespace lynq::storage {

class IConfigurationStore {
public:
    virtual ~IConfigurationStore() = default;
    virtual Result<void> put(const std::string& key, const std::string& value) = 0;
    virtual Result<std::optional<std::string>> get(const std::string& key) const = 0;
    virtual Result<void> erase(const std::string& key) = 0;
};

} // namespace lynq::storage
