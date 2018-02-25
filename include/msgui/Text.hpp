#pragma once

#include <string_view>

#include "msgui/Gui.hpp"
#include "msgui/WidgetBase.hpp"

namespace gui
{

class Text : public WidgetBase
{
public:
    Text(const char* text = "")
        : Element(""), text_(text)
    {
    }

    void onDraw() override
    {
        if (text_.size() * (display::Display::get()->getFont().width + 1) <= display::Display::get()->getWidthToEnd())
        {
            display::Display::get()->print(text_.data());
        }
        else
        {
            display::Display::get()->print(text_.substr(0, display::Display::get()->getWidthToEnd() / display::Display::get()->getFont().width).data());
        }
    }

    void setText(std::string_view text)
    {
        text_ = text;
    }

protected:
    std::string_view text_;
};

} // namespace msgui
