#pragma once

#include <array>
#include <cstdint>
#include <tuple>

namespace msgui
{
constexpr uint8_t BITS_IN_BYTE = 8;

constexpr void make_pixel(uint8_t*)
{
}

template <size_t N, typename... Args>
constexpr decltype(auto) get(Args&&... args) noexcept
{
    return std::get<N>(std::forward_as_tuple(std::forward<Args>(args)...));
}

template <typename... Data>
constexpr void make_pixel(uint8_t* byte, bool d0, bool d1, bool d2, bool d3, bool d4, bool d5, bool d6, bool d7, Data... nextData)
{
    *byte = (d0 << 7) | (d1 << 6) | (d2 << 5) | (d3 << 4) | (d4 << 3) | (d5 << 2) | (d6 << 1) | d7;
    if constexpr (sizeof...(nextData) >= 8)
    {
        make_pixel(++byte, nextData...);
    }
    else
    {
        if constexpr (sizeof...(nextData) == 7)
        {
            make_pixel(++byte, get<0>(nextData...), get<1>(nextData...), get<2>(nextData...),
                       get<3>(nextData...), get<4>(nextData...), get<5>(nextData...), get<6>(nextData...), 0);
        }
        if constexpr (sizeof...(nextData) == 6)
        {
            make_pixel(++byte, get<0>(nextData...), get<1>(nextData...), get<2>(nextData...),
                       get<3>(nextData...), get<4>(nextData...), get<5>(nextData...), 0, 0);
        }
        if constexpr (sizeof...(nextData) == 5)
        {
            make_pixel(++byte, get<0>(nextData...), get<1>(nextData...), get<2>(nextData...),
                       get<3>(nextData...), get<4>(nextData...), 0, 0, 0);
        }
        if constexpr (sizeof...(nextData) == 4)
        {
            make_pixel(++byte, get<0>(nextData...), get<1>(nextData...), get<2>(nextData...),
                       get<3>(nextData...), 0, 0, 0, 0);
        }
        if constexpr (sizeof...(nextData) == 3)
        {
            make_pixel(++byte, get<0>(nextData...), get<1>(nextData...), get<2>(nextData...), 0, 0, 0, 0, 0);
        }
        if constexpr (sizeof...(nextData) == 2)
        {
            make_pixel(++byte, get<0>(nextData...), get<1>(nextData...), 0, 0, 0, 0, 0, 0);
        }
        if constexpr (sizeof...(nextData) == 1)
        {
            make_pixel(++byte, get<0>(nextData...), 0, 0, 0, 0, 0, 0, 0);
        }
    }
}

template <typename Type>
constexpr std::size_t make_size(const int width, const int height)
{
    const float fsize      = static_cast<float>(width) * static_cast<float>(height) / (BITS_IN_BYTE * sizeof(Type));
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

template <int width, int height, typename... Data>
constexpr const std::array<uint8_t, GetSize<uint8_t, width, height>::value> make_bitmap(Data... data)
{
    std::array<uint8_t, GetSize<uint8_t, width, height>::value> bitmap{};

    if constexpr (sizeof...(data) >= 8)
    {
        make_pixel(bitmap.data(), data...);
    }
    else
    {
        if constexpr (sizeof...(data) == 7)
        {
            make_pixel(bitmap.data(), get<0>(data...), get<1>(data...), get<2>(data...),
                       get<3>(data...), get<4>(data...), get<5>(data...), get<6>(data...), 0);
        }
        if constexpr (sizeof...(data) == 6)
        {
            make_pixel(bitmap.data(), get<0>(data...), get<1>(data...), get<2>(data...),
                       get<3>(data...), get<4>(data...), get<5>(data...), 0, 0);
        }
        if constexpr (sizeof...(data) == 5)
        {
            make_pixel(bitmap.data(), get<0>(data...), get<1>(data...), get<2>(data...),
                       get<3>(data...), get<4>(data...), 0, 0, 0);
        }
        if constexpr (sizeof...(data) == 4)
        {
            make_pixel(bitmap.data(), get<0>(data...), get<1>(data...), get<2>(data...),
                       get<3>(data...), 0, 0, 0, 0);
        }
        if constexpr (sizeof...(data) == 3)
        {
            make_pixel(bitmap.data(), get<0>(data...), get<1>(data...), get<2>(data...), 0, 0, 0, 0, 0);
        }
        if constexpr (sizeof...(data) == 2)
        {
            make_pixel(bitmap.data(), get<0>(data...), get<1>(data...), 0, 0, 0, 0, 0, 0);
        }
        if constexpr (sizeof...(data) == 1)
        {
            make_pixel(bitmap.data(), get<0>(data...), 0, 0, 0, 0, 0, 0, 0);
        }
    }
    return std::move(bitmap);
}

} // namespace msgui