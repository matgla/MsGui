include_directories(../lib)
include_directories(${PROJECT_SOURCE_DIR})

set (test_sources
    GraphicDriverTests.cpp
    Runner.cpp
    WidgetBaseTests.cpp
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-result -std=c++1z -Wall -Wextra")

if (DEBUG)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Og")
else (DEBUG)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
endif (DEBUG)

add_executable(msgui_tests ${test_sources})
target_link_libraries(msgui_tests msgui)
enable_testing()