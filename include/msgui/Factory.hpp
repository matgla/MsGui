#include <string_view>

#include "msgui/Button.hpp"
#include "msgui/GraphicDriver.hpp"
#include "msgui/Text.hpp"
#include "msgui/Window.hpp"

namespace msgui
{


template <GraphicDriver GraphicDriverType>
class Factory
{
public:
    constexpr static void setDriver(GraphicDriverType& driver)
    {
        Factory<GraphicDriverType>::driver_ = &driver;
    }

    template <std::size_t CallbackSize = 0>
    constexpr static auto make_button(const Position& position = {0, 0})
    {
        return Button<CallbackSize, GraphicDriverType>(position, *driver_);
    }

    constexpr static WindowConfig<GraphicDriverType> configure_window()
    {
        return WindowConfig<GraphicDriverType>(*driver_);
    }

    template <typename FontType, std::size_t CallbackSize = 0>
    constexpr static auto make_text(const std::string_view& text, const FontType& font, const Position& position = {0, 0}, const Color& color = colors::black())
    {
        return Text<CallbackSize, FontType, GraphicDriverType>(*driver_, text.data(), position, font, color);
    }

    inline static GraphicDriverType* driver_;
};

} // namespace msgui
