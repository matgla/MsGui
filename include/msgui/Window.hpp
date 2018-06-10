#pragma once

#include <tuple>
#include <utility>

#include "StaticVector.hpp"
#include "eul/function.hpp"
#include "eul/generics/for_each.hpp"
#include "msgui/GraphicDriver.hpp"
#include "msgui/WidgetBase.hpp"
#include "primitives/Rectangle.hpp"

namespace msgui
{

template <GraphicDriver GraphicDriverType, typename... Widgets>
class Window;

template <GraphicDriver GraphicDriverType>
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

template <GraphicDriver GraphicDriverType, typename... Widgets>
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

    virtual void draw() const final
    {
        primitives::Rectangle<GraphicDriverType> frame(driver_, Area{{0, 0}, {18, 30}});
        if (fullscreen_)
        {
            Area area{{0, 0}, {driver_.width() - 1, driver_.height() - 1}};
            frame.area(area);
        }
        else
        {
            Area area{{this->position_.x, this->position_.y}, {this->position_.x + width_ - 1, this->position_.y + height_ - 1}};
            frame.area(area);
        }
        frame.fullfiled(false);
        frame.draw({0, 0, 0});

        eul::generics::for_each(childs_, [](const auto& child) { child.draw(); });
    }

    void attach(IWidget& widget)
    {

        // childs_.push_back(&widget);
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
