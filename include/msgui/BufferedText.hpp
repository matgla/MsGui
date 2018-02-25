#pragma once

#include <string_view>

#include "gui/text.hpp"
#include "hal/utils/assert.hpp"

namespace gui
{

template <std::size_t N>
class BufferedText : public gui::Text
{
public:
    BufferedText(const char (&str)[N])
        : gui::Text(""), text_(str)
    {
        Text::setText(text_);
    }

    BufferedText(const char* str)
        : gui::Text(""), text_(str)
    {
        Text::setText(text_);
    }

    BufferedText()
        : gui::Text(""), text_("\0")
    {
        Text::setText(text_);
    }

    void setText(std::string_view text)
    {
        static_assert(text.size() < N, "size of new string must be less than N");
        text_ = text.data();
    }

    char* data()
    {
        return text_;
    }

private:
    char text_[N];
};

} // namespace gui
