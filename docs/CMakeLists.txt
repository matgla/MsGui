find_package(Doxygen REQUIRED)

configure_file(${PROJECT_SOURCE_DIR}/docs/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)

add_custom_target (build_doxygen ALL
    COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating documentation with Doxygen"
    VERBATIM
)

find_package(Sphinx REQUIRED)

add_custom_target(build_sphinx ALL
    COMMAND ${SPHINX_EXECUTABLE} -b html -Dbreathe_projects.MsGUI=${CMAKE_CURRENT_BINARY_DIR}/docs/doc/xml ${PROJECT_SOURCE_DIR}/docs/source ${CMAKE_CURRENT_BINARY_DIR}/docs/sphinx
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating documentation with Sphinx"
    VERBATIM
)