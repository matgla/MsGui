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

add_executable(msgui_ut ${test_sources})
target_link_libraries(msgui_ut msgui)
add_test(msgui_build_ut
         "${CMAKE_COMMAND}" --build ${CMAKE_BINARY_DIR} --target msgui_ut)


add_test(NAME msgui_tests COMMAND msgui_ut)
set_tests_properties(msgui_tests
    PROPERTIES DEPENDS msgui_build_ut)
