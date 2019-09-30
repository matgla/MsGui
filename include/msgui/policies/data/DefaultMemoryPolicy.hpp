// TODO: move avr dependencies to HAL

#pragma once

#include <array>

namespace msgui
{
namespace policies
{
namespace data
{

template <typename DataType>
class DefaultMemoryPolicy;

template<>
class DefaultMemoryPolicy<uint8_t>
{
public:
    template <typename DataType>
    static uint8_t read(const DataType& data, std::size_t index)
    {
        if (index > data.size())
        {
            return 0; // TODO: some error handling should be added
        }

        return data[index];
    }

    template <typename DataType>
    constexpr static void write(const DataType& data, std::size_t index, uint8_t value)
    {
        if (index > data.size())
        {
            return; // TODO: some error handling should be added
        }
        data[index] = value;
    }
};

} // namespace data
} // namespace policies
} // namespace msgui
