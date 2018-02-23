#include "msgui/WidgetBase.hpp"

namespace msgui
{

WidgetBase::WidgetBase()
    : visible_(true)
{
}

void WidgetBase::show()
{
    visible_ = true;
}

void WidgetBase::hide()
{
    visible_ = false;
}

void WidgetBase::move(Vector2d pos)
{
}

} // namespace msgui