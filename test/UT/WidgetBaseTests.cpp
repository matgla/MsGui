#include "catch.hpp"

#include <string>

#include "UT/stubs/WidgetForTest.hpp"
#include "msgui/WidgetBase.hpp"

namespace msgui
{

using WidgetWithoutActions = stubs::WidgetForTest<eul::events<0>>;

TEST_CASE("WidgetBase should", "[WidgetBase]")
{
    WidgetWithoutActions widget({0, 0});
    SECTION("Show")
    {
        widget.hide();
        REQUIRE_FALSE(widget.visible());
        widget.show();
        REQUIRE(widget.visible());
    }

    SECTION("Hide")
    {
        widget.show();
        REQUIRE(widget.visible());
        widget.hide();
        REQUIRE_FALSE(widget.visible());
    }

    SECTION("Active")
    {
        widget.inactive();
        REQUIRE_FALSE(widget.isActive());
        widget.active();
        REQUIRE(widget.isActive());
    }

    SECTION("Inactive")
    {
        widget.active();
        REQUIRE(widget.isActive());
        widget.inactive();
        REQUIRE_FALSE(widget.isActive());
    }

    SECTION("Process event when active")
    {
        struct TestEvent
        {
            std::string payload;
        };

        int nrOfCalls = 0;

        REQUIRE(0 == nrOfCalls);

        stubs::WidgetForTest<eul::events<16, TestEvent>> widget({0, 0});
        widget.process(TestEvent{"some data"});
        REQUIRE(0 == nrOfCalls);

        widget.process(TestEvent{"some other data"});
        widget.registerHandler<TestEvent>([&nrOfCalls](const TestEvent& event) { static_cast<void>(event); ++nrOfCalls; });
        REQUIRE(0 == nrOfCalls);

        widget.active();
        REQUIRE(widget.isActive());
        widget.process(TestEvent{"some other data"});
        REQUIRE(1 == nrOfCalls);
    }
}

} // namespace msgui