#include "catch.hpp"

#include "msgui/Factory.hpp"
#include <iostream>

#include "UT/stubs/DriverForTest.hpp"

namespace msgui
{

TEST_CASE("Window should", "[Window]")
{
    stubs::DriverForTest driver;
    using factory = Factory<stubs::DriverForTest>;
    factory::setDriver(driver);

    SECTION("Construct window")
    {
        auto button = factory::make_button();
        auto window = factory::configure_window().make(button);
    }
}

} // namespace msgui
