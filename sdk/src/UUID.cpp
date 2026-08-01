#include "lynq/core/UUID.h"

#include <array>
#include <iomanip>
#include <random>
#include <sstream>

namespace lynq {

UUID UUID::random() {
    std::random_device rd;
    std::mt19937_64 generator(rd());
    std::uniform_int_distribution<int> distribution(0, 255);
    std::array<std::uint8_t, 16> bytes{};
    for (auto& byte : bytes) byte = static_cast<std::uint8_t>(distribution(generator));
    bytes[6] = static_cast<std::uint8_t>((bytes[6] & 0x0F) | 0x40);
    bytes[8] = static_cast<std::uint8_t>((bytes[8] & 0x3F) | 0x80);
    return UUID(bytes);
}

std::optional<UUID> UUID::parse(std::string_view text) {
    if (text.size() != 36 || text[8] != '-' || text[13] != '-' || text[18] != '-' || text[23] != '-') {
        return std::nullopt;
    }
    auto hex = [](char c) -> int {
        if (c >= '0' && c <= '9') return c - '0';
        if (c >= 'a' && c <= 'f') return c - 'a' + 10;
        if (c >= 'A' && c <= 'F') return c - 'A' + 10;
        return -1;
    };
    std::array<std::uint8_t, 16> bytes{};
    std::size_t out = 0;
    for (std::size_t i = 0; i < text.size();) {
        if (text[i] == '-') { ++i; continue; }
        if (i + 1 >= text.size() || out >= bytes.size()) return std::nullopt;
        const int hi = hex(text[i]);
        const int lo = hex(text[i + 1]);
        if (hi < 0 || lo < 0) return std::nullopt;
        bytes[out++] = static_cast<std::uint8_t>((hi << 4) | lo);
        i += 2;
    }
    return out == bytes.size() ? std::optional<UUID>(UUID(bytes)) : std::nullopt;
}

std::string UUID::toString() const {
    std::ostringstream stream;
    stream << std::hex << std::setfill('0');
    for (std::size_t i = 0; i < bytes_.size(); ++i) {
        if (i == 4 || i == 6 || i == 8 || i == 10) stream << '-';
        stream << std::setw(2) << static_cast<int>(bytes_[i]);
    }
    return stream.str();
}

} // namespace lynq
