#pragma once

#include <cstdint>

#include <eul/utils/unused.hpp>

#include "msgui/details/SizeCalculator.hpp"

namespace msgui
{
namespace policies
{
namespace chunk
{

constexpr static unsigned char lookup[16] = {
0x0, 0x8, 0x4, 0xc, 0x2, 0xa, 0x6, 0xe,
0x1, 0x9, 0x5, 0xd, 0x3, 0xb, 0x7, 0xf, };

constexpr uint8_t reverse(uint8_t n) {
   // Reverse the top and bottom nibble then swap them.
   return (lookup[n&0b1111] << 4) | lookup[n>>4];
}

constexpr uint8_t get_mask(int line_height)
{
    uint8_t mask = 0;
    for (int i = 0; i < line_height; ++i)
    {
        mask = (mask << 1 | 1);
    }
    return mask;
}

template <typename DataPolicyType, int image_width_, int image_height_>
struct ChunkPolicyConfig
{
    using DataPolicy = DataPolicyType;
    constexpr static uint8_t image_width = image_width_;
    constexpr static uint8_t image_height = image_height_;
};

struct SSD1308ChunkPolicyParameters
{
    using ChunkType = uint8_t;
    constexpr static int height = 8;
    constexpr static int width = 1;
};

template <typename Config, typename Parameters>
class ChunkPolicy
{
private:
    constexpr static uint8_t line_height_in_pixels = Config::image_height > 8 ? 8 : Config::image_height;
    constexpr static uint8_t line_width_in_pixels = 1;
    constexpr static uint8_t mask = get_mask(line_height_in_pixels);

public:
    template <typename DataType>
    constexpr static typename Parameters::ChunkType getChunk(const DataType& data, const int line, const int column)
    {
        int x = column;
        if (x >= Config::image_width)
        {
            return 0;
        }

        uint8_t byte = 0;

        uint8_t index = 0;
        uint8_t bit_offset = 0;
        for (std::size_t i = 0; i < line_height_in_pixels; ++i)
        {
            const int bit_position = i * Config::image_width + x + Config::image_width * line;
            index = (bit_position) / Parameters::height;
            bit_offset = Parameters::height - 1 - (bit_position % Parameters::height);
            uint8_t bit = 0;
            if (index < data.size())
            {
                bit = (Config::DataPolicy::read(data, index) >> (bit_offset)) & 0x01;
            }
            else
            {
                bit = 0;
            }

            byte |= (bit << (Parameters::height - 1 - i ));//- (line % Parameters::height)));
        }

        return reverse(byte);
    }

    template <size_t N, typename... Args>
    constexpr static decltype(auto) get(Args&&... args) noexcept
    {
        return std::get<N * line_height_in_pixels>(std::forward_as_tuple(std::forward<Args>(args)...));
    }

    template <typename... Data>
    constexpr static void make_pixel(uint8_t* byte, std::size_t index, bool d0, Data... nextData)
    {
        if (index % 8 == 0)
        {
            *byte = 0;
        }
        *byte |= (d0 << (7 - index));

        if (index == 7)
        {
            make_pixel(++byte, 0, nextData...);
            return;
        }
        make_pixel(byte, index + 1, nextData...);
        return;
    }


    constexpr static void make_pixel(uint8_t* byte, std::size_t index)
    {
        UNUSED2(byte, index);
        return;
    }

    template <typename... Data>
    constexpr static const std::array<uint8_t, details::GetSize<uint8_t, Config::image_width, Config::image_height>::value> make_bitmap(Data&&... data)
    {
        std::array<uint8_t, details::GetSize<uint8_t, Config::image_width, Config::image_height>::value> bitmap{};
        make_pixel(bitmap.data(), 0, data...);

        return bitmap;
    }

};

} // namespace chunk
} // namespace policies
} // namespace msgui
