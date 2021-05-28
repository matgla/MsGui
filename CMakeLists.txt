cmake_minimum_required(VERSION 3.1)

project(msgui CXX)

find_package (Python3 COMPONENTS Interpreter) 

include(FetchContent)

FetchContent_Declare(
  mspkg
  GIT_REPOSITORY https://github.com/matgla/mspkg.git
  GIT_TAG        master
)

FetchContent_MakeAvailable(mspkg)

set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${mspkg_SOURCE_DIR}/cmake)
include (mspkg)

setup_mspkg(${mspkg_SOURCE_DIR})

find_package(eul REQUIRED)


set(MS_GUI_VERSION_MAJOR 0 CACHE STRING "major version of MsGUI")
set(MS_GUI_VERSION_MINOR 2 CACHE STRING "minor version of MsGUI")
set(MS_GUI_VERSION "${MS_GUI_VERSION_MAJOR} ${MS_GUI_VERSION_MAJOR}")

set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/Modules" CACHE STRING "CMake flags")
set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/scripts/generate_image.py)

set (image_generator ${PROJECT_SOURCE_DIR}/scripts/generate_image.py CACHE INTERNAL "")

add_subdirectory(lib)
add_subdirectory(src)
if (BUILD_TESTS)
    include(CTest)
    add_subdirectory(test)
endif (BUILD_TESTS)

if (BUILD_DOCUMENTATION)
    add_subdirectory(docs)
endif ()
