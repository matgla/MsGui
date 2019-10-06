#include <iostream>

#include "msgui/Factory.hpp"
#include "msgui/fonts/Font5x7.hpp"

#include "msgui/policies/chunk/SSD1308ChunkPolicy.hpp"
#include "msgui/policies/data/DefaultMemoryPolicy.hpp"

#include "simulator/SSD1306Simulator.hpp"

int main()
{
    using Simulator              = simulator::SSD1306Simulator;
    Simulator simulator;
    using FactoryType = msgui::Factory<
        Simulator,
        msgui::policies::data::DefaultMemoryPolicy<uint8_t>,
        msgui::policies::chunk::ChunkPolicy,
        msgui::policies::chunk::SSD1308ChunkPolicyParameters
    >;

    FactoryType factory(simulator);

    std::cout << "Generating window..." << std::endl;
    const auto button = factory.make_button<32>();
    constexpr auto font = factory.make_font<msgui::fonts::Font5x7>();
    const auto text   = factory.make_text("Hello World!", font, {10, 0});
    const auto text2   = factory.make_text("Is Working", font, {10, 16});
    const auto window = factory.configure_window()
                            .width(Simulator::screen_width)
                            .height(Simulator::screen_height)
                            .make(button, text, text2);
    window.draw();
    simulator.dump("window_with_button.bmp");
}