#include "catch.hpp"

#include <string>

#include "msgui/WidgetBase.hpp"

namespace msgui
{

template<typename Events>
class WidgetForTest : public WidgetBase<Events>
{
public:
    WidgetForTest(const Vector2d& position) : WidgetBase<Events>(position)
    {
    }
    
    void draw() const override
    {
    }

    bool visible()
    {
        return this->visible_;
    }
    
    bool isActive()
    {
        return this->active_;
    }
};

using WidgetWithoutActions = WidgetForTest<eul::events<0>>;

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
        
        WidgetForTest<eul::events<16, TestEvent>> widget;
        widget.process(TestEvent{"some data"});
        
    }
}

} // namespace msgui