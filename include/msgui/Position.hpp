#pragma once

namespace msgui
{

struct Position
{
    int x;
    int y;

    bool operator==(const Position& other)
    {
        return x == other.x && y == other.y;
    }
};

} // namespace msgui
