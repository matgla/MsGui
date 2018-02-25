#pragma once

#include <bitset>
#include <cstdint>

namespace msgui
{

template <int width, int height, typename... Data>
const std::array<uint8_t, (height * width) / sizeof(uint8_t)> make_bitmap(Data... data)
{
    std::array<uint8_t, (height * width) / sizeof(uint8_t)> bitmap;
    make_pixel(bitmap.data(), bitmap);
    return bitmap;
}

void make_pixel(uint8_t*)
{
}

template <typename... Data>
void make_pixel(uint8_t* byte, bool d0, bool d1, bool d2, bool d3, bool d4, bool d5, bool d6, Data... nextData)
{
    *byte = (d0 << 7) | (d1 << 6) | (d2 << 5) | (d3 << 4) | (d4 << 3) | (d5 << 2) | (d6 << 1) | d7;
    make_pixel(byte + 1, nextData...);
}


template <int width, int height>
class BitMap
{
public:
    using DataType = std::array<uint8_t, (height * width) / sizeof(uint8_t)>;
    BitMap(const DataType data)
        : data_(std::move(data))
    {
    }

    constexpr int width()
    {
        return width;
    }

    constexpr int height()
    {
        return height;
    }

private:
    const DataType data_;
};

template <typename T>
class Font
{
public:
    Font(const int height, const int width, const T* data)
        : height_(height), width_(width), data_(data)
    {
        static_assert(height < sizeof(T), "")
    }

private:
    const int height_;
    const int width_;
    const T* data_;
};

} // namespace msgui
