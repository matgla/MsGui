#include <utility>
#include <string_view>


#include "msgui/Button.hpp"
#include "msgui/Text.hpp"
#include "msgui/Window.hpp"
#include "msgui/BitMap.hpp"
#include "msgui/Image.hpp"

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
        return Button<CallbackSize, GraphicDriverType>(position, driver_);
    }

    constexpr WindowConfig<GraphicDriverType> configure_window()
    {
        return WindowConfig<GraphicDriverType>(driver_);
    }

    template <typename FontType, std::size_t CallbackSize = 0>
    constexpr auto make_text(const std::string_view& text, const FontType& font, const Position& position = {0, 0}, const Color& color = colors::black())
    {
        return Text<CallbackSize, FontType, GraphicDriverType>(driver_, text.data(), position, font, color);
    }

    template <int Width, int Height, typename... Data>
    constexpr auto make_bitmap(Data&&... data) const
    {
        return BitMap<Width, Height>(std::forward<Data>(data)...);
    }

    template <typename BitMapType>
    constexpr auto make_image(Position pos, const BitMapType& bitmap) const
    {
        return Image<GraphicDriverType, BitMapType>(pos, driver_, bitmap);
    }

    template <typename FontType>
    constexpr auto make_font()
    {
        return FontType::createFont();
    }

    GraphicDriverType& driver_;
};

} // namespace msgui
