cmake_minimum_required(VERSION 3.1)

project(msgui CXX)

set(MS_GUI_VERSION_MAJOR 0 CACHE STRING "major version of MsGUI")
set(MS_GUI_VERSION_MINOR 2 CACHE STRING "minor version of MsGUI")
set(MS_GUI_VERSION "${MS_GUI_VERSION_MAJOR} ${MS_GUI_VERSION_MAJOR}")

add_subdirectory(lib)
add_subdirectory(src)
if (BUILD_TESTS)
    add_subdirectory(test)
endif (BUILD_TESTS)

if (BUILD_DOCUMENTATION)
    set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/Modules")
    add_subdirectory(docs)
endif ()