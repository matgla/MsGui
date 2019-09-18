#include "catch.hpp"

#include "msgui/Factory.hpp"
#include <iostream>

#include <eul/utils/unused.hpp>

#include "msgui/policies/chunk/SSD1308ChunkPolicy.hpp"
#include "msgui/policies/data/FlashMemoryPolicy.hpp"

#include "UT/stubs/ChunkPolicyForTest.hpp"
#include "UT/stubs/DriverForTest.hpp"

namespace msgui
{

TEST_CASE("Window should", "[Window]")
{
    stubs::DriverForTest driver;
    using FactoryType = Factory<stubs::DriverForTest, policies::data::FlashMemoryPolicy<uint8_t>, policies::chunk::ChunkPolicy, policies::chunk::SSD1308ChunkPolicyParameters>;
    FactoryType factory(driver);

    SECTION("Construct window")
    {
        auto button = factory.make_button();
        auto window = factory.configure_window().make(button);
        UNUSED1(window);
    }
}

} // namespace msgui
