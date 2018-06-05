#pragma once

#include <cstdint>

namespace msgui
{

template <typename T>
concept Color = requires(T t)
{
    { t.redValue() -> int },
    { t.greenValue() -> int },
    { t.blueValue() -> int }
};

} // namespace msgui