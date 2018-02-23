set(SOURCES_DIR "${PROJECT_SOURCE_DIR}/src")

include_directories(SOURCES_DIR)

set (production_includes
    ${SOURCES_DIR}/IWidget.hpp 
    ${SOURCES_DIR}/GraphicDriver.hpp 
    ${SOURCES_DIR}/WidgetBase.hpp 
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

