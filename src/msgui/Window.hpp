#pragma once
#include "msgui/StaticVector.hpp"
#include "msgui/WidgetBase.hpp"
#include "msgui/primitives/Rectancle.hpp"

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
        // primitives::Rectangle frame(Area{{0, 0}, {18, 30}});
        // // frame.draw();
        // if (fullscreen_)
        // {
        //     Area area{{0, 0}, {gui::Gui::get().getDriver().width() - 1, gui::Gui::get().getDriver().height() - 1}};
        //     // Area area{0}
        //     frame.area(area);
        // }
        // else
        // {
        //     Area area{{pos_.x, pos_.y}, {pos_.x + width_, pos_.y + height_}};
        //     frame.area(area);
        // }
        // frame.fullfiled(false);
        // frame.draw();

        // for (auto* child : childs_)
        // {
        //     if (child)
        //     {
        //         child->draw();
        //     }
        // }
        gui::Gui::get().getDriver().setPixel(83, 47, true);
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
    containers::StaticVector<IWidget*, N> childs_;
    bool fullscreen_;
    Vector2d pos_;
    int height_;
    int width_;
};


} // namespace msgui