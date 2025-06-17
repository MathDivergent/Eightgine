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
            COMMAND cmd /c mklink /J "${LINKNAME_NATIVE}" "${ORIGINAL_NATIVE}" # TODO: Check
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
        "${ARG_MODULE_OR_EXECUTABLE_SOURCES_DIR}/*.cpp" "${ARG_MODULE_OR_EXECUTABLE_SOURCES_DIR}/*.c"
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
    set(MULTI_VALUE_ARGS MODULE_INCLUDE_DIR MODULE_PRIVATE_DEFINITIONS MODULE_INTERFACE_DEFINITIONS)
    cmake_parse_arguments("ARG" "" "${ONE_VALUE_ARGS}" "${MULTI_VALUE_ARGS}" ${ARGN})

    eightgine_file(MODULE_OR_EXECUTABLE_SOURCE_FILES MODULE_SOURCE_FILES
        MODULE_OR_EXECUTABLE_SOURCES_DIR "${ARG_MODULE_SOURCES_DIR}"
    )

    add_library("${ARG_MODULE_NAME}" SHARED ${MODULE_SOURCE_FILES})

    if(ARG_MODULE_INCLUDE_DIR)
        target_include_directories("${ARG_MODULE_NAME}" PUBLIC ${ARG_MODULE_INCLUDE_DIR})
    endif()

    if(WIN32)
        set(SHARED_EXPORT "__declspec(dllexport)")
        set(SHARED_IMPORT "__declspec(dllimport)")
    else()
        set(SHARED_EXPORT "__attribute__((visibility(\"default\")))")
        set(SHARED_IMPORT "")
    endif()

    string(TOUPPER "${ARG_MODULE_NAME}" MODULE_NAME_UPPER)
    list(APPEND MODULE_PRIVATE_DEFINITIONS "${MODULE_NAME_UPPER}_API=${SHARED_EXPORT}")
    list(APPEND MODULE_INTERFACE_DEFINITIONS "${MODULE_NAME_UPPER}_API=${SHARED_IMPORT}")

    if(ARG_MODULE_PRIVATE_DEFINITIONS)
        list(APPEND MODULE_PRIVATE_DEFINITIONS ${ARG_MODULE_PRIVATE_DEFINITIONS})
    endif()

    if(ARG_MODULE_INTERFACE_DEFINITIONS)
        list(APPEND MODULE_INTERFACE_DEFINITIONS ${ARG_MODULE_INTERFACE_DEFINITIONS})
    endif()

    target_compile_definitions("${ARG_MODULE_NAME}"
        PRIVATE ${MODULE_PRIVATE_DEFINITIONS} INTERFACE ${MODULE_INTERFACE_DEFINITIONS}
    )
endfunction()

function(eightgine_add_executable)
    set(ONE_VALUE_ARGS EXECUTABLE_NAME EXECUTABLE_SOURCES_DIR)
    set(MULTI_VALUE_ARGS EXECUTABLE_INCLUDE_DIR EXECUTABLE_SOURCE_FILES)
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

    if(ARG_EXECUTABLE_INCLUDE_DIR)
        target_include_directories("${ARG_EXECUTABLE_NAME}" PUBLIC ${ARG_EXECUTABLE_INCLUDE_DIR})
    endif()

    set_target_properties(${ARG_EXECUTABLE_NAME} PROPERTIES
        DEBUG_POSTFIX "${CMAKE_DEBUG_POSTFIX}"
        RELWITHDEBINFO_POSTFIX "${CMAKE_RELWITHDEBINFO_POSTFIX}"
        WIN32_EXECUTABLE TRUE # TODO: Temp
    )
endfunction()

function(eightgine_install_dependency)
    set(ONE_VALUE_ARGS MODULE_OR_EXECUTABLE_NAME DEPENDENCY_NAME DEPENDENCY_BIN_DIR)
    cmake_parse_arguments("ARG" "" "${ONE_VALUE_ARGS}" "" ${ARGN})

    set(DEPENDENCY_BIN_SRC "${ARG_DEPENDENCY_BIN_DIR}/${ARG_DEPENDENCY_NAME}.dll") # TODO: Temp
    set(DEPENDENCY_BIN_DST "$<TARGET_FILE_DIR:${ARG_MODULE_OR_EXECUTABLE_NAME}>/${ARG_DEPENDENCY_NAME}.dll") # TODO: Temp

    add_custom_command(TARGET "${ARG_MODULE_OR_EXECUTABLE_NAME}"
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${DEPENDENCY_BIN_SRC}" "${DEPENDENCY_BIN_DST}" # TODO: Check
    )
endfunction()

function(eightgine_install_libcxx_dependency) # TODO: Rework
    set(ONE_VALUE_ARGS MODULE_OR_EXECUTABLE_NAME)
    cmake_parse_arguments("ARG" "" "${ONE_VALUE_ARGS}" "" ${ARGN})

    get_filename_component(COMPILER_BIN_DIR "${CMAKE_CXX_COMPILER}" DIRECTORY)

    if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang") # Clang / LLVM
        set(LIBCXX_DLLS "libc++" "libunwind")
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU") # MinGW GCC
        set(LIBCXX_DLLS "libstdc++-6" "libgcc_s_seh-1" "libwinpthread-1")
    else()
        message(WARNING "Unknown compiler: ${CMAKE_CXX_COMPILER_ID}")
        return()
    endif()

    foreach(LIBCXX_NAME ${LIBCXX_DLLS})
        set(DLL_PATH "${COMPILER_BIN_DIR}/${LIBCXX_NAME}.dll")
        if(EXISTS "${DLL_PATH}")
            message(STATUS "Found dependency DLL: ${DLL_PATH}")
            eightgine_install_dependency(MODULE_OR_EXECUTABLE_NAME "${ARG_MODULE_OR_EXECUTABLE_NAME}"
                DEPENDENCY_NAME "${LIBCXX_NAME}"
                DEPENDENCY_BIN_DIR "${COMPILER_BIN_DIR}"
            )
        else()
            message(WARNING "Missing dependency DLL: ${DLL_PATH}")
        endif()
    endforeach()
endfunction()

function(eightgine_link_dependency)
    set(ONE_VALUE_ARGS MODULE_OR_EXECUTABLE_NAME DEPENDENCY_NAME DEPENDENCY_LIB_DIR DEPENDENCY_BIN_DIR)
    set(MULTI_VALUE_ARGS DEPENDENCY_INCLUDE_DIR DEPENDENCY_PRIVATE_DEFINITIONS DEPENDENCY_INTERFACE_DEFINITIONS)
    cmake_parse_arguments("ARG" "" "${ONE_VALUE_ARGS}" "${MULTI_VALUE_ARGS}" ${ARGN})

    if(ARG_DEPENDENCY_INCLUDE_DIR)
        target_include_directories("${ARG_MODULE_OR_EXECUTABLE_NAME}" PUBLIC ${ARG_DEPENDENCY_INCLUDE_DIR})
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

    if(ARG_DEPENDENCY_PRIVATE_DEFINITIONS)
        target_compile_definitions("${ARG_MODULE_OR_EXECUTABLE_NAME}" PRIVATE ${ARG_DEPENDENCY_PRIVATE_DEFINITIONS})
    endif()

    if(ARG_DEPENDENCY_INTERFACE_DEFINITIONS)
        target_compile_definitions("${ARG_MODULE_OR_EXECUTABLE_NAME}" INTERFACE ${ARG_DEPENDENCY_INTERFACE_DEFINITIONS})
    endif()
endfunction()
