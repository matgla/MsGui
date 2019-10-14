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

        if (x_pos <= -1 * BitMapType::Chunk::width || x_pos > bitmap_.width())
        {
            return {};
        }

        if (y_pos <= -1 * BitMapType::Chunk::height || y_pos > bitmap_.height())
        {
            return {};
        }

        int offset = y_pos;
        if (y_pos < 0) y_pos = 0;

        typename BitMapType::ChunkType chunk = bitmap_.getChunk(x_pos, y_pos);
        chunk.offset_in_x(offset);
        return chunk;
    }

private:
    const BitMapType& bitmap_;
};

} // namespace msgui
