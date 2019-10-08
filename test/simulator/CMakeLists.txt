add_subdirectory(lib)
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/test)

set (simulator_sources
    simulator/SSD1306Simulator.hpp
    ExampleWindow.cpp
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -Wno-unused-result -std=c++1z -Wall -Wextra -fconcepts")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (DEBUG)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Og -g")
else (DEBUG)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
endif (DEBUG)


add_executable(simulator ${simulator_sources})
target_link_libraries(simulator msgui bitmap)
enable_testing()