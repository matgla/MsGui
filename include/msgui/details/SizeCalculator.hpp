#pragma once

namespace msgui
{
namespace details
{

template <typename Type>
constexpr std::size_t make_size(const int width, const int height)
{
    constexpr int bits_in_byte = 8;
    const float fsize      = static_cast<float>(width) * static_cast<float>(height) / (bits_in_byte * sizeof(Type));
    const std::size_t size = static_cast<std::size_t>(fsize);
    if (fsize == static_cast<float>(size))
    {
        return size;
    }
    return size + 1;
}

template <typename Type, int width, int height>
struct GetSize
{
    static_assert(width >= 0, "Width must be >= 0");
    static_assert(height >= 0, "Height must be >= 0");
    constexpr static std::size_t value = make_size<Type>(width, height);
};

} // namespace details
} // namespace msgui
