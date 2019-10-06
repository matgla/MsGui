#pragma once

#include <utility>

#include <msgui/BitMap.hpp>
#include <msgui/WidgetBase.hpp>
#include <msgui/Position.hpp>

#include <iostream>

namespace msgui
{

template <typename GraphicDriverType, typename BitMapType>
class Image
    : public WidgetBase<eul::events<16>, GraphicDriverType>
{
public:
    constexpr Image(Position position, GraphicDriverType& driver, const BitMapType& bitmap)
        : WidgetBase<eul::events<16>, GraphicDriverType>(position, driver)
        , bitmap_(bitmap)
    {

    }

    constexpr typename BitMapType::ChunkType getChunk(const int x, const int y) const
    {
        const int x_pos = x - this->position_.x;
        int y_pos = y - this->position_.y;

        if (x_pos < 0)
        {
            return 0;
        }

        if (y_pos <= -8)
        {
            return 0;
        }

        int offset = y_pos < 0 ? 0 - y_pos : 0;
        if (y_pos < 0) y_pos = 0;

        typename BitMapType::ChunkType chunk = bitmap_.getChunk(x_pos, y_pos);
        return chunk << offset;
    }

    void draw() const override
    {

    }

private:
    const BitMapType& bitmap_;
};

} // namespace msgui
