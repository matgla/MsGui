#include "catch.hpp"

#include "src/WidgetBase.hpp"

namespace msgui
{

class WidgetForTest : public WidgetBase
{
public:
    void draw() const override
    {
    }

    bool visible()
    {
        return visible_;
    }
};

TEST_CASE("WidgetBase should", "[WidgetBase]")
{
    WidgetForTest widget;
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
}

} // namespace msgui