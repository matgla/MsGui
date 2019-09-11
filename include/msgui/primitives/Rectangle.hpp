#pragma once

#include "msgui/Area.hpp"
#include "msgui/Color.hpp"
#include "msgui/GraphicDriver.hpp"
#include "msgui/primitives/IShape.hpp"
#include "msgui/primitives/Line.hpp"

namespace msgui
{
namespace primitives
{

template <typename GraphicDriverType>
class Rectangle : public IShape
{
public:
    Rectangle(GraphicDriverType& driver, Area area = {}, bool fullfiled = true)
        : driver_(driver), area_(area), fullfiled_(fullfiled)
    {
    }

    void area(const Area& area)
    {
        area_ = area;
    }

    void draw(const msgui::Color& color) override
    {
        if (fullfiled_)
        {
            for (int x = area_.start.x; x < area_.end.x; ++x)
            {
                for (int y = area_.start.y; y < area_.end.y; ++y)
                {
                    driver_.setPixel(x, y);
                }
            }
        }
        else
        {
            Line top(driver_, {area_.start.x, area_.start.y}, {area_.end.x, area_.start.y});
            Line left(driver_, {area_.start.x, area_.start.y}, {area_.start.x, area_.end.y});
            Line bottom(driver_, {area_.start.x, area_.end.y}, {area_.end.x, area_.end.y});
            Line right(driver_, {area_.end.x, area_.start.y}, {area_.end.x, area_.end.y});

            top.draw(color);
            left.draw(color);
            bottom.draw(color);
            right.draw(color);
        }
    }

    void fullfiled(bool fullfiled)
    {
        fullfiled_ = fullfiled;
    }

private:
    GraphicDriverType& driver_;
    Area area_;
    bool fullfiled_;
}; // namespace primitives

} // namespace primitives
} // namespace msgui