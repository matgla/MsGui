#pragma once

#include "eul/function.hpp"

namespace msgui
{

class GraphicDriver
{
public:
    using SetPixelCallback  = eul::function<void(int, int, bool), 8>;
    using GetWidthCallback  = eul::function<int(), 8>;
    using GetHeightCallback = eul::function<int(), 8>;
    using DrawCallback      = eul::function<void(), 8>;

    GraphicDriver(SetPixelCallback setPixel, GetWidthCallback getWidth, GetHeightCallback getHeight, DrawCallback draw);

    void setPixel(int x, int y, bool enable);
    int width() const;
    int height() const;
    void draw();

private:
    SetPixelCallback setPixel_;
    GetWidthCallback getWidth_;
    GetHeightCallback getHeight_;
    DrawCallback draw_;
};

} // namespace msgui