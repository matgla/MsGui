#pragma once

namespace msgui
{
namespace primitives
{

class IShape
{
public:
    virtual void draw() = 0;
    virtual ~IShape()   = default;
};

} // namespace primitives
} // namespace gui