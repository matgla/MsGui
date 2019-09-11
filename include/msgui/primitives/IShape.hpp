#pragma once

#include "msgui/Color.hpp"

namespace msgui
{
namespace primitives
{

class IShape
{
public:
    virtual void draw(const msgui::Color& color) = 0;
    // virtual ~IShape()                            = default;
};

} // namespace primitives
} // namespace msgui