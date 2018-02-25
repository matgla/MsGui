
#include "catch.hpp"

#include "msgui/BitMap.hpp"
#include "msgui/BitMapHelpers.hpp"

#include <iomanip>
#include <iostream>

namespace msgui
{

TEST_CASE("BitMap should", "[BitMap]")
{
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

    SECTION("BitMap example")
    {
    }
}

} // namespace msgui
