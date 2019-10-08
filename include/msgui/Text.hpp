#pragma once

#include <string_view>

#include "msgui/GraphicDriver.hpp"
#include "msgui/Position.hpp"
#include "msgui/WidgetBase.hpp"
#include "msgui/Image.hpp"
#include "msgui/BitMap.hpp"

#include <iostream>

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
        const int x_pos = x - this->position_.x;

        if (x_pos < 0)
        {
            return 0;
        }

        const int y_pos = y - this->position_.y;

        if (y_pos <= -8)
        {
            return 0;
        }

        int letter_index = x_pos / (font_.width() + 1);

        if (static_cast<std::size_t>(letter_index) >= text_.size())
        {
            return 0;
        }
        const auto& bitmap = font_.get(text_[letter_index]);

        const auto letter_position_x = letter_index * (font_.width() + 1);
        Image<GraphicDriverType, typename std::decay<decltype(bitmap)>::type> image(Position{letter_position_x, this->position_.y}, driver_, bitmap);
        return image.getChunk(x_pos, y);
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

    void draw() const
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
