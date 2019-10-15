#include "catch.hpp"

#include "msgui/Factory.hpp"
#include <iostream>

#include <eul/utils/unused.hpp>

#include "msgui/policies/chunk/SSD1308ChunkPolicy.hpp"
#include "msgui/policies/data/DefaultMemoryPolicy.hpp"

#include "UT/stubs/ChunkPolicyForTest.hpp"
#include "UT/stubs/DriverForTest.hpp"

namespace msgui
{

TEST_CASE("Window should", "[Window]")
{
    stubs::DriverForTest<64, 32> driver;
    using FactoryType = Factory<decltype(driver), policies::data::DefaultMemoryPolicy<uint8_t>, policies::chunk::ChunkPolicy, policies::chunk::SSD1308ChunkPolicyParameters>;
    FactoryType factory(driver);

    SECTION("Draw via chunks")
    {
        auto bitmap = factory.make_bitmap<10, 3>(
            1, 0, 1, 0, 1, 1, 1, 1, 1, 1,
            0, 0, 0, 1, 0, 0, 0, 0, 0, 1,
            1, 0, 0, 1, 1, 1, 1, 1, 1, 1
        );

        auto image = factory.make_image(Position{2, 3}, bitmap);

        auto bitmap2 = factory.make_bitmap<3, 3>(
            1, 0, 1,
            1, 1, 1,
            1, 1, 1
        );

        auto image2 = factory.make_image(Position{3, 5}, bitmap2);
        auto window = factory.configure_window().make(image, image2);
        window.draw();
        REQUIRE(driver.buffer_[0] == 0x0);
        REQUIRE(driver.buffer_[1] == 0x0);
        // a = 10
        // b = 11
        // c = 12
        // 00010100
        // 00101000
        REQUIRE(driver.buffer_[2] == 0x28);

        // 00000111
        // 11100000
        REQUIRE(driver.buffer_[3] == 0xe0);
    }
}

} // namespace msgui
