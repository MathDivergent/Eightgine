function(eightgine_copy_shared_library_to_binaries_dir)
    set(ARGS TARGET_NAME DEPENDENCY_NAME DEPENDENCY_BIN_DIR)
    cmake_parse_arguments("ARG" "" "${ARGS}" "" ${ARGN})

    set(DEPENDENCY_BIN_SRC "${ARG_DEPENDENCY_BIN_DIR}/${ARG_DEPENDENCY_NAME}.dll")
    set(DEPENDENCY_BIN_DST "$<TARGET_FILE_DIR:${ARG_TARGET_NAME}>/${ARG_DEPENDENCY_NAME}.dll")

    add_custom_command(TARGET "${ARG_TARGET_NAME}" POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${DEPENDENCY_BIN_SRC}" "${DEPENDENCY_BIN_DST}")
endfunction()

function(eightgine_set_target_dependency)
    set(ARGS TARGET_NAME DEPENDENCY_NAME DEPENDENCY_INCLUDE_DIR DEPENDENCY_LIB_DIR DEPENDENCY_BIN_DIR)
    cmake_parse_arguments("ARG" "" "${ARGS}" "" ${ARGN})

    if(ARG_DEPENDENCY_INCLUDE_DIR)
        target_include_directories("${ARG_TARGET_NAME}" PUBLIC "${ARG_DEPENDENCY_INCLUDE_DIR}")
    endif()

    if(ARG_DEPENDENCY_LIB_DIR)
        target_link_directories("${ARG_TARGET_NAME}" PUBLIC "${ARG_DEPENDENCY_LIB_DIR}")
    endif()

    if(ARG_DEPENDENCY_BIN_DIR)
        eightgine_copy_shared_library_to_binaries_dir(TARGET_NAME "${ARG_TARGET_NAME}" DEPENDENCY_NAME "${ARG_DEPENDENCY_NAME}"
            DEPENDENCY_BIN_DIR "${ARG_DEPENDENCY_BIN_DIR}"
        )
    endif()

    target_link_libraries("${ARG_TARGET_NAME}" PUBLIC "${ARG_DEPENDENCY_NAME}")
endfunction()

macro(eightgine_find_source_files)
    set(ARGS OUTPUT SOURCES_DIR)
    cmake_parse_arguments("ARG" "" "${ARGS}" "" ${ARGN})

    file(GLOB_RECURSE "${ARG_OUTPUT}" "${ARG_SOURCES_DIR}/*.cpp" "${ARG_SOURCES_DIR}/*.hpp" "${ARG_SOURCES_DIR}/*.h")
endmacro()
