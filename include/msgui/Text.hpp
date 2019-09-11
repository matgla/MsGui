#pragma once

#include <string_view>

#include "msgui/GraphicDriver.hpp"
#include "msgui/Position.hpp"
#include "msgui/WidgetBase.hpp"

namespace msgui
{

template <std::size_t CallbackSize, typename FontType, typename GraphicDriverType>
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
        for (int y = 0; y < letterBitMap.height(); ++y)
        {
            for (int x = 0; x < letterBitMap.height(); ++x)
            {
                bool enable = letterBitMap.getPixel(x, y);
                if (enable)
                {
                    driver_.setPixel(static_cast<uint32_t>(x + pos.x), static_cast<uint32_t>(y + pos.y));
                }
            }
        }
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
