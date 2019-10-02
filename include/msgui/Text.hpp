#pragma once

#include <string_view>

#include "msgui/GraphicDriver.hpp"
#include "msgui/Position.hpp"
#include "msgui/WidgetBase.hpp"
#include "msgui/Image.hpp"
#include "msgui/BitMap.hpp"

// #include <board.hpp>

namespace msgui
{

template <std::size_t CallbackSize, typename FontType, typename GraphicDriverType, template<typename, typename> typename ChunkPolicy, typename ChunkParameters>
class Text : public WidgetBase<eul::events<16>, GraphicDriverType>
{
public:
    Text(GraphicDriverType& driver, const char* text, Position position, const FontType& font, const Color& color = colors::black())
        : WidgetBase<eul::events<16>, GraphicDriverType>(position, driver),
          driver_(driver),
          text_(text),
          font_(font),
          color_(color)
    {
    }

    void drawChar(Position pos, char c) const
    {
        const auto& letterBitMap = font_.get(c);
        for (int x = 0; x < letterBitMap.width(); ++x)
        {
            const uint8_t byte = letterBitMap.getByte(x);
            driver_.write(byte);
        }
        driver_.write(0x00);
    }

    constexpr typename ChunkParameters::ChunkType getChunk(int x, int y) const
    {
        // using Serial = board::interfaces::SERIAL;

        // const int line_size = driver_.width() - this->position_.x;
        // const int text_size_x = (font_.width() + 1) * text_.length();
        // const int number_of_lines = text_size_x / line_size + 1;
        // const int text_size_y = (font_.height() + 1) * number_of_lines;
        // Serial::write("X_pos: ");
        const int x_pos = x - this->position_.x;
        // char data[20];
        // itoa(x_pos, data, 10);
        // Serial::write(data);

        if (x_pos < 0)
        {
            // Serial::write("\n");
            return 0;
        }

        const int y_pos = y - this->position_.y;
        // itoa(y_pos, data, 10);

        // Serial::write(", Y_pos: ");
        // Serial::write(data);
        if (y_pos < 0)
        {
            // Serial::write("\n");
            return 0;
        }

        int letter_index = x_pos / (font_.width() + 1);

        if (static_cast<std::size_t>(letter_index) >= text_.size())
        {
            // Serial::write("\n");

            return 0;
        }
        // itoa(letter_index, data, 10);

        // Serial::write(", index: ");
        // Serial::write(data);
        const auto& bitmap = font_.get(text_[letter_index]);
        // TODO: Fix multiline

        const auto letter_position_x = letter_index * (font_.width() + 1);
        // itoa(letter_position_x, data, 10);

        // Serial::write(", Letter_position: ");
        // Serial::write(data);
        Image<GraphicDriverType, typename std::decay<decltype(bitmap)>::type> image(Position{letter_position_x, this->position_.y}, driver_, bitmap);
        auto byte =  image.getChunk(x_pos, y_pos);
        // itoa(byte, data, 16);

        // Serial::write(", byte: 0x");
        // Serial::write(data);
        // Serial::write("\n");
        return byte;
    }

    void print(std::string_view text) const
    {
        static_cast<void>(text);
        // for (const auto& letter : text)
        // {
            // drawChar(pos, letter);
            // pos.x += font_.width() + 1;
        // }
    }

    int widthToEnd() const
    {
        return driver_.width() - this->position_.x;
    }

    virtual void draw() const override
    {
        if (static_cast<int>(text_.size()) * (font_.width() + 1) <= widthToEnd())
        {
            print(text_);
        }
        else
        {
            print(text_.substr(0, widthToEnd() / font_.width()));
        }
    }

    void setText(std::string_view text)
    {
        text_ = text;
    }

    void setColor(const msgui::Color& color)
    {
        color_ = color;
    }

protected:
    GraphicDriverType& driver_;
    std::string_view text_;
    const FontType& font_;
    msgui::Color color_;
};

} // namespace msgui
