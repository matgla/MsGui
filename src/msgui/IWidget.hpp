#pragma once

#include "msgui/Vector2d.hpp"

namespace msgui
{

class IWidget
{
public:
    virtual ~IWidget() = default;

    virtual void draw() const       = 0;
    virtual void move(Vector2d pos) = 0;
    virtual void show()             = 0;
    virtual void hide()             = 0;
};

} // namespace msgui