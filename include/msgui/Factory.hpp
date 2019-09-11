#include <string_view>

#include "msgui/Button.hpp"
#include "msgui/Text.hpp"
#include "msgui/Window.hpp"

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

    GraphicDriverType& driver_;
};

} // namespace msgui
