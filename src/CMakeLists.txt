set(SOURCES_DIR "${PROJECT_SOURCE_DIR}/src")

include_directories(${SOURCES_DIR})

set (production_includes
    ${SOURCES_DIR}/msgui/Area.hpp 
    ${SOURCES_DIR}/msgui/GraphicDriver.hpp 
    ${SOURCES_DIR}/msgui/Gui.hpp 
    ${SOURCES_DIR}/msgui/IWidget.hpp 
    ${SOURCES_DIR}/msgui/primitives/IShape.hpp 
    ${SOURCES_DIR}/msgui/primitives/Line.hpp 
    ${SOURCES_DIR}/msgui/primitives/Rectangle.hpp 
    ${SOURCES_DIR}/msgui/WidgetBase.hpp 
    ${SOURCES_DIR}/msgui/Window.hpp 
)

set (production_sources
    ${SOURCES_DIR}/msgui/GraphicDriver.cpp 
    ${SOURCES_DIR}/msgui/WidgetBase.cpp 
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

