#pragma once

#include <array>
#include <cstdint>
#include <optional>
#include <string>
#include <string_view>

namespace lynq {

class UUID {
public:
    UUID() = default;
    explicit UUID(std::array<std::uint8_t, 16> bytes) : bytes_(bytes) {}

    static UUID random();
    static std::optional<UUID> parse(std::string_view text);
    [[nodiscard]] std::string toString() const;
    [[nodiscard]] const std::array<std::uint8_t, 16>& bytes() const noexcept { return bytes_; }
    auto operator<=>(const UUID&) const = default;

private:
    std::array<std::uint8_t, 16> bytes_{};
};

} // namespace lynq
