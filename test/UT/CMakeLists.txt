include_directories(../lib)
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/test)

set (test_sources
    BitMapTests.cpp
    BitwiseChunkTests.cpp
    Runner.cpp
    WidgetBaseTests.cpp
    ButtonTests.cpp
    WindowTests.cpp
    ImageTests.cpp
    TextTests.cpp
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -Wno-unused-result -std=c++1z -Wall -Wextra -fconcepts")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (DEBUG)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Og -g")
else (DEBUG)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
endif (DEBUG)

if (ASAN_ENABLED)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
endif (ASAN_ENABLED)

add_executable(msgui_tests ${test_sources})
target_link_libraries(msgui_tests msgui)
enable_testing()