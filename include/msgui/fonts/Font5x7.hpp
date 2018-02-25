#pragma once

#include "msgui/Font.hpp"

namespace msgui
{
namespace fonts
{

constexpr int width                       = 5;
constexpr int height                      = 7;
constexpr int numberOfCharacters          = 96;
constexpr int firstAsciiCharacterPosition = 32;

using Char5x7     = msgui::BitMap<5, 7>;
using Font5x7Type = msgui::Font<
    width, height, numberOfCharacters, firstAsciiCharacterPosition>;

extern const Font5x7Type Font5x7;

} // namespace fonts
} // namespace msgui