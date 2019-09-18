#pragma once

#include <string_view>

#include "msgui/GraphicDriver.hpp"
#include "msgui/Position.hpp"
#include "msgui/WidgetBase.hpp"

namespace msgui
{

template <std::size_t CallbackSize, typename FontType, typename GraphicDriverType, template<typename, typename> typename ChunkPolicy, typename ChunkParameters>
class Text : public WidgetBase<eul::events<16>, GraphicDriverType>
{
public:
    Text(GraphicDriverType& driver, const char* text, Position position, const FontType& font, const Color& color = colors::black())
        : WidgetBase<eul::events<16>, GraphicDriverType>(position, driver),
          position_(position),
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

    ChunkParameters::ChunkType getChunk(int x, int y) const
    {
        int x_start = x + ChunkParameters::width;
        int x_offset = x_start - position_.x;
        if (x <= 0) return 0;
        int y_start = y + ChunkParameters::height;
        int y_offset = y_start - position_.y;
        if (y <= 0) return 0;

        // int x_bitoffset = x_offset % ChunkParameters::width;
        int y_bitoffset = y_offset % ChunkParameters::height;

        // int line = x_offset / ChunkParameters::height;
        // int column = y_offset / ChunkParameters::width;

        // get letter bitmap

        int letter_index = (x_offset / (font_.width() + 1));

        // relokacja może być w dół albo w górę, teraz tego nie ogarniam ...., musze rozpisać algorytm

        typename ChunkParameters::ChunkType chunk = font_.get(text_[letter_index]).getByte(x_offset) << y_bitoffset;
        return chunk;
    }

    void print(std::string_view text) const
    {
        Position pos = position_;
        for (const auto& letter : text)
        {
            drawChar(pos, letter);
            pos.x += font_.width() + 1;
        }
    }

    int widthToEnd() const
    {
        return driver_.width() - position_.x;
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
    Position position_;
    GraphicDriverType& driver_;
    std::string_view text_;
    const FontType& font_;
    msgui::Color color_;
};

} // namespace msgui
