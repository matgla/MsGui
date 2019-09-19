#include "catch.hpp"

#include "msgui/Factory.hpp"

#include "msgui/policies/chunk/SSD1308ChunkPolicy.hpp"
#include "msgui/policies/data/FlashMemoryPolicy.hpp"

#include "UT/stubs/ChunkPolicyForTest.hpp"
#include "UT/stubs/DriverForTest.hpp"

namespace msgui
{

TEST_CASE("Button should", "[Button]")
{
    stubs::DriverForTest driver;
    using FactoryType = Factory<decltype(driver), policies::data::FlashMemoryPolicy<uint8_t>, policies::chunk::ChunkPolicy, policies::chunk::SSD1308ChunkPolicyParameters>;
    FactoryType factory(driver);

    SECTION("perform action")
    {
        auto button  = factory.make_button<32>();
        bool pressed = false;
        button.onClick([&pressed]() { pressed = true; });
        button.press();
        REQUIRE(pressed == false);
        button.active();
        button.press();
        REQUIRE(pressed == true);
    }
}

} // namespace msgui
