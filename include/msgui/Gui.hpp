#pragma once

#include <optional>

#include "msgui/graphicDriver.hpp"

namespace msgui
{

class Gui
{
public:
    static Gui& get()
    {
        static Gui gui;
        return gui;
    }

    void setDriver(GraphicDriver driver)
    {
        driver_ = driver;
    }

    GraphicDriver& getDriver()
    {
        return *driver_;
    }

private:
    Gui()
    {
    }

    std::optional<GraphicDriver> driver_;
};

} // namespace msgui