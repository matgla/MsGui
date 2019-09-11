include (../cmake/GitModules.cmake)

fetch_module_via_branch(lib/eul ${CMAKE_CURRENT_SOURCE_DIR}/eul ${PROJECT_SOURCE_DIR} "master")
