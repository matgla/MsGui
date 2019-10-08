#pragma once

#include "msgui/details/SizeCalculator.hpp"

#include "msgui/Position.hpp"

#include <iostream>

namespace msgui
{

template <int x_size, int y_size>
class BitwiseChunk
{
private:
    using DataType = std::array<uint8_t, details::GetSize<uint8_t, x_size, y_size>::value>;
    constexpr static int bitsize_of_uint8_t = 8 * sizeof(uint8_t);
public:
    using byte = char;
    constexpr BitwiseChunk() : chunk_data_{}
    {

    }

    constexpr bool set_pixel(Position position)
    {
        if (position.x < 0 || position.y < 0 || position.x >= x_size || position.y >= y_size)
        {
            return false;
        }

        int pixel_position = (position.y * x_size + position.x) / bitsize_of_uint8_t;
        int pixel_offset = (position.y * x_size + position.x) % bitsize_of_uint8_t;
        chunk_data_[pixel_position] |= (1 << pixel_offset);
        return true;
    }

    constexpr bool clear_pixel(const Position& position)
    {
        return false;
    }

    constexpr static std::size_t height()
    {
        return y_size;
    }

    constexpr static std::size_t width()
    {
        return x_size;
    }

    constexpr byte get_pixel(const Position& position) const
    {
        if (position.x < 0 || position.y < 0 || position.x >= x_size || position.y >= y_size)
        {
            return -1;
        }
        std::size_t pixel_position = (position.y * x_size + position.x) / bitsize_of_uint8_t;
        std::size_t pixel_offset = (position.y * x_size + position.x) % bitsize_of_uint8_t;
        return (chunk_data_[pixel_position] >> pixel_offset) & 0x1;
    }

    constexpr void offset_in_x(int offset_length)
    {

    }
private:
    DataType chunk_data_;
};

} // namespace msgui
