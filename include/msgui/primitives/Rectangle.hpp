#pragma once

#include "msgui/Area.hpp"
#include "msgui/Gui.hpp"
#include "msgui/primitives/IShape.hpp"
#include "msgui/primitives/Line.hpp"

namespace msgui
{
namespace primitives
{

class Rectangle : public IShape
{
public:
    Rectangle(Area area = {}, bool fullfiled = true)
        : area_(area), fullfiled_(fullfiled)
    {
    }

    void area(const Area& area)
    {
        area_ = area;
    }

    void draw() override
    {
        if (fullfiled_)
        {
            for (int x = area_.start.x; x < area_.end.x; ++x)
            {
                for (int y = area_.start.y; y < area_.end.y; ++y)
                {
                    Gui::get().getDriver().setPixel(x, y, true);
                }
            }
        }
        else
        {
            Line top{{area_.start.x, area_.start.y}, {area_.end.x, area_.start.y}};
            Line left{{area_.start.x, area_.start.y}, {area_.start.x, area_.end.y}};
            Line bottom{{area_.start.x, area_.end.y}, {area_.end.x, area_.end.y}};
            Line right{{area_.end.x, area_.start.y}, {area_.end.x, area_.end.y}};

            top.draw();
            left.draw();
            bottom.draw();
            right.draw();
        }
    }

    void fullfiled(bool fullfiled)
    {
        fullfiled_ = fullfiled;
    }

private:
    Area area_;
    bool fullfiled_;
};

} // namespace primitives
} // namespace msgui