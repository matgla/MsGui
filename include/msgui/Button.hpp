#pragma once

#include "msgui/WidgetBase.hpp"

namespace msgui
{

class Press {};

template <std::size_t CallbackSize>
class Button : public WidgetBase<eul::events<CallbackSize, Press>>
{
    using CallbackType = typename eul::event_loop<eul::events<CallbackSize, Press>>::template callback_type<Press>;
public:
    Button(const Vector2d& position) : WidgetBase<eul::events<CallbackSize, Press>>(position)
    {}

    void onClick(const eul::function<void(), CallbackSize>& callback)
    {
        callback_ = callback;
        this->template registerHandler<Press>([this](const Press&) { callback_(); });
    }

    void press()
    {
        this->process(Press{});
    }

    void draw() const override
    {
        
    }
    
    eul::function<void(), CallbackSize> callback_; 
    
};

} // namespace msgui
