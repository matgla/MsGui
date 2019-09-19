#pragma once

#include <vector>

#include "msgui/Color.hpp"
#include "msgui/Position.hpp"

#include <eul/utils/unused.hpp>

namespace msgui
{
namespace stubs
{

template <uint32_t Width = 0, uint32_t Height = 0>
class DriverForTest
{
public:
    void setPixel(const Position& position, const Color& color)
    {
        (void)position;
        (void)color;
    }

    uint32_t width()
    {
        return Width;
    }

    uint32_t height()
    {
        return Height;
    }

    void draw()
    {
    }

    template <typename ChunkType>
    void write(const ChunkType data)
    {
        buffer_.push_back(data);
    }

    std::vector<uint8_t> buffer_;
};

} // namespace stubs
} // namespace msgui
