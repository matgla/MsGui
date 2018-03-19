#include "catch.hpp"

#include "msgui/WidgetBase.hpp"

namespace msgui
{

class WidgetForTest : public WidgetBase<>
{
public:
    WidgetForTest(const Vector2d& position) : WidgetBase(position)
    {
    }
    
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
    WidgetForTest widget({0, 0});
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