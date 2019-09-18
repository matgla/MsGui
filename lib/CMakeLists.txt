include (../cmake/GitModules.cmake)

set(DISABLE_TESTS "ON")
fetch_module_via_branch(lib/eul ${CMAKE_CURRENT_SOURCE_DIR}/eul ${PROJECT_SOURCE_DIR} "master")
