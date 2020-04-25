#pragma once

#include <utility>

#include <msgui/BitMap.hpp>
#include <msgui/WidgetBase.hpp>
#include <msgui/Position.hpp>

namespace msgui
{

static inline uint64_t get_microseconds()
{
    struct timeval val;
    gettimeofday(&val, NULL);
    return (val.tv_sec * 1000000 + val.tv_usec);
}

template <typename BitMapType>
class AnimatedSprite
    : public WidgetBase<eul::events<16>>
{
public:
    constexpr AnimatedSprite(Position position, const BitMapType& bitmap, int frame_offset, int time)
        : WidgetBase<eul::events<16>>(position)
        , bitmap_(&bitmap)
        , frame_number_(0)
        , frame_offset_(frame_offset)
        , number_of_frames_(bitmap.width() / frame_offset_)
        , time_(time)
        , prev_time_(0)
    {

    }

    template <typename DriverType>
    void draw(DriverType& driver)
    {
        Position pos = this->position_;

        int x_offset = frame_number_ * frame_offset_;

        for (int y = 0; y < bitmap_->height(); ++y)
        {
            for (int x = x_offset; x < x_offset + frame_offset_; ++x)
            {
                if (bitmap_->getPixel(x, y))
                {
                    driver.set_pixel(x + pos.x - x_offset, y + pos.y);
                }
            }
        }

        if (get_microseconds() - prev_time_ >= 1000 * time_)
        {
            prev_time_ = get_microseconds();
            if (frame_number_ == number_of_frames_ - 1)
            {
                frame_number_ = 0;
            }
            else
            {
                ++frame_number_;
            }
        }
    }

    bool has_pixel(msgui::Position position) const
    {
        int x_offset = frame_number_ * frame_offset_;

        if (position.x >= x_offset + frame_offset_ || position.x <= 0)
        {
            return false;
        }

        return bitmap_->getPixel(x_offset + position.x, position.y);
    }

    template <typename DriverType>
    void draw(DriverType& driver) const
    {
        const_cast<AnimatedSprite<BitMapType>*>(this)->draw(driver);
    }

private:
    const BitMapType* bitmap_;
    int frame_number_;
    int frame_offset_;
    int number_of_frames_;
    uint64_t time_;
    uint64_t prev_time_;
};

} // namespace msgui
