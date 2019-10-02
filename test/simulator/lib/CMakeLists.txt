include (../../../cmake/GitModules.cmake)

fetch_module_via_branch(test/simulator/lib/bitmap/bitmap ${CMAKE_CURRENT_SOURCE_DIR}/bitmap ${PROJECT_SOURCE_DIR} "master")
