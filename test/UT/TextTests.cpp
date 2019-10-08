
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

    SECTION("Text should get correct text with x offset")
    {
        const auto text = factory.make_text("Hello World", font, Position{10, 0});
        REQUIRE(text.getChunk(9, 0) == 0x00);
        REQUIRE(text.getChunk(10, 0) == 0x7f);
        REQUIRE(text.getChunk(11, 0) == 0x08);
    }

    SECTION("Text should get correct text with y offset")
    {
        auto text = factory.make_text("Hello World", font, Position{1, 1});
        REQUIRE(text.getChunk(0, 0) == 0x00);
        // 00111111
        REQUIRE(text.getChunk(1, 0) == 0xfe);
        REQUIRE(text.getChunk(1, 8) == 0x00);

        text.move(Position{1, 2});
        // 00011111
        REQUIRE(text.getChunk(1, 0) == 0xfc);
        REQUIRE(text.getChunk(1, 8) == 0x01);

        text.move(Position{1, 3});
        // 00001111
        REQUIRE(text.getChunk(1, 0) == 0xf8);
        REQUIRE(text.getChunk(1, 8) == 0x03);

        text.move(Position{1, 4});
        // 00000111
        REQUIRE(text.getChunk(1, 0) == 0xf0);
        REQUIRE(text.getChunk(1, 8) == 0x07);

        text.move(Position{1, 5});
        // 00000011
        REQUIRE(text.getChunk(1, 0) == 0xe0);
        REQUIRE(text.getChunk(1, 8) == 0x0f);

        text.move(Position{1, 6});
        // 00000001
        REQUIRE(text.getChunk(1, 0) == 0xc0);
        REQUIRE(text.getChunk(1, 8) == 0x1f);

        text.move(Position{1, 7});
        // 00000000
        REQUIRE(text.getChunk(1, 0) == 0x80);
        REQUIRE(text.getChunk(1, 8) == 0x3f);


        text.move(Position{1, 8});
        // 00000000
        REQUIRE(text.getChunk(1, 0) == 0x00);
        REQUIRE(text.getChunk(1, 8) == 0x7f);

    }
}

} // namespace msgui
