function(eightgine_create_junction)
    set(ONE_VALUE_ARGS ORIGINAL LINKNAME)
    cmake_parse_arguments("ARG" "" "${ONE_VALUE_ARGS}" "" ${ARGN})

    file(TO_NATIVE_PATH "${ARG_ORIGINAL}" ORIGINAL_NATIVE)
    file(TO_NATIVE_PATH "${ARG_LINKNAME}" LINKNAME_NATIVE)

    get_filename_component(ORIGINAL_ABS "${ORIGINAL_NATIVE}" ABSOLUTE)
    get_filename_component(ORIGINAL_REAL "${ORIGINAL_ABS}" REALPATH)

    get_filename_component(LINKNAME_ABS "${LINKNAME_NATIVE}" ABSOLUTE)
    get_filename_component(LINKNAME_REAL "${LINKNAME_ABS}" REALPATH)

    if(ORIGINAL_REAL STREQUAL LINKNAME_REAL)
        return()
    endif()

    if(NOT EXISTS "${LINKNAME_NATIVE}")
        execute_process(
            COMMAND cmd /c mklink /J "${LINKNAME_NATIVE}" "${ORIGINAL_NATIVE}"
            RESULT_VARIABLE RESULT
            ERROR_VARIABLE ERRORS
            WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
        )

        if(NOT RESULT EQUAL 0)
            message(FATAL_ERROR "Junction '${LINKNAME_NATIVE} -> ${ORIGINAL_NATIVE}' creation failed:\n${ERRORS}")
        endif()
    endif()
endfunction()

function(eightgine_file)
    set(ONE_VALUE_ARGS MODULE_OR_EXECUTABLE_SOURCE_FILES MODULE_OR_EXECUTABLE_SOURCES_DIR)
    cmake_parse_arguments("ARG" "" "${ONE_VALUE_ARGS}" "" ${ARGN})

    file(GLOB_RECURSE SOURCE_FILES
        "${ARG_MODULE_OR_EXECUTABLE_SOURCES_DIR}/*.cpp"
        "${ARG_MODULE_OR_EXECUTABLE_SOURCES_DIR}/*.hpp" "${ARG_MODULE_OR_EXECUTABLE_SOURCES_DIR}/*.h"
    )
    set(${ARG_MODULE_OR_EXECUTABLE_SOURCE_FILES} ${SOURCE_FILES} PARENT_SCOPE)

    foreach(SOURCE_FILE IN LISTS SOURCE_FILES)
        get_filename_component(SOURCE_FILE_PATH "${SOURCE_FILE}" PATH)

        file(RELATIVE_PATH GROUP_NAME "${CMAKE_CURRENT_SOURCE_DIR}" "${SOURCE_FILE_PATH}")
        string(REPLACE "/" "\\" GROUP_NAME "${GROUP_NAME}")

        source_group("${GROUP_NAME}" FILES "${SOURCE_FILE}")
    endforeach()
endfunction()

function(eightgine_add_module)
    set(ONE_VALUE_ARGS MODULE_NAME MODULE_SOURCES_DIR)
    cmake_parse_arguments("ARG" "" "${ONE_VALUE_ARGS}" "" ${ARGN})

    eightgine_file(MODULE_OR_EXECUTABLE_SOURCE_FILES MODULE_SOURCE_FILES
        MODULE_OR_EXECUTABLE_SOURCES_DIR "${ARG_MODULE_SOURCES_DIR}"
    )

    add_library("${ARG_MODULE_NAME}" SHARED ${MODULE_SOURCE_FILES})
endfunction()

function(eightgine_add_executable)
    set(ONE_VALUE_ARGS EXECUTABLE_NAME EXECUTABLE_SOURCES_DIR)
    set(MULTI_VALUE_ARGS EXECUTABLE_SOURCE_FILES)
    cmake_parse_arguments("ARG" "" "${ONE_VALUE_ARGS}" "${MULTI_VALUE_ARGS}" ${ARGN})

    if(ARG_EXECUTABLE_SOURCES_DIR)
        eightgine_file(MODULE_OR_EXECUTABLE_SOURCE_FILES EXECUTABLE_SOURCE_FILES
            MODULE_OR_EXECUTABLE_SOURCES_DIR "${ARG_EXECUTABLE_SOURCES_DIR}"
        )
    endif()

    foreach(EXECUTABLE_SOURCE_FILE IN LISTS ARG_EXECUTABLE_SOURCE_FILES)
        if(EXISTS "${EXECUTABLE_SOURCE_FILE}")
            list(APPEND CLEAR_EXECUTABLE_SOURCE_FILES "${EXECUTABLE_SOURCE_FILE}")
        else()
            message(WARNING "File '${EXECUTABLE_SOURCE_FILE}' in EXECUTABLE_SOURCE_FILES does not exist!")
        endif()
    endforeach()

    add_executable("${ARG_EXECUTABLE_NAME}" ${EXECUTABLE_SOURCE_FILES} ${CLEAR_EXECUTABLE_SOURCE_FILES})

    set_target_properties(${ARG_EXECUTABLE_NAME} PROPERTIES
        DEBUG_POSTFIX "${CMAKE_DEBUG_POSTFIX}"
        RELWITHDEBINFO_POSTFIX "${CMAKE_RELWITHDEBINFO_POSTFIX}"
        WIN32_EXECUTABLE TRUE
    )
endfunction()

function(eightgine_install_dependency)
    set(ONE_VALUE_ARGS MODULE_OR_EXECUTABLE_NAME DEPENDENCY_NAME DEPENDENCY_BIN_DIR)
    cmake_parse_arguments("ARG" "" "${ONE_VALUE_ARGS}" "" ${ARGN})

    set(DEPENDENCY_BIN_SRC "${ARG_DEPENDENCY_BIN_DIR}/${ARG_DEPENDENCY_NAME}.dll")
    set(DEPENDENCY_BIN_DST "$<TARGET_FILE_DIR:${ARG_MODULE_OR_EXECUTABLE_NAME}>/${ARG_DEPENDENCY_NAME}.dll")

    add_custom_command(TARGET "${ARG_MODULE_OR_EXECUTABLE_NAME}"
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${DEPENDENCY_BIN_SRC}" "${DEPENDENCY_BIN_DST}"
    )
endfunction()

function(eightgine_link_dependency)
    set(ONE_VALUE_ARGS MODULE_OR_EXECUTABLE_NAME DEPENDENCY_NAME DEPENDENCY_INCLUDE_DIR DEPENDENCY_LIB_DIR DEPENDENCY_BIN_DIR)
    cmake_parse_arguments("ARG" "" "${ONE_VALUE_ARGS}" "" ${ARGN})

    if(ARG_DEPENDENCY_INCLUDE_DIR)
        target_include_directories("${ARG_MODULE_OR_EXECUTABLE_NAME}" PUBLIC "${ARG_DEPENDENCY_INCLUDE_DIR}")
    endif()

    if(ARG_DEPENDENCY_LIB_DIR)
        target_link_directories("${ARG_MODULE_OR_EXECUTABLE_NAME}" PUBLIC "${ARG_DEPENDENCY_LIB_DIR}")
    endif()

    if(ARG_DEPENDENCY_BIN_DIR)
        eightgine_install_dependency(MODULE_OR_EXECUTABLE_NAME "${ARG_MODULE_OR_EXECUTABLE_NAME}"
            DEPENDENCY_NAME "${ARG_DEPENDENCY_NAME}"
            DEPENDENCY_BIN_DIR "${ARG_DEPENDENCY_BIN_DIR}"
        )
    endif()

    target_link_libraries("${ARG_MODULE_OR_EXECUTABLE_NAME}" PUBLIC "${ARG_DEPENDENCY_NAME}")
endfunction()
