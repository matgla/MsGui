#include "catch.hpp"

#include <algorithm>

#include "msgui/BitwiseChunk.hpp"
#include "msgui/Position.hpp"

namespace msgui
{

TEST_CASE("BitwiseChunk should", "[BitwiseChunk]")
{
    SECTION("return correct size")
    {
        using ChunkA = BitwiseChunk<10, 15>;
        using ChunkB = BitwiseChunk<1, 8>;

        REQUIRE(ChunkA::width() == 10);
        REQUIRE(ChunkA::height() == 15);

        REQUIRE(ChunkB::width() == 1);
        REQUIRE(ChunkB::height() == 8);
    }

    SECTION("notify out of bound")
    {
        BitwiseChunk<1, 1> chunk;
        REQUIRE(chunk.set_pixel({0, 0}));
        REQUIRE(chunk.set_pixel({0, 1}) == false);
        REQUIRE(chunk.set_pixel({1, 0}) == false);
        REQUIRE(chunk.get_pixel({0, 0}) == 1);
        REQUIRE(chunk.get_pixel({0, 1}) == -1);
        REQUIRE(chunk.get_pixel({1, 0}) == -1);
    }

    SECTION("set specific pixel")
    {
        BitwiseChunk<5, 5> chunk;

        /**************
         *  | 0 1 2 3 4
         * ------------
         * 0| 1 1 0 1 1
         * 1| 1 0 1 0 1
         * 2| 0 1 1 1 0
         * 3| 1 0 1 0 1
         * 4| 1 1 0 1 1
         ***************/

        std::vector<Position> pixel_positions = {
            // left top corner
            {0, 0},
            {0, 1},
            {1, 0},

            // right top corner
            {3, 0},
            {4, 0},
            {4, 1},

            // left bottom corner
            {0, 3},
            {0, 4},
            {1, 4},

            // right bottom corner
            {3, 4},
            {4, 3},
            {4, 4},

            // center
            {1, 2},
            {2, 2},
            {3, 2},
            {2, 1},
            {2, 3}
        };

        for (const auto& pos : pixel_positions)
        {
            chunk.set_pixel(pos);
        }

        for (std::size_t y = 0; y < chunk.height(); ++y)
        {
            for (std::size_t x = 0; x < chunk.width(); ++x)
            {
                const Position position{static_cast<int>(x), static_cast<int>(y)};
                if (std::find(pixel_positions.begin(), pixel_positions.end(), position) != pixel_positions.end())
                {
                    REQUIRE(chunk.get_pixel(position) == 1);
                    continue;
                }
                REQUIRE(chunk.get_pixel(position) == 0);
            }
        }
    }

    SECTION("perform offset in X axis")
    {
        BitwiseChunk<5, 5> chunk;

        /**************
         *  | 0 1 2 3 4          | 0 1 2 3 4          | 0 1 2 3 4
         * ------------         ------------         ------------
         * 0| 1 1 0 1 1         0| 0 1 1 0 0         0| 0 0 1 1 0
         * 1| 1 0 1 0 1         1| 1 0 1 0 0         1| 0 1 0 1 0
         * 2| 0 1 1 1 0  -> -2  2| 1 1 0 0 0  -> +1  2| 0 1 1 0 0
         * 3| 1 0 1 0 1         3| 1 0 1 0 0         3| 0 1 0 1 0
         * 4| 1 1 0 1 1         4| 0 1 1 0 0         4| 0 0 1 1 0
         ***************/

        const std::vector<Position> pixel_positions_after_first_offset = {
            {1, 0},
            {2, 0},
            {0, 1},
            {2, 1},
            {0, 2},
            {1, 2},
            {0, 3},
            {2, 3},
            {1, 4},
            {2, 4}
        };

        const std::vector<Position> pixel_positions_after_second_offset = {
            {2, 0},
            {3, 0},
            {1, 1},
            {3, 1},
            {1, 2},
            {2, 2},
            {1, 3},
            {3, 3},
            {2, 4},
            {3, 4}
        };

        std::vector<Position> pixel_positions = {
            // left top corner
            {0, 0},
            {0, 1},
            {1, 0},

            // right top corner
            {3, 0},
            {4, 0},
            {4, 1},

            // left bottom corner
            {0, 3},
            {0, 4},
            {1, 4},

            // right bottom corner
            {3, 4},
            {4, 3},
            {4, 4},

            // center
            {1, 2},
            {2, 2},
            {3, 2},
            {2, 1},
            {2, 3}
        };

        for (const auto& pos : pixel_positions)
        {
            chunk.set_pixel(pos);
        }


        chunk.offset_in_x(-2);

        for (std::size_t y = 0; y < chunk.height(); ++y)
        {
            for (std::size_t x = 0; x < chunk.width(); ++x)
            {
                const Position position{static_cast<int>(x), static_cast<int>(y)};
                if (std::find(pixel_positions_after_first_offset.begin(),
                                pixel_positions_after_first_offset.end(), position) != pixel_positions_after_first_offset.end())
                {
                    REQUIRE(chunk.get_pixel(position) == 1);
                    continue;
                }
                REQUIRE(chunk.get_pixel(position) == 0);
            }
        }

        chunk.offset_in_x(1);
        for (std::size_t y = 0; y < chunk.height(); ++y)
        {
            for (std::size_t x = 0; x < chunk.width(); ++x)
            {
                const Position position{static_cast<int>(x), static_cast<int>(y)};
                if (std::find(pixel_positions_after_second_offset.begin(),
                                pixel_positions_after_second_offset.end(), position) != pixel_positions_after_second_offset.end())
                {
                    REQUIRE(chunk.get_pixel(position) == 1);
                    continue;
                }
                REQUIRE(chunk.get_pixel(position) == 0);
            }
        }

        chunk.offset_in_x(0);
        for (std::size_t y = 0; y < chunk.height(); ++y)
        {
            for (std::size_t x = 0; x < chunk.width(); ++x)
            {
                const Position position{static_cast<int>(x), static_cast<int>(y)};
                if (std::find(pixel_positions_after_second_offset.begin(),
                                pixel_positions_after_second_offset.end(), position) != pixel_positions_after_second_offset.end())
                {
                    REQUIRE(chunk.get_pixel(position) == 1);
                    continue;
                }
                REQUIRE(chunk.get_pixel(position) == 0);
            }
        }

    }
}

} // namespace msgui
