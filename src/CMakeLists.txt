set(SOURCES_DIR "${PROJECT_SOURCE_DIR}/src")
set(INCLUDES_DIR "${PROJECT_SOURCE_DIR}/include")

set (production_includes
    ${INCLUDES_DIR}/msgui/Area.hpp
    ${INCLUDES_DIR}/msgui/BitMap.hpp
    ${INCLUDES_DIR}/msgui/BitMapHelpers.hpp
    ${INCLUDES_DIR}/msgui/GraphicDriver.hpp
    ${INCLUDES_DIR}/msgui/Font.hpp
    ${INCLUDES_DIR}/msgui/fonts/Font5x7.hpp
    ${INCLUDES_DIR}/msgui/Gui.hpp
    ${INCLUDES_DIR}/msgui/primitives/IShape.hpp
    ${INCLUDES_DIR}/msgui/primitives/Line.hpp
    ${INCLUDES_DIR}/msgui/primitives/Rectangle.hpp
    ${INCLUDES_DIR}/msgui/WidgetBase.hpp
    ${INCLUDES_DIR}/msgui/Window.hpp
)

set (sources
    ${SOURCES_DIR}/fonts/Font5x7.cpp
    ${production_sources}
)

add_library(msgui STATIC)
target_sources(msgui
    PRIVATE
        ${sources})

target_compile_options(msgui
    PRIVATE
        $<$<COMPILE_LANGUAGE:CXX>:${msgui_cxx_compilation_flags} -fconcepts -Wall -Wextra -Wpedantic -Wconversion -Wcast-align -Wunused -Wshadow -Wold-style-cast -Wpointer-arith -Wcast-qual -Wno-missing-braces>
        $<$<CONFIG:DEBUG>:-Og -g>
        $<$<CONFIG:RELEASE>:-Os>
)

target_link_options(msgui
    PRIVATE
        ${msgui_linking_flags}
)

target_link_libraries(msgui PUBLIC eul_utils)
target_include_directories(msgui PUBLIC ${PROJECT_SOURCE_DIR}/include)
