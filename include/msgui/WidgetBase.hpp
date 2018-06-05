#pragma once

#include <eul/event_loop.hpp>

#include "msgui/IWidget.hpp"
#include "msgui/Position.hpp"
#include "msgui/GraphicDriver.hpp"


namespace msgui
{

template<typename Events, GraphicDriver GraphicDriverType>
class WidgetBase : public IWidget
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
    
    virtual void move(Position position)
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