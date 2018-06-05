
#include "catch.hpp"

#include "msgui/Button.hpp"

namespace msgui
{

TEST_CASE("Button should", "[Button]")
{
    SECTION("perform action")
    {
        Button<sizeof(int*)> button({0, 0});
        bool pressed = false;
        button.onClick([&pressed](){ pressed = true;});
        button.press();
        REQUIRE(pressed == false);
        button.active();
        button.press();
        REQUIRE(pressed == true);
    }

}

} // namespace msgui
