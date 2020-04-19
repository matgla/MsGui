#pragma once

#include <tuple>
#include <utility>

#include "StaticVector.hpp"
#include <eul/function.hpp>
#include <eul/mpl/tuples/for_each.hpp>
#include "msgui/WidgetBase.hpp"
#include "primitives/Rectangle.hpp"

namespace msgui
{

template <typename GraphicDriverType, typename... Widgets>
class Window;

template <typename GraphicDriverType>
class WindowConfig
{
    using WindowConfigType = WindowConfig<GraphicDriverType>;

public:
    using Height = int;
    using Width  = int;
    using Title  = std::string_view;

    WindowConfig(GraphicDriverType& driver)
        : driver_(driver)
    {
    }

    /**
     * Test documentation
     */
    WindowConfigType& position(const Position& position)
    {
        position_ = position;
        return *this;
    }

    WindowConfigType& height(Height height)
    {
        height_ = height;
        return *this;
    }

    WindowConfigType& width(Width width)
    {
        width_ = width;
        return *this;
    }

    WindowConfigType& title(const Title& title)
    {
        title_ = title;
        return *this;
    }

    WindowConfigType& driver(GraphicDriverType& driver)
    {
        driver_ = &driver;
        return *this;
    }

    template <typename... Widgets>
    auto make(Widgets&&... widgets)
    {
        return Window<GraphicDriverType, Widgets...>(*this, widgets...);
    }

    constexpr Position position() const
    {
        return position_;
    }

    constexpr Height height() const
    {
        return height_;
    }

    constexpr Width width() const
    {
        return width_;
    }

    constexpr Title title() const
    {
        return title_;
    }

    constexpr GraphicDriverType& driver() const
    {
        return driver_;
    }

private:
    Position position_;
    Height height_;
    Width width_;
    Title title_;
    GraphicDriverType& driver_;
};

template <typename GraphicDriverType, typename... Widgets>
class Window : public WidgetBase<eul::events<16>, GraphicDriverType>
{
public:
    Window(const WindowConfig<GraphicDriverType>& config, Widgets&&... widgets)
        : WidgetBase<eul::events<16>, GraphicDriverType>(config.position(), config.driver()),
          driver_(config.driver()),
          childs_(std::forward<Widgets>(widgets)...),
          fullscreen_(false),
          height_(config.height()),
          width_(config.width())

    {
    }

    void draw() const
    {
        eul::mpl::tuples::for_each(childs_, [](const auto& child)
        {
            child.draw();
        });
        driver_.sync();
    }

    void fullscreen(bool fullscreen)
    {
        fullscreen_ = fullscreen;
    }

private:
    GraphicDriverType& driver_;
    std::tuple<Widgets...> childs_;
    bool fullscreen_;
    int height_;
    int width_;
};

} // namespace msgui
