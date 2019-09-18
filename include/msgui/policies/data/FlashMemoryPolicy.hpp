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
class FlashMemoryPolicy;

template<>
class FlashMemoryPolicy<uint8_t>
{
public:
    template <typename DataType>
    constexpr static uint8_t read(const DataType& data, std::size_t index)
    {
        if (index > data.size())
        {
            return 0; // TODO: some error handling should be added
        }

        return data[index];//pgm_read_byte(&data[index]);
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
