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
    constexpr static uint32_t screen_width = Width;
    constexpr static uint32_t screen_height = Height;
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
        uint8_t byte = 0;
        for (int i = 0; i < 8; i++)
        {
            byte |= data.get_pixel(msgui::Position{0, i}) << i;
        }
        buffer_.push_back(byte);
    }

    std::vector<uint8_t> buffer_;
};

} // namespace stubs
} // namespace msgui
