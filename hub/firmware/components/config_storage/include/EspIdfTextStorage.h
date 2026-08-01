#pragma once

#include "lynq/storage/JsonConfigurationStore.h"

#include <string>
#include <string_view>

namespace lynq::hub {

class EspIdfTextStorage final : public storage::ITextStorage {
public:
    Result<void> initialize();

    Result<std::string> read(std::string_view key) override;
    Result<void> write(std::string_view key,
                       std::string_view value) override;
    Result<void> remove(std::string_view key) override;

private:
    std::string basePath_{"/lynq"};
};

} // namespace lynq::hub
