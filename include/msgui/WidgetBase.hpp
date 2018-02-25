#pragma once

#include "msgui/IWidget.hpp"
#include "msgui/Vector2d.hpp"

namespace msgui
{

class WidgetBase : public IWidget
{
public:
    WidgetBase(const Vector2d& position);

    virtual void show() final;
    virtual void hide() final;
    virtual void move(Vector2d pos);

protected:
    bool visible_;
    Vector2d position_;
};
} // namespace msgui