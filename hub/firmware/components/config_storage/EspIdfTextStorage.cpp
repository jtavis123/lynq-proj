#include "EspIdfTextStorage.h"

namespace lynq::hub {

Result<void> EspIdfTextStorage::initialize() {
    // Mount SPIFFS/LittleFS and create the LYNQ configuration directory
    // during physical Hub integration.
    return Result<void>::success();
}

Result<std::string> EspIdfTextStorage::read(std::string_view) {
    return Result<std::string>::failure(
        ErrorCode::Unsupported,
        "ESP-IDF JSON file loading awaits Hub filesystem integration.");
}

Result<void> EspIdfTextStorage::write(
    std::string_view,
    std::string_view) {
    return Result<void>::failure(
        ErrorCode::Unsupported,
        "ESP-IDF JSON file saving awaits Hub filesystem integration.");
}

Result<void> EspIdfTextStorage::remove(std::string_view) {
    return Result<void>::failure(
        ErrorCode::Unsupported,
        "ESP-IDF JSON file removal awaits Hub filesystem integration.");
}

} // namespace lynq::hub
