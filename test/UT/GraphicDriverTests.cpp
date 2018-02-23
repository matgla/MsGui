#include "catch.hpp"

#include "src/GraphicDriver.hpp"
#include "src/Vector2d.hpp"

namespace msgui
{

TEST_CASE("Graphic driver should", "[GraphicDriver]")
{

    Vector2d position{0, 0};
    bool enabled    = false;
    int height      = 100;
    int width       = 100;
    int drawCounter = 0;

    GraphicDriver driver(
        [&position, &enabled](int x, int y, bool enable) {
            position.x = x;
            position.y = y;
            enabled    = enable;
        },
        [&width] {
            return width;
        },
        [&height] {
            return height;
        },
        [&drawCounter] {
            ++drawCounter;
        });

    SECTION("Return width")
    {
        width = 10;
        REQUIRE(driver.width() == width);
        width = 15;
        REQUIRE(driver.width() == width);
    }

    SECTION("Return height")
    {
        height = 111;
        REQUIRE(driver.height() == height);

        height = 92134;
        REQUIRE(driver.height() == height);
    }

    SECTION("Set pixels")
    {
        driver.setPixel(1, 10, true);
        REQUIRE(position.x == 1);
        REQUIRE(position.y == 10);
        REQUIRE(enabled == true);

        driver.setPixel(16, 2, false);
        REQUIRE(position.x == 16);
        REQUIRE(position.y == 2);
        REQUIRE(enabled == false);
    }

    SECTION("Do nothing for negative")
    {
        driver.setPixel(1, 10, true);
        REQUIRE(position.x == 1);
        REQUIRE(position.y == 10);
        REQUIRE(enabled == true);

        driver.setPixel(-10, -56, false);
        REQUIRE(position.x == 1);
        REQUIRE(position.y == 10);
        REQUIRE(enabled == true);
    }

    SECTION("Draw")
    {
        driver.draw();
        REQUIRE(drawCounter == 1);

        driver.draw();
        REQUIRE(drawCounter == 2);
    }

    SECTION("Not draw outside frame")
    {
        width  = 10;
        height = 15;
        driver.setPixel(1, 10, true);
        REQUIRE(position.x == 1);
        REQUIRE(position.y == 10);
        REQUIRE(enabled == true);

        driver.setPixel(width + 1, height + 1, false);
        REQUIRE(position.x == 1);
        REQUIRE(position.y == 10);
        REQUIRE(enabled == true);
    }
}

} // msgui