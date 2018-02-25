set(SOURCES_DIR "${PROJECT_SOURCE_DIR}/src")
set(INCLUDES_DIR "${PROJECT_SOURCE_DIR}/include")

set (production_includes
    ${INCLUDES_DIR}/msgui/Area.hpp 
    ${INCLUDES_DIR}/msgui/BitMap.hpp 
    ${INCLUDES_DIR}/msgui/BitMapHelpers.hpp 
    ${INCLUDES_DIR}/msgui/GraphicDriver.hpp 
    ${INCLUDES_DIR}/msgui/Gui.hpp 
    ${INCLUDES_DIR}/msgui/IWidget.hpp 
    ${INCLUDES_DIR}/msgui/primitives/IShape.hpp 
    ${INCLUDES_DIR}/msgui/primitives/Line.hpp 
    ${INCLUDES_DIR}/msgui/primitives/Rectangle.hpp 
    ${INCLUDES_DIR}/msgui/WidgetBase.hpp 
    ${INCLUDES_DIR}/msgui/Window.hpp 
)

set (production_sources
    ${SOURCES_DIR}/GraphicDriver.cpp 
    ${SOURCES_DIR}/WidgetBase.cpp 
)

set (sources
    ${production_includes}
    ${production_sources}
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-result -std=c++1z -Wall -Wextra")

if (DEBUG)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Og")
else (DEBUG)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
endif (DEBUG)

add_library(msgui ${sources})
target_include_directories(msgui PUBLIC ${INCLUDES_DIR})
