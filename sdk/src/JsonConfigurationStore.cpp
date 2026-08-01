#include "lynq/storage/JsonConfigurationStore.h"

#include <cctype>

namespace lynq::storage {

JsonConfigurationStore::JsonConfigurationStore(ITextStorage& storage)
    : storage_(storage) {}

Result<std::string> JsonConfigurationStore::load(
    std::string_view documentName) {
    if (documentName.empty()) {
        return Result<std::string>::failure(
            ErrorCode::InvalidArgument, "Document name is required.");
    }
    return storage_.read(documentName);
}

Result<void> JsonConfigurationStore::save(
    std::string_view documentName,
    std::string_view json) {
    if (documentName.empty()) {
        return Result<void>::failure(
            ErrorCode::InvalidArgument, "Document name is required.");
    }
    if (!looksLikeJson(json)) {
        return Result<void>::failure(
            ErrorCode::InvalidArgument, "Configuration must be JSON.");
    }
    return storage_.write(documentName, json);
}

Result<void> JsonConfigurationStore::erase(
    std::string_view documentName) {
    if (documentName.empty()) {
        return Result<void>::failure(
            ErrorCode::InvalidArgument, "Document name is required.");
    }
    return storage_.remove(documentName);
}

bool JsonConfigurationStore::looksLikeJson(std::string_view value) {
    std::size_t first = 0;
    while (first < value.size() &&
           std::isspace(static_cast<unsigned char>(value[first]))) {
        ++first;
    }
    if (first == value.size()) return false;

    std::size_t last = value.size();
    while (last > first &&
           std::isspace(static_cast<unsigned char>(value[last - 1]))) {
        --last;
    }

    const char open = value[first];
    const char close = value[last - 1];
    return (open == '{' && close == '}') ||
           (open == '[' && close == ']');
}

} // namespace lynq::storage
