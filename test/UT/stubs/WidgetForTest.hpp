#include "UT/stubs/DriverForTest.hpp"

#include "msgui/Position.hpp"
#include "msgui/WidgetBase.hpp"

namespace msgui
{
namespace stubs
{

template <typename Events>
class WidgetForTest : public WidgetBase<Events, DriverForTest<0,0>>
{
public:
    WidgetForTest(const Position& position)
        : WidgetBase<Events, DriverForTest<0,0>>(position, driverForTest_)
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

    DriverForTest<0,0> driverForTest_;
};

} // namespace stubs
} // namespace msgui
