#pragma once

#include "msgui/Position.hpp"

namespace msgui
{
    
template <typename T>
concept bool GraphicDriver = requires(T t) 
{
    { t.setPixel(const Position& position, const Color& color) } -> void;
    { t.width() } -> int;
    { t.height() } -> int;
    { t.draw() } -> void;
};

} // namespace msgui