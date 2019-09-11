#pragma once

#include "msgui/BitMapHelpers.hpp"

namespace msgui
{

template <int Width, int Height>
class BitMap
{
public:
    using DataType = std::array<uint8_t, GetSize<uint8_t, Width, Height>::value>;

    template <typename... Data>
    constexpr BitMap(Data&&... data)
        : data_(make_bitmap<Width, Height>(std::forward<Data>(data)...))
    {
    }

    constexpr int width() const
    {
        return Width;
    }

    constexpr int height() const
    {
        return Height;
    }

    constexpr bool getPixel(const int x, const int y) const
    {
        if (x >= width() || y >= height())
        {
            return false;
        }
        const int bytesFromStart = x + y * Width;
        const int index          = bytesFromStart / BITS_IN_BYTE;
        return (data_[index] >> (BITS_IN_BYTE - 1 - (bytesFromStart % BITS_IN_BYTE))) & 0x01;
    }

    void setPixel(const int x, const int y, bool enable)
    {
        const int bytesFromStart = x + y * Width;
        const int index          = bytesFromStart / BITS_IN_BYTE;
        if (enable)
        {
            data_[index] |= (enable << (BITS_IN_BYTE - 1 - (bytesFromStart % BITS_IN_BYTE)));
        }
        else
        {
            data_[index] &= (enable << (BITS_IN_BYTE - 1 - (bytesFromStart % BITS_IN_BYTE)));
        }
    }

    void pixelOn(const int x, const int y)
    {
        setPixel(x, y, true);
    }

    void pixelOff(const int x, const int y)
    {
        setPixel(x, y, false);
    }

    DataType& data()
    {
        return data_;
    }

private:
    const DataType data_;
};

} // namespace msgui
