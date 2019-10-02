#pragma once

#include "msgui/BitMapHelpers.hpp"

#include "msgui/policies/chunk/SSD1308ChunkPolicy.hpp"

namespace msgui
{

template <int Width, int Height, typename MemoryPolicy, template<typename, typename> typename ChunkPolicy, typename ChunkParameters>
class BitMap
{
public:
    using DataType = std::array<uint8_t, GetSize<uint8_t, Width, Height>::value>;
    using ChunkPolicyType = ChunkPolicy<msgui::policies::chunk::ChunkPolicyConfig<MemoryPolicy, Width, Height>, ChunkParameters>;
    using ChunkType = typename ChunkParameters::ChunkType;
    template <typename... Data>
    constexpr BitMap(Data&&... data)
        : data_(ChunkPolicyType::make_bitmap(std::forward<Data>(data)...))
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

    constexpr uint8_t getByte(const int x) const
    {
        return ChunkPolicyType::getChunk(data_, 0, x);
    }

    constexpr typename ChunkParameters::ChunkType getChunk(const int x, const int y) const
    {
        return ChunkPolicyType::getChunk(data_, y, x);
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
