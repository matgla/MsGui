#include <cassert>

#include "msgui/Color.hpp"
#include "msgui/Position.hpp"

#include <bitmap/bitmap_image.hpp>

namespace simulator
{

template <int Width, int Height>
class Simulator
{
public:
    Simulator()
    {
        clear();
    }

    void setPixel(const msgui::Position& position, const msgui::Color& color)
    {
        assert(position.x <= Width);
        assert(position.y <= Height);
        buffer_[position.x][position.y] = color;
    }

    int width()
    {
        return Width;
    }

    int height()
    {
        return Height;
    }

    void draw()
    {
    }

    void clear()
    {
        for (auto& line : buffer_)
        {
            for (auto& color : line)
            {
                color.r = 255;
                color.g = 255;
                color.b = 255;
            }
        }
    }

    void dump(std::string_view filename)
    {
        bitmap_image image(Width, Height);

        for (int x = 0; x < Width; ++x)
        {
            for (int y = 0; y < Height; ++y)
            {
                const auto& color = buffer_[x][y];
                image.set_pixel(x, y, color.r, color.g, color.b);
            }
        }
        image.save_image(filename.data());
    }

private:
    std::array<std::array<msgui::Color, Height>, Width> buffer_;
};

} // namespace simulator
