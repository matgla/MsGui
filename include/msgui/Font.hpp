#pragma once

#include <array>

#include "msgui/BitMap.hpp"

namespace msgui
{

template <int Width, int Height, int NumberOfCharacters, int Offset, typename MemoryPolicy, template<typename, typename> typename ChunkPolicy, typename ChunkParameters>
class Font
{
public:
    using FontData = std::array<BitMap<Width, Height, MemoryPolicy, ChunkPolicy, ChunkParameters>, NumberOfCharacters>;

    template <typename... A>
    constexpr Font(A&&... args)
        : data_{std::forward<A>(args)...}
    {
    }

    const BitMap<Width, Height, MemoryPolicy, ChunkPolicy, ChunkParameters>& get(int c) const
    {
        int position = c - Offset;
        if (position < 0 || position > NumberOfCharacters - 2)
        {
            return data_[0]; // unknown character
        }
        return data_[position];
    }

    constexpr int width() const
    {
        return Width;
    }

    constexpr int height() const
    {
        return Height;
    }

private:
    const FontData data_;
};

} // namespace msgui
