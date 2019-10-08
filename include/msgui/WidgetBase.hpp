#pragma once

#include <eul/event_loop.hpp>

#include "msgui/Position.hpp"


namespace msgui
{

template<typename Events, typename GraphicDriverType>
class WidgetBase
{
private:
    using EventLoop = eul::event_loop<Events>;

    template<typename Event>
    using CallbackType = typename eul::event_loop<Events>::template callback_type<Event>;


public:

    WidgetBase(const Position& position, GraphicDriverType& driver)
        : visible_(true), active_(false), position_(position), driver_(driver)
    {
    }

    void show()
    {
        visible_ = true;
    }

    void hide()
    {
        visible_ = false;
    }

    void active()
    {
        active_ = true;
    }

    void inactive()
    {
        active_ = false;
    }

    void move(Position position)
    {
        position_ = position;
    }

    template <typename Event>
    void process(const Event& event)
    {
        if (active_)
        {
            eventLoop_.dispatch(event);
        }
    }

    template <typename Event>
    void registerHandler(const CallbackType<Event>& handler)
    {
        eventLoop_.template register_event<Event>(handler);
    }

protected:
    bool visible_;
    bool active_;
    Position position_;
    EventLoop eventLoop_;
    GraphicDriverType& driver_;
};
} // namespace msgui