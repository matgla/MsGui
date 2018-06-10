#pragma once

#include <algorithm>

#include "msgui/Vector2d.hpp"
#include "msgui/primitives/IShape.hpp"
#include "msgui/primitives/Line.hpp"

namespace msgui
{
namespace primitives
{

template <typename T>
int sgn(T val)
{
    return (T(0) < val) - (val < T(0));
}

template <GraphicDriver GraphicDriverType>
class Line : public IShape
{
public:
    Line(GraphicDriverType& driver, Vector2d start, Vector2d end)
        : driver_(driver), start_(start), end_(end)
    {
    }

    void draw(const msgui::Color& color) override
    {
        // Bresenham algorithm
        if (start_.x > end_.x)
        {
            std::swap(start_, end_);
        }

        if (start_.x == end_.x)
        {
            if (start_.y > end_.y)
            {
                std::swap(start_, end_);
            }
            for (int y = start_.y; y <= end_.y; ++y)
            {
                driver_.setPixel({start_.x, y}, color);
            }
        }
        else
        {
            int deltaX   = end_.x - start_.x;
            int deltaY   = end_.y - start_.y;
            int deltaErr = 2 * deltaY - deltaX;
            int y        = start_.y;

            for (int x = start_.x; x < end_.x; ++x)
            {
                driver_.setPixel({x, y}, color);
                if (deltaErr > 0)
                {
                    y = y + 1;
                    deltaErr -= 2 * deltaX;
                }
                deltaErr = deltaErr + 2 * deltaY;
            }
        }
    }

private:
    GraphicDriverType& driver_;
    Vector2d start_;
    Vector2d end_;
};

} // namespace primitives
} // namespace msgui