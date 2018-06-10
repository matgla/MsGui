#include "msgui/Color.hpp"
#include "msgui/Position.hpp"

namespace msgui
{
namespace stubs
{

class DriverForTest
{
public:
    void setPixel(const Position& position, const Color& color)
    {
        (void)position;
        (void)color;
    }

    int width()
    {
        return 0;
    }

    int height()
    {
        return 0;
    }

    void draw()
    {
    }
};

} // namespace stubs
} // namespace msgui
