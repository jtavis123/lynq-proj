#pragma once

#include <compare>
#include <string>

namespace lynq {

struct Version {
    int major{0};
    int minor{0};
    int patch{0};
    std::string label;

    [[nodiscard]] std::string toString() const {
        std::string result = std::to_string(major) + "." +
                             std::to_string(minor) + "." +
                             std::to_string(patch);
        if (!label.empty()) result += "-" + label;
        return result;
    }

    auto operator<=>(const Version&) const = default;
};

inline constexpr Version kSdkVersion{0, 1, 1, "alpha"};

} // namespace lynq
