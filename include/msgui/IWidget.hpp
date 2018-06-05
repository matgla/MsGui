#pragma once

#include "msgui/Position.hpp"

namespace msgui
{

class IWidget
{
public:
    virtual ~IWidget() = default;

    virtual void draw() const       = 0;
    virtual void move(Position pos) = 0;
    virtual void show()             = 0;
    virtual void hide()             = 0;
    virtual void active()           = 0;
    virtual void inactive()         = 0;
};

} // namespace msgui