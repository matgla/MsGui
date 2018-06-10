#pragma once

#include <cstdint>

namespace msgui
{

struct Color
{
    int r;
    int g;
    int b;
};

namespace colors
{
constexpr Color black()
{
    return Color{0, 0, 0};
}
} // namespace colors

} // namespace msgui