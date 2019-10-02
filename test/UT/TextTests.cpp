
#include <catch.hpp>

#include "msgui/Text.hpp"

#include "msgui/policies/chunk/SSD1308ChunkPolicy.hpp"
#include "msgui/policies/data/DefaultMemoryPolicy.hpp"
#include "msgui/Factory.hpp"
#include "msgui/fonts/Font5x7.hpp"

#include "UT/stubs/DriverForTest.hpp"


namespace msgui
{

TEST_CASE("Text should", "[Text]")
{
    stubs::DriverForTest<80, 30> driver;
    using FactoryType = Factory<decltype(driver), policies::data::DefaultMemoryPolicy<uint8_t>, policies::chunk::ChunkPolicy, policies::chunk::SSD1308ChunkPolicyParameters>;
    FactoryType factory(driver);
    constexpr auto font = factory.make_font<fonts::Font5x7>();

    SECTION("Text should get correct text without offset")
    {
        const auto text = factory.make_text("Hello World", font, Position{0, 0});
        REQUIRE(text.getChunk(0, 0) == 0x7f);
        REQUIRE(text.getChunk(1, 0) == 0x08);

    }
}

} // namespace msgui
