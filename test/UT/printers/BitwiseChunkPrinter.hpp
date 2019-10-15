#pragma once

#include <ostream>

#include "msgui/BitwiseChunk.hpp"

namespace msgui
{

template <int x_size, int y_size>
std::ostream& operator<<(std::ostream& os, const BitwiseChunk<x_size, y_size>& chunk)
{

    for (int y = 0; y < y_size; ++y)
    {
        os << "[ ";
        for (int x = 0; x < x_size; ++x)
        {
            os << static_cast<int>(chunk.get_pixel(msgui::Position{x, y}));
            if (x < x_size - 1)
            {
                os << " ";
            }
            else
            {
                os << " ]";
            }
        }
        os << std::endl;
    }
    return os;
}

} // namespace msgui
