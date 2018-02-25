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
        : fullscreen_(false), pos_(pos), height_(height), width_(width)
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
            Area area{{pos_.x, pos_.y}, {pos_.x + width_, pos_.y + height_}};
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
    Vector2d pos_;
    int height_;
    int width_;
};


} // namespace msgui