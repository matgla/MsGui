#include "catch.hpp"

#include "msgui/Factory.hpp"

#include "UT/stubs/DriverForTest.hpp"

namespace msgui
{

TEST_CASE("Button should", "[Button]")
{
    stubs::DriverForTest driver;
    using factory = Factory<stubs::DriverForTest>;
    factory::setDriver(driver);

    SECTION("perform action")
    {
        auto button  = factory::make_button<32>();
        bool pressed = false;
        button.onClick([&pressed]() { pressed = true; });
        button.press();
        REQUIRE(pressed == false);
        button.active();
        button.press();
        REQUIRE(pressed == true);
    }
}

} // namespace msgui
