#pragma once

#include <cstdint>

namespace msgui
{
namespace stubs
{

class ChunkPolicyForTests
{
public:
    constexpr static uint32_t height = 1;
    constexpr static uint32_t width = 1;
    using ChunkType = uint8_t;
};

} // namespace stubs
} // namespace msgui
