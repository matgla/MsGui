#include "UT/stubs/DriverForTest.hpp"

#include "msgui/Position.hpp"
#include "msgui/WidgetBase.hpp"

namespace msgui
{
namespace stubs
{

template <typename Events>
class WidgetForTest : public WidgetBase<Events, DriverForTest>
{
public:
    WidgetForTest(const Position& position)
        : WidgetBase<Events, DriverForTest>(position, driverForTest_)
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

    DriverForTest driverForTest_;
};

} // namespace stubs
} // namespace msgui
