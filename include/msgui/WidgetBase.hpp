#pragma once

#include <eul/event_loop.hpp>

#include "msgui/IWidget.hpp"
#include "msgui/Vector2d.hpp"

namespace msgui
{

template<std::size_t CallbackSize = 0, typename... Events>
class WidgetBase : public IWidget
{
public:
    WidgetBase(const Vector2d& position) : visible_(true), position_(position)
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
    
    virtual void move(Vector2d position)
    {
        position_ = position;
    }

protected:
    bool visible_;
    Vector2d position_;
    eul::event_loop<CallbackSize, Events...> event_loop;
};
} // namespace msgui