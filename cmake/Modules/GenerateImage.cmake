function (generate_image target image_path output_file image_name namespace)
    set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS ${image_path})

    add_custom_command(OUTPUT ${output_file}
        COMMAND ${image_generator} -i ${image_path} -o ${output_file} -s ${image_name} -n ${namespace}
    )

    file (TOUCH ${CMAKE_BINARY_DIR}/dummy.cpp)
    add_library(${image_name} STATIC ${output_file} ${CMAKE_BINARY_DIR}/dummy.cpp)
    target_link_libraries(${target} INTERFACE ${image_name})
endfunction()
