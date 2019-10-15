
#include "catch.hpp"

#include "msgui/BitMap.hpp"
#include "msgui/BitMapHelpers.hpp"

#include <iomanip>


#include "msgui/policies/chunk/SSD1308ChunkPolicy.hpp"
#include "msgui/policies/data/DefaultMemoryPolicy.hpp"
#include "msgui/Factory.hpp"

#include "UT/stubs/DriverForTest.hpp"
#include "UT/printers/BitwiseChunkPrinter.hpp"



namespace msgui
{

TEST_CASE("BitMap should", "[BitMap]")
{
    stubs::DriverForTest driver;
    using FactoryType = Factory<decltype(driver), policies::data::DefaultMemoryPolicy<uint8_t>, policies::chunk::ChunkPolicy, policies::chunk::SSD1308ChunkPolicyParameters>;
    FactoryType factory(driver);

    SECTION("make_bitmap")
    {
        const std::array<uint8_t, details::GetSize<uint8_t, 5, 5>::value> bitmap = make_bitmap<5, 5>(
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
        using ChunkType = decltype(bitmap)::ChunkType;
        REQUIRE(bitmap.getChunk(0, 0) == ChunkType{{1},{0},{0},{0},{0},{0},{0},{0}});
        REQUIRE(bitmap.getChunk(1, 0) == ChunkType{{0},{2},{0},{0},{0},{0},{0},{0}});
        REQUIRE(bitmap.getChunk(2, 0) == ChunkType{{1},{0},{0},{0},{0},{0},{0},{0}});

        REQUIRE(bitmap.getChunk(0, 1) == ChunkType{{0},{0},{0},{0},{0},{0},{0},{0}});
        REQUIRE(bitmap.getChunk(1, 1) == ChunkType{{1},{0},{0},{0},{0},{0},{0},{0}});
        REQUIRE(bitmap.getChunk(2, 1) == ChunkType{{0},{0},{0},{0},{0},{0},{0},{0}});

        REQUIRE(bitmap.getChunk(0, 2) == ChunkType{{0},{0},{0},{0},{0},{0},{0},{0}});
        REQUIRE(bitmap.getChunk(1, 2) == ChunkType{{0},{0},{0},{0},{0},{0},{0},{0}});
        REQUIRE(bitmap.getChunk(2, 2) == ChunkType{{0},{0},{0},{0},{0},{0},{0},{0}});
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
        using ChunkType = decltype(bitmap)::ChunkType;
        REQUIRE(bitmap.getChunk(0, 0) == ChunkType{{1},{0},{1},{0},{0},{1},{0},{0}});
        REQUIRE(bitmap.getChunk(1, 0) == ChunkType{{1},{1},{1},{0},{0},{1},{1},{1}});
        REQUIRE(bitmap.getChunk(0, 1) == ChunkType{{0},{1},{0},{0},{1},{0},{0},{1}});
        REQUIRE(bitmap.getChunk(1, 1) == ChunkType{{1},{1},{0},{0},{1},{1},{1},{0}});
        REQUIRE(bitmap.getChunk(0, 2) == ChunkType{{1},{0},{0},{1},{0},{0},{1},{1}});
        REQUIRE(bitmap.getChunk(1, 2) == ChunkType{{1},{0},{0},{1},{1},{1},{0},{0}});
        REQUIRE(bitmap.getChunk(0, 3) == ChunkType{{0},{0},{1},{0},{0},{1},{1},{0}});
        REQUIRE(bitmap.getChunk(1, 3) == ChunkType{{0},{0},{1},{1},{1},{0},{0},{1}});
        REQUIRE(bitmap.getChunk(0, 4) == ChunkType{{0},{1},{0},{0},{1},{1},{0},{0}});
        REQUIRE(bitmap.getChunk(1, 4) == ChunkType{{0},{1},{1},{1},{0},{0},{1},{1}});
        REQUIRE(bitmap.getChunk(0, 5) == ChunkType{{1},{0},{0},{1},{1},{0},{0},{1}});
        REQUIRE(bitmap.getChunk(1, 5) == ChunkType{{1},{1},{1},{0},{0},{1},{1},{1}});
        REQUIRE(bitmap.getChunk(0, 6) == ChunkType{{0},{0},{1},{1},{0},{0},{1},{1}});
        REQUIRE(bitmap.getChunk(1, 6) == ChunkType{{1},{1},{0},{0},{1},{1},{1},{1}});
        REQUIRE(bitmap.getChunk(0, 7) == ChunkType{{0},{1},{1},{0},{0},{1},{1},{1}});
        REQUIRE(bitmap.getChunk(1, 7) == ChunkType{{1},{0},{0},{1},{1},{1},{1},{0}});
        REQUIRE(bitmap.getChunk(0, 8) == ChunkType{{1},{1},{0},{0},{1},{1},{1},{0}});
        REQUIRE(bitmap.getChunk(1, 8) == ChunkType{{0},{0},{1},{1},{1},{1},{0},{1}});
        REQUIRE(bitmap.getChunk(0, 9) == ChunkType{{1},{0},{0},{1},{1},{1},{0},{0}});
        REQUIRE(bitmap.getChunk(1, 9) == ChunkType{{0},{1},{1},{1},{1},{0},{1},{1}});
        REQUIRE(bitmap.getChunk(0, 10) == ChunkType{{0},{0},{1},{1},{1},{0},{0},{1}});
        REQUIRE(bitmap.getChunk(1, 10) == ChunkType{{1},{1},{1},{1},{0},{1},{1},{0}});
        REQUIRE(bitmap.getChunk(0, 11) == ChunkType{{0},{1},{1},{1},{0},{0},{1},{0}});
        REQUIRE(bitmap.getChunk(1, 11) == ChunkType{{1},{1},{1},{0},{1},{1},{0},{1}});
        REQUIRE(bitmap.getChunk(0, 12) == ChunkType{{1},{1},{1},{0},{0},{1},{0},{1}});
        REQUIRE(bitmap.getChunk(1, 12) == ChunkType{{1},{1},{0},{1},{1},{0},{1},{0}});
        REQUIRE(bitmap.getChunk(0, 13) == ChunkType{{1},{1},{0},{0},{1},{0},{1},{0}});
        REQUIRE(bitmap.getChunk(1, 13) == ChunkType{{1},{0},{1},{1},{0},{1},{0},{0}});
        REQUIRE(bitmap.getChunk(0, 14) == ChunkType{{1},{0},{0},{1},{0},{1},{0},{0}});
        REQUIRE(bitmap.getChunk(1, 14) == ChunkType{{0},{1},{1},{0},{1},{0},{0},{0}});
        REQUIRE(bitmap.getChunk(0, 15) == ChunkType{{0},{0},{1},{0},{1},{0},{0},{0}});
        REQUIRE(bitmap.getChunk(1, 15) == ChunkType{{1},{1},{0},{1},{0},{0},{0},{0}});
        REQUIRE(bitmap.getChunk(0, 16) == ChunkType{{0},{1},{0},{1},{0},{0},{0},{0}});
        REQUIRE(bitmap.getChunk(1, 16) == ChunkType{{1},{0},{1},{0},{0},{0},{0},{0}});
        REQUIRE(bitmap.getChunk(0, 17) == ChunkType{{1},{0},{1},{0},{0},{0},{0},{0}});
        REQUIRE(bitmap.getChunk(1, 17) == ChunkType{{0},{1},{0},{0},{0},{0},{0},{0}});
        REQUIRE(bitmap.getChunk(0, 18) == ChunkType{{0},{1},{0},{0},{0},{0},{0},{0}});
        REQUIRE(bitmap.getChunk(1, 18) == ChunkType{{1},{0},{0},{0},{0},{0},{0},{0}});
        REQUIRE(bitmap.getChunk(0, 19) == ChunkType{{1},{0},{0},{0},{0},{0},{0},{0}});
        REQUIRE(bitmap.getChunk(1, 19) == ChunkType{{0},{0},{0},{0},{0},{0},{0},{0}});
        REQUIRE(bitmap.getChunk(0, 20) == ChunkType{{0},{0},{0},{0},{0},{0},{0},{0}});
        REQUIRE(bitmap.getChunk(1, 20) == ChunkType{{0},{0},{0},{0},{0},{0},{0},{0}});
        REQUIRE(bitmap.getChunk(0, 21) == ChunkType{{0},{0},{0},{0},{0},{0},{0},{0}});
        REQUIRE(bitmap.getChunk(1, 21) == ChunkType{{0},{0},{0},{0},{0},{0},{0},{0}});
    }

    SECTION("BitMap should get correct chunks for wide bitmap")
    {
        const auto bitmap = factory.make_bitmap<19, 2>(
            1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1,
            0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1
        //  0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18
        );
        using ChunkType = decltype(bitmap)::ChunkType;

        REQUIRE(bitmap.getChunk(0, 0)  == ChunkType{{1},{0},{0},{0},{0},{0},{0},{0}});
        REQUIRE(bitmap.getChunk(1, 0)  == ChunkType{{1},{1},{0},{0},{0},{0},{0},{0}});
        REQUIRE(bitmap.getChunk(2, 0)  == ChunkType{{0},{0},{0},{0},{0},{0},{0},{0}});
        REQUIRE(bitmap.getChunk(3, 0)  == ChunkType{{1},{1},{0},{0},{0},{0},{0},{0}});
        REQUIRE(bitmap.getChunk(7, 0)  == ChunkType{{0},{1},{0},{0},{0},{0},{0},{0}});
        REQUIRE(bitmap.getChunk(7, 1)  == ChunkType{{1},{0},{0},{0},{0},{0},{0},{0}});
        REQUIRE(bitmap.getChunk(10, 0) == ChunkType{{1},{0},{0},{0},{0},{0},{0},{0}});
        REQUIRE(bitmap.getChunk(11, 0) == ChunkType{{1},{1},{0},{0},{0},{0},{0},{0}});
        REQUIRE(bitmap.getChunk(17, 0) == ChunkType{{0},{1},{0},{0},{0},{0},{0},{0}});
        REQUIRE(bitmap.getChunk(18, 0) == ChunkType{{1},{1},{0},{0},{0},{0},{0},{0}});
    }
}

} // namespace msgui
