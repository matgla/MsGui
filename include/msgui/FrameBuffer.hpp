#pragma once

#include <array>
#include <cstdint>

namespace msgui
{

template <typename DisplayDriver, uint32_t screen_width, uint32_t screen_height>
class FrameBuffer
{
public:
    using BufferType = std::array<uint8_t, (screen_width * screen_height) / 8>;
    FrameBuffer(DisplayDriver& display) : display_(display) {}

    constexpr uint32_t height() const
    {
        return screen_height;
    }

    constexpr uint32_t width() const
    {
        return screen_width;
    }

    constexpr void setPixel(uint16_t x, uint16_t y)
    {
        constexpr uint16_t bits_in_byte = 8;
        const auto y_pos = (y / bits_in_byte) * 128;
        buffer_[y_pos + x] |= (0x01 << (y % y_pos));
    }

    constexpr void draw()
    {
        display_.display(buffer_);
    }
private:
    DisplayDriver& display_;
    BufferType buffer_;
};

} // namespace msgui
