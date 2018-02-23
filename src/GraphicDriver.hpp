#pragma once

#include <functional>

namespace msgui
{

class GraphicDriver
{
public:
    using SetPixelCallback  = std::function<void(int, int, bool)>;
    using GetWidthCallback  = std::function<int()>;
    using GetHeightCallback = std::function<int()>;
    using DrawCallback      = std::function<void()>;

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