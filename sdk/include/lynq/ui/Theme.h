#pragma once

#include <cstdint>

namespace lynq::ui {

struct Color {
    std::uint8_t red{0};
    std::uint8_t green{0};
    std::uint8_t blue{0};
};

struct Theme {
    Color background;
    Color surface;
    Color elevatedSurface;
    Color primaryText;
    Color secondaryText;
    Color accent;
    Color success;
    Color warning;
    Color danger;
    std::uint16_t cornerRadius{18};
    std::uint16_t spacingUnit{8};
};

inline constexpr Theme kLynqDarkTheme{
    {15, 17, 21},
    {26, 29, 35},
    {37, 41, 49},
    {246, 247, 249},
    {164, 171, 184},
    {41, 126, 192},
    {52, 199, 89},
    {255, 159, 10},
    {255, 69, 58},
    18,
    8
};

} // namespace lynq::ui
