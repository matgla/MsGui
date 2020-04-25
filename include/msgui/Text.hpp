#pragma once

#include <string_view>

#include "msgui/GraphicDriver.hpp"
#include "msgui/Position.hpp"
#include "msgui/WidgetBase.hpp"
#include "msgui/Image.hpp"
#include "msgui/BitMap.hpp"

namespace msgui
{

template <std::size_t CallbackSize, typename FontType>
class Text : public WidgetBase<eul::events<16>>
{
public:
    Text(const char* text, Position position, const FontType& font, const Color& color = colors::black())
        : WidgetBase<eul::events<16>>(position),
          text_(text),
          font_(font),
          color_(color)
    {
    }

    template <typename DriverType>
    void drawChar(Position pos, char c, DriverType& driver) const
    {
        const auto& letterBitMap = font_.get(c);
        for (int y = 0; y < letterBitMap.height(); ++y)
        {
            for (int x = 0; x < letterBitMap.width(); ++x)
            {
                bool enable = letterBitMap.getPixel(x, y);
                if (enable)
                {
                    driver.set_pixel(x + pos.x, y + pos.y);
                }
            }
        }
    }

    template <typename DriverType>
    void print(std::string_view text, DriverType& driver) const
    {
        if (this->visible_)
        {
            Position pos = this->position_;
            for (const auto& letter : text)
            {
                drawChar(pos, letter, driver);
                pos.x += font_.width() + 1;
            }
        }
    }

    template <typename DriverType>
    int widthToEnd(DriverType& driver) const
    {
        return driver.width() - this->position_.x;
    }

    template <typename DriverType>
    void draw(DriverType& driver) const
    {
        if (static_cast<int>(text_.size()) * (font_.width() + 1) <= widthToEnd(driver))
        {
            print(text_, driver);
        }
        else
        {
            print(text_.substr(0, widthToEnd(driver) / font_.width()), driver);
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
    std::string_view text_;
    const FontType& font_;
    msgui::Color color_;
};

} // namespace msgui
