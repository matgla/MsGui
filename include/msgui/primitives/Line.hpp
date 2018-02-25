#pragma once

#include <algorithm>

#include "msgui/gui.hpp"
#include "msgui/primitives/IShape.hpp"
#include "msgui/vector2d.hpp"

namespace msgui
{
namespace primitives
{

template <typename T>
int sgn(T val)
{
    return (T(0) < val) - (val < T(0));
}

class Line : public IShape
{
public:
    Line(Vector2d start, Vector2d end)
        : start_(start), end_(end)
    {
    }

    void draw() override
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
                Gui::get().getDriver().setPixel(start_.x, y, true);
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
                Gui::get().getDriver().setPixel(x, y, true);
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
    Vector2d start_;
    Vector2d end_;
};

} // namespace primitives
} // namespace gui