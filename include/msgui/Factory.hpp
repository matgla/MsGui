#include "msgui/Button.hpp"
#include "msgui/GraphicDriver.hpp"

namespace msgui
{

template <GraphicDriver GraphicDriverType>
class Factory
{
public:
    constexpr static void setDriver(GraphicDriverType& driver)
    {
        Factory<GraphicDriverType>::driver_ = &driver;
    }

    template <std::size_t CallbackSize>
    constexpr static auto button(const Position& position = {0, 0})
    {
        return Button<CallbackSize, GraphicDriverType>(position, *driver_);
    }

    inline static GraphicDriverType* driver_;
};

} // namespace msgui
