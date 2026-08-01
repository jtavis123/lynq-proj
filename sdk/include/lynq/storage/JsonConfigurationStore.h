#pragma once

#include "lynq/core/Result.h"

#include <functional>
#include <string>
#include <string_view>

namespace lynq::storage {

class ITextStorage {
public:
    virtual ~ITextStorage() = default;
    virtual Result<std::string> read(std::string_view key) = 0;
    virtual Result<void> write(std::string_view key,
                               std::string_view value) = 0;
    virtual Result<void> remove(std::string_view key) = 0;
};

class JsonConfigurationStore {
public:
    explicit JsonConfigurationStore(ITextStorage& storage);

    Result<std::string> load(std::string_view documentName);
    Result<void> save(std::string_view documentName,
                      std::string_view json);
    Result<void> erase(std::string_view documentName);

    static bool looksLikeJson(std::string_view value);

private:
    ITextStorage& storage_;
};

} // namespace lynq::storage
