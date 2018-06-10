#include <iostream>

#include "msgui/Factory.hpp"
#include "msgui/fonts/Font5x7.hpp"

#include "simulator/Simulator.hpp"

int main()
{
    constexpr int display_width  = 320;
    constexpr int display_height = 240;
    using Simulator              = simulator::Simulator<display_width, display_height>;
    Simulator simulator;
    using factory = msgui::Factory<Simulator>;
    factory::setDriver(simulator);

    std::cout << "Generating window..." << std::endl;
    const auto button = factory::make_button();
    const auto text   = factory::make_text("Hello World!", msgui::fonts::Font5x7, {10, 0});
    const auto window = factory::configure_window()
                            .width(display_width)
                            .height(display_height)
                            .make(button, text);
    window.draw();
    simulator.dump("window_with_button.bmp");
}