cmake_minimum_required(VERSION 3.1)

project(msgui CXX)

set(MS_GUI_VERSION_MAJOR 0 CACHE STRING "major version of MsGUI")
set(MS_GUI_VERSION_MINOR 1 CACHE STRING "minor version of MsGUI")
set(MS_GUI_VERSION "${MS_GUI_VERSION_MAJOR} ${MS_GUI_VERSION_MAJOR}")

add_subdirectory(lib)
add_subdirectory(src)
if (BUILD_TESTS)
    add_subdirectory(test)
endif (BUILD_TESTS)