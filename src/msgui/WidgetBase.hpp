#pragma once

#include "msgui/IWidget.hpp"

namespace msgui
{

class WidgetBase : public IWidget
{
public:
    WidgetBase();

    virtual void show() final;
    virtual void hide() final;
    virtual void move(Vector2d pos);

protected:
    bool visible_;
};
} // namespace msgui