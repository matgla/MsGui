#pragma once

#include <utility>

#include <msgui/BitMap.hpp>
#include <msgui/WidgetBase.hpp>
#include <msgui/Position.hpp>

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
        int x_pos = x - this->position_.x;
        int y_pos = y - this->position_.y;
        int x_offset = 0;
        int y_offset = 0;

        if (x_pos < 0)
        {
            x_offset = -1 * x_pos;
            x_pos = 0;
        }

        if (y_pos < 0)
        {
            y_offset = -1 * y_pos;
            y_pos = 0;
        }

        if (x_pos >= bitmap_.width())
        {
            x_offset = x_pos - bitmap_.width();
        }

        if (y_pos >= bitmap_.height())
        {
            y_offset = y_pos - bitmap_.height();
        }

        typename BitMapType::ChunkType chunk = bitmap_.getChunk(x_pos, y_pos);
        chunk.offset_in_y(y_offset);
        chunk.offset_in_x(x_offset);
        return chunk;
    }

private:
    const BitMapType& bitmap_;
};

} // namespace msgui
