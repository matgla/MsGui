#include <utility>
#include <string_view>


#include "msgui/Button.hpp"
#include "msgui/Text.hpp"
#include "msgui/Window.hpp"
#include "msgui/BitMap.hpp"
#include "msgui/Image.hpp"

namespace msgui
{


template <typename GraphicDriverType, typename MemoryPolicy, template<typename, typename> typename ChunkPolicy, typename ChunkParameters>
class Factory
{
public:
    constexpr Factory(GraphicDriverType& driver) : driver_(driver)
    {
    }

    template <std::size_t CallbackSize = 0>
    constexpr auto make_button(const Position& position = {0, 0})
    {
        return Button<CallbackSize, GraphicDriverType, ChunkPolicy, ChunkParameters>(position, driver_);
    }

    constexpr WindowConfig<GraphicDriverType, MemoryPolicy, ChunkPolicy, ChunkParameters> configure_window()
    {
        return WindowConfig<GraphicDriverType, MemoryPolicy, ChunkPolicy, ChunkParameters>(driver_);
    }

    template <typename FontType, std::size_t CallbackSize = 0>
    constexpr auto make_text(const std::string_view& text, const FontType& font, const Position& position = {0, 0}, const Color& color = colors::black())
    {
        return Text<CallbackSize, FontType, GraphicDriverType, ChunkPolicy, ChunkParameters>(driver_, text.data(), position, font, color);
    }

    template <int Width, int Height, typename... Data>
    constexpr auto make_bitmap(Data&&... data)
    {
        return BitMap<Width, Height, MemoryPolicy, ChunkPolicy, ChunkParameters>(std::forward<Data>(data)...);
    }

    template <int Width, int Height, typename... Data>
    constexpr auto make_image(Position pos, Data&&... data)
    {
        using BitMapType = BitMap<Width, Height, MemoryPolicy, ChunkPolicy, ChunkParameters>;
        return Image<GraphicDriverType, BitMapType>(pos, driver_, BitMapType(std::forward<Data>(data)...));
    }

    GraphicDriverType& driver_;
};

} // namespace msgui
