#pragma once

#include <array>

namespace msgui
{

template <typename Type, std::size_t BufferSize>
class StaticVector
{
public:
    StaticVector()
        : firstFreePosition_(0)
    {
    }

    void push_back(const Type& data)
    {
        if (firstFreePosition_ >= BufferSize)
        {
            return;
        }

        data_[firstFreePosition_] = data;
        ++firstFreePosition_;
    }

    std::size_t size() const
    {
        return firstFreePosition_;
    }

    typedef Type* iterator;
    typedef const Type* const_iterator;

    iterator begin()
    {
        return &data_[0];
    }

    const_iterator begin() const
    {
        return &data_[0];
    }

    iterator end()
    {
        return &data_[firstFreePosition_];
    }

    const_iterator end() const
    {
        return &data_[firstFreePosition_];
    }

    Type pop_back()
    {
        if (0 == firstFreePosition_)
        {
            return {};
        }
        --firstFreePosition_;
        return data_[firstFreePosition_];
    }

    Type get_last()
    {
        if (0 == size())
        {
            return {};
        }

        return data_[firstFreePosition_ - 1];
    }

    int find(int data) const
    {
        for (std::size_t i = 0; i < data_.size(); i++)
        {
            if (data == data_[i])
            {
                return i;
            }
        }
        return -1;
    }

private:
    std::size_t firstFreePosition_;
    std::array<Type, BufferSize> data_;
};

} // namespace msgui