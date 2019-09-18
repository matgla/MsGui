#include "msgui/Color.hpp"
#include "msgui/Position.hpp"

#include <eul/utils/unused.hpp>

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

    uint32_t width()
    {
        return 0;
    }

    uint32_t height()
    {
        return 0;
    }

    void draw()
    {
    }

    template <typename ChunkType>
    void write(const ChunkType data)
    {
        UNUSED1(data);
    }
};

} // namespace stubs
} // namespace msgui
