#include <cassert>
#include <vector>

#include "msgui/Color.hpp"
#include "msgui/Position.hpp"

#include "msgui/policies/chunk/SSD1308ChunkPolicy.hpp"

#include <bitmap/bitmap_image.hpp>

namespace simulator
{

class SSD1306Simulator
{
public:
    constexpr static uint32_t screen_width = 128;
    constexpr static uint32_t screen_height = 64;
    constexpr static uint8_t chunk_height =  msgui::policies::chunk::SSD1308ChunkPolicyParameters::height;
    constexpr static uint8_t chunk_width =  msgui::policies::chunk::SSD1308ChunkPolicyParameters::width;
    constexpr static uint8_t number_of_rows = screen_height / chunk_height;
    constexpr static uint8_t number_of_columns = screen_width / chunk_width;

    using ChunkType = msgui::policies::chunk::SSD1308ChunkPolicyParameters::ChunkType;
    using LineType = std::array<ChunkType, number_of_columns>;
    using BufferType = std::array<LineType, number_of_rows>;

    SSD1306Simulator()
        : cursor_x_(0)
        , cursor_y_(0)
    {
        clear();
    }

    void write(ChunkType chunk)
    {
        buffer_[cursor_y_][cursor_x_] = chunk;
        cursor_x_ += 1;
        if (cursor_x_ >= number_of_columns)
        {
            cursor_x_ = 0;
            cursor_y_ += 1;
        }
    }

    constexpr uint32_t width() const
    {
        return screen_width;
    }

    constexpr uint32_t height() const
    {
        return screen_height;
    }

    void clear()
    {

        for (auto& line : buffer_)
        {
            line = LineType{};
        }
    }

    void dump(std::string_view filename)
    {
        bitmap_image image(screen_width, screen_height);

        for (int x = 0; x < number_of_columns; ++x)
        {
            for (int y = 0; y < number_of_rows; ++y)
            {
                const auto& data = buffer_[y][x];
                for (int bit = 0; bit < chunk_height; ++bit)
                {
                    if ((data >> bit) & 0x1)
                    {
                        image.set_pixel(x, y * chunk_height + bit, 255, 255, 255);
                    }
                }
            }
        }
        image.save_image(filename.data());
    }

private:
    BufferType buffer_;
    int cursor_x_;
    int cursor_y_;
};

} // namespace simulator
