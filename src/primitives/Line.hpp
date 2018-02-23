#pragma once

#include "gui.hpp"
#include "primitives/IShape.hpp"
#include "vector2d.hpp"

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

    void draw() const override
    {
        // Bresenham algorithm
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

private:
    Vector2d start_;
    Vector2d end_;
};

} // namespace primitives
} // namespace gui