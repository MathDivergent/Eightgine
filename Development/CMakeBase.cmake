function(eightgine_file)
    set(ARGS MODULE_OR_EXECUTABLE_SOURCE_FILES MODULE_OR_EXECUTABLE_SOURCES_DIR)
    cmake_parse_arguments("ARG" "" "${ARGS}" "" ${ARGN})

    file(GLOB_RECURSE ${ARG_MODULE_OR_EXECUTABLE_SOURCE_FILES}
        "${ARG_MODULE_OR_EXECUTABLE_SOURCES_DIR}/*.cpp"
        "${ARG_MODULE_OR_EXECUTABLE_SOURCES_DIR}/*.hpp" "${ARG_MODULE_OR_EXECUTABLE_SOURCES_DIR}/*.h"
    )
endfunction()

function(eightgine_add_module)
    set(ARGS MODULE_NAME MODULE_SOURCES_DIR)
    cmake_parse_arguments("ARG" "" "${ARGS}" "" ${ARGN})

    file(GLOB_RECURSE MODULE_SOURCE_FILES
        "${ARG_MODULE_SOURCES_DIR}/*.cpp" "${ARG_MODULE_SOURCES_DIR}/*.hpp" "${ARG_MODULE_SOURCES_DIR}/*.h"
    )
    add_library("${ARG_MODULE_NAME}" SHARED ${MODULE_SOURCE_FILES})
endfunction()

function(test_function)
    cmake_parse_arguments(ARG "" "LIST_NAME" "MY_LIST" ${ARGN})

    message(WARNING "LIST_NAME: ${ARG_LIST_NAME}")
    message(WARNING "MY_LIST: ${ARG_MY_LIST}")
endfunction()

function(eightgine_add_executable)
    set(ARGS EXECUTABLE_NAME EXECUTABLE_SOURCES_DIR)
    set(MULTI_ARGS EXECUTABLE_SOURCE_FILES)
    cmake_parse_arguments("ARG" "" "${ARGS}" "${MULTI_ARGS}" ${ARGN})

    if(ARG_EXECUTABLE_SOURCES_DIR)
        file(GLOB_RECURSE EXECUTABLE_SOURCE_FILES
            "${ARG_EXECUTABLE_SOURCES_DIR}/*.cpp" "${ARG_EXECUTABLE_SOURCES_DIR}/*.hpp" "${ARG_EXECUTABLE_SOURCES_DIR}/*.h"
        )
    endif()

    set(CLEAR_EXECUTABLE_SOURCE_FILES)
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
    set(ARGS MODULE_OR_EXECUTABLE_NAME DEPENDENCY_NAME DEPENDENCY_BIN_DIR)
    cmake_parse_arguments("ARG" "" "${ARGS}" "" ${ARGN})

    set(DEPENDENCY_BIN_SRC "${ARG_DEPENDENCY_BIN_DIR}/${ARG_DEPENDENCY_NAME}.dll")
    set(DEPENDENCY_BIN_DST "$<TARGET_FILE_DIR:${ARG_MODULE_OR_EXECUTABLE_NAME}>/${ARG_DEPENDENCY_NAME}.dll")

    add_custom_command(TARGET "${ARG_MODULE_OR_EXECUTABLE_NAME}"
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${DEPENDENCY_BIN_SRC}" "${DEPENDENCY_BIN_DST}"
    )
endfunction()

function(eightgine_link_dependency)
    set(ARGS MODULE_OR_EXECUTABLE_NAME DEPENDENCY_NAME DEPENDENCY_INCLUDE_DIR DEPENDENCY_LIB_DIR DEPENDENCY_BIN_DIR)
    cmake_parse_arguments("ARG" "" "${ARGS}" "" ${ARGN})

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
