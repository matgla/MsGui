
#include "catch.hpp"

#include "msgui/BitMap.hpp"
#include "msgui/BitMapHelpers.hpp"

#include <iomanip>


#include "msgui/policies/chunk/SSD1308ChunkPolicy.hpp"
#include "msgui/policies/data/FlashMemoryPolicy.hpp"
#include "msgui/Factory.hpp"

#include "UT/stubs/DriverForTest.hpp"


namespace msgui
{

TEST_CASE("Image should", "[Image]")
{
    stubs::DriverForTest driver;
    using FactoryType = Factory<stubs::DriverForTest, policies::data::FlashMemoryPolicy<uint8_t>, policies::chunk::ChunkPolicy, policies::chunk::SSD1308ChunkPolicyParameters>;
    FactoryType factory(driver);

    SECTION("Image should get correct chunks for small image")
    {
        const auto image = factory.make_image<3, 3>(
            Position{10, 10},
            1, 0, 1,
            0, 1, 0,
            1, 0, 1
        );
        REQUIRE(image.getChunk(0, 0)   == 0b00000000);
        REQUIRE(image.getChunk(8, 10)   == 0b00000000);
        REQUIRE(image.getChunk(9, 10)   == 0b00000000);
        REQUIRE(image.getChunk(10, 10) == 0b10100000);
        REQUIRE(image.getChunk(11, 10) == 0b01000000);
        REQUIRE(image.getChunk(11, 9)  == 0b10000000);
        REQUIRE(image.getChunk(11, 8)  == 0b00000000);
    }
}

} // namespace msgui
