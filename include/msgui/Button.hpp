#pragma once

#include "msgui/GraphicDriver.hpp"
#include "msgui/WidgetBase.hpp"

#include <eul/utils/unused.hpp>

namespace msgui
{

class Press
{
};

template <std::size_t CallbackSize>
class Button : public WidgetBase<eul::events<CallbackSize, Press>>
{
    using CallbackType = typename eul::event_loop<eul::events<CallbackSize, Press>>::template callback_type<Press>;

public:
    Button(const Position& position)
        : WidgetBase<eul::events<CallbackSize, Press>>(position)
    {
    }

    void onClick(const eul::function<void(), CallbackSize>& callback)
    {
        callback_ = callback;
        this->template registerHandler<Press>([this](const Press&) { callback_(); });
    }

    void press()
    {
        this->process(Press{});
    }

    eul::function<void(), CallbackSize> callback_;
};

} // namespace msgui
