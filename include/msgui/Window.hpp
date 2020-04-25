#pragma once

#include <tuple>
#include <utility>

#include <chrono>
#include <sys/time.h>
#include <time.h>

#include "StaticVector.hpp"
#include <eul/function.hpp>
#include <eul/mpl/tuples/for_each.hpp>
#include "msgui/WidgetBase.hpp"
#include "primitives/Rectangle.hpp"
#include "msgui/AnimatedSprite.hpp"

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
class Window : public WidgetBase<eul::events<16>>
{
public:
    Window(const WindowConfig<GraphicDriverType>& config, Widgets&&... widgets)
        : WidgetBase<eul::events<16>>(config.position()),
          driver_(config.driver()),
          childs_(std::forward<Widgets>(widgets)...),
          fullscreen_(false),
          height_(config.height()),
          width_(config.width()),
          framerate_(60),
          previous_frame_timestamp_(0)

    {
    }

    void display()
    {
        std::chrono::microseconds current{get_microseconds()};
        std::chrono::microseconds delta = current - previous_frame_timestamp_;
        std::chrono::microseconds frame_time = std::chrono::microseconds(1000000/framerate_);
        if (delta < frame_time)
        {
            delta = frame_time - delta;
            struct timespec ts;
            ts.tv_sec = delta.count() / 1000000;
            ts.tv_nsec = (delta.count() % 1000000) * 1000;
            nanosleep(&ts, &ts);

        }
        previous_frame_timestamp_ = std::chrono::microseconds(get_microseconds());
        eul::mpl::tuples::for_each(childs_, [this](const auto& child)
        {
            child.draw(driver_);
        });
        driver_.sync();
    }

    void fullscreen(bool fullscreen)
    {
        fullscreen_ = fullscreen;
    }

    void set_framerate(int framerate)
    {
        framerate_ = framerate;
    }

    int get_framerate() const
    {
        return framerate_;
    }

private:
    GraphicDriverType& driver_;
    std::tuple<Widgets...> childs_;
    bool fullscreen_;
    int height_;
    int width_;
    int framerate_;
    std::chrono::microseconds previous_frame_timestamp_;
};

template <typename GraphicDriverType>
class Window<GraphicDriverType> : public WidgetBase<eul::events<16>>
{
public:
    Window(const WindowConfig<GraphicDriverType>& config)
        : WidgetBase<eul::events<16>>(config.position()),
          driver_(config.driver()),
          fullscreen_(false),
          height_(config.height()),
          width_(config.width()),
          framerate_(60),
          previous_frame_timestamp_(0)

    {
    }

    void display()
    {
        std::chrono::microseconds current{get_microseconds()};
        std::chrono::microseconds delta = current - previous_frame_timestamp_;
        std::chrono::microseconds frame_time = std::chrono::microseconds(1000000/framerate_);
        if (delta < frame_time)
        {
            delta = frame_time - delta;
            struct timespec ts;
            ts.tv_sec = delta.count() / 1000000;
            ts.tv_nsec = (delta.count() % 1000000) * 1000;
            nanosleep(&ts, &ts);

        }
        previous_frame_timestamp_ = std::chrono::microseconds(get_microseconds());
        driver_.sync();
    }

    void fullscreen(bool fullscreen)
    {
        fullscreen_ = fullscreen;
    }

    void set_framerate(int framerate)
    {
        framerate_ = framerate;
    }

    int get_framerate() const
    {
        return framerate_;
    }

private:
    GraphicDriverType& driver_;
    bool fullscreen_;
    int height_;
    int width_;
    int framerate_;
    std::chrono::microseconds previous_frame_timestamp_;
};

} // namespace msgui
