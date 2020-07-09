#pragma once

#include <eul/event_loop.hpp>

#include "msgui/Position.hpp"

namespace msgui
{

template<typename Events>
class WidgetBase
{
private:
    using EventLoop = eul::event_loop<Events>;

    template<typename Event>
    using CallbackType = typename eul::event_loop<Events>::template callback_type<Event>;


public:

    WidgetBase(const Position& position)
        : visible_(true), active_(false), position_(position)
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

    void set_position(Position position)
    {
        position_ = position;
    }

    Position get_position() const
    {
        return position_;
    }

    void move(Position position)
    {
        position_ = {position_.x + position.x, position_.y + position.y};
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
};
} // namespace msgui
