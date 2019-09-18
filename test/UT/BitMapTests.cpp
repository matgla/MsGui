
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

TEST_CASE("BitMap should", "[BitMap]")
{
    stubs::DriverForTest driver;
    using FactoryType = Factory<stubs::DriverForTest, policies::data::FlashMemoryPolicy<uint8_t>, policies::chunk::ChunkPolicy, policies::chunk::SSD1308ChunkPolicyParameters>;
    FactoryType factory(driver);

    SECTION("make_bitmap")
    {
        const std::array<uint8_t, GetSize<uint8_t, 5, 5>::value> bitmap = make_bitmap<5, 5>(
            0, 1, 0, 1, 0,
            0, 1, 0, 1, 0,
            0, 0, 0, 0, 0,
            1, 0, 0, 0, 1,
            0, 1, 1, 1, 0);

        /*  01010
            01010
            00000
            10001
            01110
            =
            01010010 0x52
            10000001 0x81
            00010111 0x17
            0        0x00 */


        const std::array<uint8_t, 4> expected{0x52, 0x81, 0x17, 0x00};
        REQUIRE(expected == bitmap);
    }

    SECTION("BitMap should get correct chunks for small bitmap")
    {
        const auto bitmap = factory.make_bitmap<3, 2>(
            1, 0, 1,
            0, 1, 0
        );

        REQUIRE(bitmap.getChunk(0, 0) == 0b10000000);
        REQUIRE(bitmap.getChunk(1, 0) == 0b01000000);
        REQUIRE(bitmap.getChunk(2, 0) == 0b10000000);

        REQUIRE(bitmap.getChunk(0, 1) == 0b00000000);
        REQUIRE(bitmap.getChunk(1, 1) == 0b10000000);
        REQUIRE(bitmap.getChunk(2, 1) == 0b00000000);

        REQUIRE(bitmap.getChunk(0, 2) == 0b00000000);
        REQUIRE(bitmap.getChunk(1, 2) == 0b00000000);
        REQUIRE(bitmap.getChunk(2, 2) == 0b00000000);
    }

    SECTION("BitMap should get correct chunks for high bitmap")
    {
        const auto bitmap = factory.make_bitmap<2, 19>(
            1, 1,
            0, 1,
            1, 1,
            0, 0,
            0, 0,
            1, 1,
            0, 1,
            0, 1, //
            1, 0,
            1, 0,
            0, 1,
            0, 1,
            1, 1,
            1, 1,
            1, 0, //
            0, 1,
            0, 1,
            1, 0,
            0, 1,
            1, 0
        );

        REQUIRE(bitmap.getChunk(0, 0)  == 0b10100100);
        REQUIRE(bitmap.getChunk(1, 0)  == 0b11100111);
        REQUIRE(bitmap.getChunk(0, 1)  == 0b01001001);
        REQUIRE(bitmap.getChunk(1, 1)  == 0b11001110);
        REQUIRE(bitmap.getChunk(0, 2)  == 0b10010011);
        REQUIRE(bitmap.getChunk(1, 2)  == 0b10011100);
        REQUIRE(bitmap.getChunk(0, 3)  == 0b00100110);
        REQUIRE(bitmap.getChunk(1, 3)  == 0b00111001);
        REQUIRE(bitmap.getChunk(0, 4)  == 0b01001100);
        REQUIRE(bitmap.getChunk(1, 4)  == 0b01110011);
        REQUIRE(bitmap.getChunk(0, 5)  == 0b10011001);
        REQUIRE(bitmap.getChunk(1, 5)  == 0b11100111);
        REQUIRE(bitmap.getChunk(0, 6)  == 0b00110011);
        REQUIRE(bitmap.getChunk(1, 6)  == 0b11001111);
        REQUIRE(bitmap.getChunk(0, 7)  == 0b01100111);
        REQUIRE(bitmap.getChunk(1, 7)  == 0b10011110);
        REQUIRE(bitmap.getChunk(0, 8)  == 0b11001110);
        REQUIRE(bitmap.getChunk(1, 8)  == 0b00111101);
        REQUIRE(bitmap.getChunk(0, 9)  == 0b10011100);
        REQUIRE(bitmap.getChunk(1, 9)  == 0b01111011);
        REQUIRE(bitmap.getChunk(0, 10) == 0b00111001);
        REQUIRE(bitmap.getChunk(1, 10) == 0b11110110);
        REQUIRE(bitmap.getChunk(0, 11) == 0b01110010);
        REQUIRE(bitmap.getChunk(1, 11) == 0b11101101);
        REQUIRE(bitmap.getChunk(0, 12) == 0b11100101);
        REQUIRE(bitmap.getChunk(1, 12) == 0b11011010);
        REQUIRE(bitmap.getChunk(0, 13) == 0b11001010);
        REQUIRE(bitmap.getChunk(1, 13) == 0b10110100);
        REQUIRE(bitmap.getChunk(0, 14) == 0b10010100);
        REQUIRE(bitmap.getChunk(1, 14) == 0b01101000);
        REQUIRE(bitmap.getChunk(0, 15) == 0b00101000);
        REQUIRE(bitmap.getChunk(1, 15) == 0b11010000);
        REQUIRE(bitmap.getChunk(0, 16) == 0b01010000);
        REQUIRE(bitmap.getChunk(1, 16) == 0b10100000);
        REQUIRE(bitmap.getChunk(0, 17) == 0b10100000);
        REQUIRE(bitmap.getChunk(1, 17) == 0b01000000);
        REQUIRE(bitmap.getChunk(0, 18) == 0b01000000);
        REQUIRE(bitmap.getChunk(1, 18) == 0b10000000);
        REQUIRE(bitmap.getChunk(0, 19) == 0b10000000);
        REQUIRE(bitmap.getChunk(1, 19) == 0b00000000);
        REQUIRE(bitmap.getChunk(0, 20) == 0b00000000);
        REQUIRE(bitmap.getChunk(1, 20) == 0b00000000);
        REQUIRE(bitmap.getChunk(0, 21) == 0b00000000);
        REQUIRE(bitmap.getChunk(1, 21) == 0b00000000);
    }

    SECTION("BitMap should get correct chunks for wide bitmap")
    {
        const auto bitmap = factory.make_bitmap<19, 2>(
            1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1,
            0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1
        //  0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18
        );

        REQUIRE(bitmap.getChunk(0, 0)  == 0b10000000);
        REQUIRE(bitmap.getChunk(1, 0)  == 0b11000000);
        REQUIRE(bitmap.getChunk(2, 0)  == 0b00000000);
        REQUIRE(bitmap.getChunk(3, 0)  == 0b11000000);
        REQUIRE(bitmap.getChunk(7, 0)  == 0b01000000);
        REQUIRE(bitmap.getChunk(7, 1)  == 0b10000000);
        REQUIRE(bitmap.getChunk(10, 0) == 0b10000000);
        REQUIRE(bitmap.getChunk(11, 0) == 0b11000000);
        REQUIRE(bitmap.getChunk(17, 0) == 0b01000000);
        REQUIRE(bitmap.getChunk(18, 0) == 0b11000000);
    }
}

} // namespace msgui
