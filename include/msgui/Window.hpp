#pragma once
#include "StaticVector.hpp"
#include "WidgetBase.hpp"
#include "primitives/Rectangle.hpp"
namespace msgui
{

template <std::size_t N>
class Window : public WidgetBase
{
public:
    Window(Vector2d pos, int height, int width, std::string_view title = "")
        : WidgetBase(pos), fullscreen_(false), height_(height), width_(width)
    {
    }

    virtual void draw() const final
    {
        primitives::Rectangle frame(Area{{0, 0}, {18, 30}});
        if (fullscreen_)
        {
            Area area{{0, 0}, {msgui::Gui::get().getDriver().width() - 1, msgui::Gui::get().getDriver().height() - 1}};
            frame.area(area);
        }
        else
        {
            Area area{{position_.x, position_.y}, {position_.x + width_, position_.y + height_}};
            frame.area(area);
        }
        frame.fullfiled(false);
        frame.draw();

        for (auto* child : childs_)
        {
            if (child)
            {
                child->draw();
            }
        }
    }

    void attach(IWidget& widget)
    {
        childs_.push_back(&widget);
    }

    void fullscreen(bool fullscreen)
    {
        fullscreen_ = fullscreen;
    }

private:
    StaticVector<IWidget*, N> childs_;
    bool fullscreen_;
    int height_;
    int width_;
};


} // namespace msgui