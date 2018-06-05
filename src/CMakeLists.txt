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
    ${INCLUDES_DIR}/msgui/IWidget.hpp 
    ${INCLUDES_DIR}/msgui/primitives/IShape.hpp 
    ${INCLUDES_DIR}/msgui/primitives/Line.hpp 
    ${INCLUDES_DIR}/msgui/primitives/Rectangle.hpp 
    ${INCLUDES_DIR}/msgui/WidgetBase.hpp 
    ${INCLUDES_DIR}/msgui/Window.hpp 
)

set (sources
    ${production_sources}
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-result -std=c++1z -Wall -Wextra -fconcepts")

if (DEBUG)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Og")
else (DEBUG)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
endif (DEBUG)

add_library(msgui INTERFACE)
target_sources(msgui INTERFACE ${sources})
target_link_libraries(msgui INTERFACE eul)
