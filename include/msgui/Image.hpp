#pragma once

#include <utility>

#include <msgui/BitMap.hpp>
#include <msgui/WidgetBase.hpp>
#include <msgui/Position.hpp>

namespace msgui
{

template <typename BitMapType>
class Image
    : public WidgetBase<eul::events<1>>
{
public:
    constexpr Image(Position position, const BitMapType& bitmap)
        : WidgetBase<eul::events<1>>(position)
        , bitmap_(bitmap)
    {

    }

    const BitMapType& bitmap() const
    {
        return bitmap_;
    }

    template <typename DriverType>
    void draw(DriverType& driver) const
    {
        Position pos = this->position_;

        for (int y = 0; y < bitmap_.height(); ++y)
        {
            for (int x = 0; x < bitmap_.width(); ++x)
            {
                if (bitmap_.getPixel(x, y))
                {
                    driver.set_pixel(x + pos.x, y + pos.y);
                }
            }
        }
    }

private:
    const BitMapType& bitmap_;
};

} // namespace msgui
