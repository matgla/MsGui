#pragma once

#include "msgui/details/SizeCalculator.hpp"

#include "msgui/Position.hpp"

namespace msgui
{

template <int x_size, int y_size>
class BitwiseChunk
{
private:
    using DataType = uint8_t;
    constexpr static int bitsize_of_uint8_t = 8 * sizeof(uint8_t);
public:
    using SelfType = BitwiseChunk<x_size, y_size>;

    using byte = char;
    constexpr BitwiseChunk() : chunk_data_{}
    {

    }

    constexpr BitwiseChunk(std::initializer_list<std::initializer_list<uint8_t>>&& data) : chunk_data_{}
    {
        int y = 0;
        for (auto& row : data)
        {
            int x = 0;
            for (auto& bit : row)
            {
                if (bit)
                {
                    set_pixel(Position{x, y});
                }
                ++x;
            }
            ++y;
        }
    }

    constexpr bool set_pixel(Position position)
    {
        if (position.x < 0 || position.y < 0 || position.x >= x_size || position.y >= y_size)
        {
            return false;
        }

        int pixel_offset = (position.y * x_size + position.x) % bitsize_of_uint8_t;
        chunk_data_ |= (1 << pixel_offset);
        return true;
    }

    constexpr bool clear_pixel(const Position& position)
    {
        if (position.x < 0 || position.y < 0 || position.x >= x_size || position.y >= y_size)
        {
            return false;
        }

        int pixel_offset = (position.y * x_size + position.x) % bitsize_of_uint8_t;
        chunk_data_ &= ~(1 << pixel_offset);

        return true;
    }

    constexpr static int height()
    {
        return y_size;
    }

    constexpr static int width()
    {
        return x_size;
    }

    constexpr byte get_pixel(const Position& position) const
    {
        if (position.x < 0 || position.y < 0 || position.x >= x_size || position.y >= y_size)
        {
            return 0;
        }
        std::size_t pixel_position = (position.y * x_size + position.x) / bitsize_of_uint8_t;
        std::size_t pixel_offset = (position.y * x_size + position.x) % bitsize_of_uint8_t;
        return (chunk_data_ >> pixel_offset) & 0x1;
    }

    constexpr void offset_in_x(int offset_length)
    {
        if (offset_length < 0)
        {
            for (int y = 0; y < y_size; ++y)
            {
                for (int x = 0; x < x_size; ++x)
                {
                    int target_x = x - offset_length;
                    if (target_x >= 0 && target_x < x_size)
                    {
                        if (get_pixel(Position{target_x, y}))
                        {
                            set_pixel(Position{x, y});
                            continue;
                        }
                    }
                    clear_pixel(Position{x, y});
                }
            }
        }
        else
        {
            for (int y = y_size; y >= 0; --y)
            {
                for (int x = x_size; x >= 0; --x)
                {
                    int target_x = x - offset_length;
                    if (target_x >= 0 && target_x < x_size)
                    {
                        if (get_pixel(Position{target_x, y}))
                        {
                            set_pixel(Position{x, y});
                            continue;
                        }
                    }
                    clear_pixel(Position{x, y});
                }
            }
        }
    }

    constexpr void offset_in_y(int offset_length)
    {
        if (offset_length < 0)
        {
            for (int y = 0; y < y_size; ++y)
            {
                for (int x = 0; x < x_size; ++x)
                {
                    int target_y = y - offset_length;
                    if (target_y >= 0 && target_y < y_size)
                    {
                        if (get_pixel(Position{x, target_y}))
                        {
                            set_pixel(Position{x, y});
                            continue;
                        }
                    }
                    clear_pixel(Position{x, y});
                }
            }
        }
        else
        {
            for (int y = y_size; y >= 0; --y)
            {
                for (int x = x_size; x >= 0; --x)
                {
                    int target_y = y - offset_length;
                    if (target_y >= 0 && target_y < y_size)
                    {
                        if (get_pixel(Position{x, target_y}))
                        {
                            set_pixel(Position{x, y});
                            continue;
                        }
                    }
                    clear_pixel(Position{x, y});
                }
            }
        }
    }

    SelfType& operator |= (const SelfType& other)
    {
        for (int y = 0; y < y_size; ++y)
        {
            for (int x = 0; x < x_size; ++x)
            {
                bool pixel = other.get_pixel(Position{x, y});
                if (pixel)
                {
                    set_pixel(Position{x, y});
                    continue;
                }
            }
        }
        return *this;
    }

    bool operator==(const SelfType& other) const
    {
        return chunk_data_ == other.chunk_data_;
    }

    uint8_t get_byte() const
    {
        return chunk_data_;
    }

private:
    DataType chunk_data_;
};

} // namespace msgui
