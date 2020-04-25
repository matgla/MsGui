#pragma once

#include <utility>
#include <string_view>

#include "msgui/Button.hpp"
#include "msgui/Text.hpp"
#include "msgui/Window.hpp"
#include "msgui/BitMap.hpp"
#include "msgui/Image.hpp"
#include "msgui/AnimatedSprite.hpp"

namespace msgui
{

template <typename GraphicDriverType>
class Factory
{
public:
    constexpr Factory(GraphicDriverType& driver) : driver_(driver)
    {
    }

    template <std::size_t CallbackSize = 0>
    constexpr auto make_button(const Position& position = {0, 0})
    {
        return Button<CallbackSize>(position, driver_);
    }

    constexpr WindowConfig<GraphicDriverType> configure_window()
    {
        return WindowConfig<GraphicDriverType>(driver_);
    }

    template <typename FontType, std::size_t CallbackSize = 0>
    constexpr auto make_text(const std::string_view& text, const FontType& font, const Position& position = {0, 0}, const Color& color = colors::black())
    {
        return Text<CallbackSize, FontType>(text.data(), position, font, color);
    }

    template <int Width, int Height, typename... Data>
    constexpr auto make_bitmap(Data&&... data) const
    {
        return BitMap<Width, Height>(std::forward<Data>(data)...);
    }

    template <typename BitMapType>
    constexpr auto make_image(Position pos, const BitMapType& bitmap) const
    {
        return Image<BitMapType>(pos, bitmap);
    }

    template <typename BitMapType>
    constexpr auto make_animated_sprite(Position pos, const BitMapType& bitmap, int frame_offset, int time) const
    {
        return AnimatedSprite<BitMapType>(pos, bitmap, frame_offset, time);
    }

    template <typename FontType>
    constexpr auto make_font()
    {
        return FontType::createFont();
    }

    GraphicDriverType& driver_;
};

namespace factory
{

template <int Width, int Height, typename... Data>
constexpr auto make_bitmap(Data&&... data)
{
    return BitMap<Width, Height>(std::forward<Data>(data)...);
}

} // namespace factory

} // namespace msgui
