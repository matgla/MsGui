#pragma once

#include <string_view>

#include "msgui/Gui.hpp"
#include "msgui/Vector2d.hpp"
#include "msgui/WidgetBase.hpp"

namespace msgui
{

template <typename FontType>
class Text : public WidgetBase
{
public:
    Text(const char* text, Vector2d position, const FontType& font)
        : WidgetBase(position), text_(text), font_(font)
    {
    }

    void drawChar(Vector2d pos, char c) const
    {
        const auto& letterBitMap = font_.get(c);
        for (int y = 0; y < letterBitMap.height(); ++y)
        {
            for (int x = 0; x < letterBitMap.height(); ++x)
            {
                bool enable = letterBitMap.getPixel(x, y);
                Gui::get().getDriver().setPixel(x + pos.x, y + pos.y, enable);
            }
        }
    }

    void print(std::string_view text) const
    {
        Vector2d pos = position_;
        for (const auto& letter : text)
        {
            drawChar(pos, letter);
            pos.x += font_.width() + 1;
        }
    }

    int widthToEnd() const
    {
        return Gui::get().getDriver().width() - position_.x;
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

protected:
    std::string_view text_;
    const FontType& font_;
};

} // namespace msgui
