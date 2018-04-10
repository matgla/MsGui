#pragma once

#include <eul/event_loop.hpp>

#include "msgui/IWidget.hpp"
#include "msgui/Vector2d.hpp"

namespace msgui
{

template<typename Events>
class WidgetBase : public IWidget
{
    using EventLoop = eul::event_loop<Events>;
    
    template<typename Event>
    using CallbackType = typename eul::event_loop<Events>::template callback_type<Event>;

public:
    WidgetBase(const Vector2d& position) : visible_(true), active_(false), position_(position)
    {
    }

    virtual void show() final
    {
        visible_ = true;
    }
    
    virtual void hide() final
    {
        visible_ = false;    
    }
    
    virtual void active() final 
    {
        active_ = true;
    }
    
    virtual void inactive() final 
    {
        active_ = false;
    }
    
    virtual void move(Vector2d position)
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
    Vector2d position_;
    EventLoop eventLoop_;
};
} // namespace msgui