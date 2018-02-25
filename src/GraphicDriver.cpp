#include "msgui/GraphicDriver.hpp"

namespace msgui
{

GraphicDriver::GraphicDriver(SetPixelCallback setPixel, GetWidthCallback getWidth, GetHeightCallback getHeight, DrawCallback draw)
    : setPixel_(setPixel),
      getWidth_(getWidth),
      getHeight_(getHeight),
      draw_(draw)
{
}

void GraphicDriver::setPixel(int x, int y, bool enable)
{
    if (x < 0 || x >= getWidth_())
    {
        return;
    }
    if (y < 0 || y >= getHeight_())
    {
        return;
    }
    setPixel_(x, y, enable);
}

int GraphicDriver::width() const
{
    return getWidth_();
}

int GraphicDriver::height() const
{
    return getHeight_();
}

void GraphicDriver::draw()
{
    draw_();
}


} // namespace msgui