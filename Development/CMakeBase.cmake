# [[Defaults]]
set(EIGHTGINE_DEFAULT_MODULE_TYPE SHARED)
set(EIGHTGINE_DIRTY_MODULE_OR_EXECUTABLE_NAME_PREFIX "8")

if(WIN32)
    add_compile_definitions("EIGHTGINE_PLATFORM_WINDOWS=1")
    set(EIGHTGINE_BIN_TYPE "dll")
else()
    add_compile_definitions("EIGHTGINE_PLATFORM_WINDOWS=0")
endif()

if(LINUX)
    add_compile_definitions("EIGHTGINE_PLATFORM_LINUX=1")
    set(EIGHTGINE_BIN_TYPE "so")
else()
    add_compile_definitions("EIGHTGINE_PLATFORM_LINUX=0")
endif()

if(APPLE)
    add_compile_definitions("EIGHTGINE_PLATFORM_MACOS=1")
    set(EIGHTGINE_BIN_TYPE "dylib")
else()
    add_compile_definitions("EIGHTGINE_PLATFORM_MACOS=0")
endif()


# [[Macros]]
macro(eightgine_set_module_or_executable MODULE_OR_EXECUTABLE_NAME) # TODO: rewrite as function
    set(DIRTY_${MODULE_OR_EXECUTABLE_NAME} "${EIGHTGINE_DIRTY_MODULE_OR_EXECUTABLE_NAME_PREFIX}${${MODULE_OR_EXECUTABLE_NAME}}")
endmacro()

macro(eightgine_get_module_or_executable MODULE_OR_EXECUTABLE_NAME) # TODO: rewrite as function
    eightgine_set_module_or_executable(${MODULE_OR_EXECUTABLE_NAME})
    if(NOT TARGET "${DIRTY_${MODULE_OR_EXECUTABLE_NAME}}")
        set(DIRTY_${MODULE_OR_EXECUTABLE_NAME} "${${MODULE_OR_EXECUTABLE_NAME}}")
    endif()
endmacro()

macro(eightgine_get_module_or_executable_access MODULE_OR_EXECUTABLE_NAME) # TODO: rewrite as function
    eightgine_get_module_or_executable(${MODULE_OR_EXECUTABLE_NAME})
    get_target_property(MODULE_OR_EXECUTABLE_TYPE "${DIRTY_${MODULE_OR_EXECUTABLE_NAME}}" TYPE)
    if(MODULE_OR_EXECUTABLE_TYPE STREQUAL "LIBRARY_INTERFACE")
        set(${MODULE_OR_EXECUTABLE_NAME}_ACCESS "INTERFACE")
    else()
        set(${MODULE_OR_EXECUTABLE_NAME}_ACCESS "PUBLIC")
    endif()
endmacro()


# [[Functions]]
function(eightgine_install_dependency)
    set(ONE_VALUE_ARGS
        MODULE_OR_EXECUTABLE_NAME
        DEPENDENCY_NAME
        DEPENDENCY_BIN_DIR
    )
    cmake_parse_arguments("ARG" "" "${ONE_VALUE_ARGS}" "" ${ARGN})

    eightgine_get_module_or_executable(ARG_MODULE_OR_EXECUTABLE_NAME)

    add_custom_command(TARGET "${DIRTY_ARG_MODULE_OR_EXECUTABLE_NAME}"
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${ARG_DEPENDENCY_BIN_DIR}/${ARG_DEPENDENCY_NAME}.${EIGHTGINE_BIN_TYPE}"
        "$<TARGET_FILE_DIR:${DIRTY_ARG_MODULE_OR_EXECUTABLE_NAME}>/${ARG_DEPENDENCY_NAME}.${EIGHTGINE_BIN_TYPE}"
    )
endfunction()

function(eightgine_install_libcxx_dependency) # TODO: Rework
    set(ONE_VALUE_ARGS
        MODULE_OR_EXECUTABLE_NAME
    )
    cmake_parse_arguments("ARG" "" "${ONE_VALUE_ARGS}" "" ${ARGN})

    get_filename_component(COMPILER_BIN_DIR "${CMAKE_CXX_COMPILER}" DIRECTORY)

    if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang") # Clang / LLVM
        set(LIBCXX_DLLS "libc++" "libunwind")
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU") # MinGW GCC
        set(LIBCXX_DLLS "libstdc++-6" "libgcc_s_seh-1" "libwinpthread-1")
    else()
        message(WARNING "UNKNOWN COMPILER: ${CMAKE_CXX_COMPILER_ID}")
        return()
    endif()

    if(NOT WIN32) # TODO: temp
        return()
    endif()

    foreach(LIBCXX_NAME ${LIBCXX_DLLS})
        set(DLL_PATH "${COMPILER_BIN_DIR}/${LIBCXX_NAME}.dll")
        if(EXISTS "${DLL_PATH}")
            message(STATUS "FOUND DEPENDENCY DLL: ${DLL_PATH}")
            eightgine_install_dependency(MODULE_OR_EXECUTABLE_NAME "${ARG_MODULE_OR_EXECUTABLE_NAME}"
                DEPENDENCY_NAME "${LIBCXX_NAME}"
                DEPENDENCY_BIN_DIR "${COMPILER_BIN_DIR}"
            )
        else()
            message(WARNING "MISSING DEPENDENCY DLL: ${DLL_PATH}")
        endif()
    endforeach()
endfunction()

function(eightgine_add_symlink)
    set(ONE_VALUE_ARGS
        ORIGINAL
        LINKNAME
    )
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
        execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink "${ORIGINAL_NATIVE}" "${LINKNAME_NATIVE}")
    endif()
endfunction()

function(eightgine_file)
    set(ONE_VALUE_ARGS
        MODULE_OR_EXECUTABLE_SOURCES_DIR
        MODULE_OR_EXECUTABLE_SOURCES_FILES
    )
    cmake_parse_arguments("ARG" "" "${ONE_VALUE_ARGS}" "" ${ARGN})

    file(GLOB_RECURSE SOURCES_FILES
        "${ARG_MODULE_OR_EXECUTABLE_SOURCES_DIR}/*.cpp" "${ARG_MODULE_OR_EXECUTABLE_SOURCES_DIR}/*.hpp"
        "${ARG_MODULE_OR_EXECUTABLE_SOURCES_DIR}/*.c" "${ARG_MODULE_OR_EXECUTABLE_SOURCES_DIR}/*.h"
    )
    set(${ARG_MODULE_OR_EXECUTABLE_SOURCES_FILES} ${SOURCES_FILES} PARENT_SCOPE)

    foreach(SOURCE_FILE IN LISTS SOURCES_FILES)
        get_filename_component(SOURCE_FILE_PATH "${SOURCE_FILE}" PATH)

        file(RELATIVE_PATH GROUP_NAME "${CMAKE_CURRENT_SOURCE_DIR}" "${SOURCE_FILE_PATH}")
        string(REPLACE "/" "\\" GROUP_NAME "${GROUP_NAME}")

        source_group("${GROUP_NAME}" FILES "${SOURCE_FILE}")
    endforeach()
endfunction()

function(eightgine_configure_module_or_executable)
    set(ONE_VALUE_ARGS
        MODULE_OR_EXECUTABLE_NAME
        MODULE_OR_EXECUTABLE_LIB_DIR MODULE_OR_EXECUTABLE_BIN_DIR
    )
    set(MULTI_VALUE_ARGS
        MODULE_OR_EXECUTABLE_INCLUDE_DIR
        MODULE_OR_EXECUTABLE_SOURCES_DIR MODULE_OR_EXECUTABLE_SOURCES_FILES
        MODULE_OR_EXECUTABLE_DEFINITIONS
        MODULE_OR_EXECUTABLE_PROPERTIES
    )
    cmake_parse_arguments("ARG" "" "${ONE_VALUE_ARGS}" "${MULTI_VALUE_ARGS}" ${ARGN})

    eightgine_get_module_or_executable(ARG_MODULE_OR_EXECUTABLE_NAME)
    eightgine_get_module_or_executable_access(ARG_MODULE_OR_EXECUTABLE_NAME)

    if(ARG_MODULE_OR_EXECUTABLE_INCLUDE_DIR)
        target_include_directories("${DIRTY_ARG_MODULE_OR_EXECUTABLE_NAME}" ${ARG_MODULE_OR_EXECUTABLE_NAME_ACCESS} ${ARG_MODULE_OR_EXECUTABLE_INCLUDE_DIR})
    endif()

    if(ARG_MODULE_OR_EXECUTABLE_SOURCES_DIR)
        foreach(SOURCES_DIR IN LISTS ARG_MODULE_OR_EXECUTABLE_SOURCES_DIR)
            eightgine_file(MODULE_OR_EXECUTABLE_SOURCES_FILES SOURCES_FILES MODULE_OR_EXECUTABLE_SOURCES_DIR ${SOURCES_DIR})
            target_sources("${DIRTY_ARG_MODULE_OR_EXECUTABLE_NAME}" ${ARG_MODULE_OR_EXECUTABLE_NAME_ACCESS} ${SOURCES_FILES})
        endforeach()
    endif()

    if(ARG_MODULE_OR_EXECUTABLE_SOURCES_FILES)
        foreach(SOURCE_FILE IN LISTS ARG_MODULE_OR_EXECUTABLE_SOURCES_FILES)
            if(EXISTS "${SOURCE_FILE}")
                list(APPEND SOURCES_FILES "${SOURCE_FILE}")
            else()
                message(WARNING "SOURCE '${SOURCE_FILE}' DOES NOT EXIST")
            endif()
        endforeach()

        target_sources("${DIRTY_ARG_MODULE_OR_EXECUTABLE_NAME}" ${ARG_MODULE_OR_EXECUTABLE_NAME_ACCESS} ${SOURCES_FILES})
    endif()

    if(ARG_MODULE_OR_EXECUTABLE_LIB_DIR)
        target_link_directories("${DIRTY_ARG_MODULE_OR_EXECUTABLE_NAME}" ${ARG_MODULE_OR_EXECUTABLE_NAME_ACCESS} "${ARG_MODULE_OR_EXECUTABLE_LIB_DIR}")
    endif()

    if(ARG_MODULE_OR_EXECUTABLE_BIN_DIR)
         set_target_properties("${DIRTY_ARG_MODULE_OR_EXECUTABLE_NAME}" PROPERTIES MODULE_OR_EXECUTABLE_BIN_DIR "${ARG_MODULE_OR_EXECUTABLE_BIN_DIR}")
    endif()

    if(ARG_MODULE_OR_EXECUTABLE_DEFINITIONS)
        target_compile_definitions("${DIRTY_ARG_MODULE_OR_EXECUTABLE_NAME}" ${ARG_MODULE_OR_EXECUTABLE_DEFINITIONS})
    endif()

    if(ARG_MODULE_OR_EXECUTABLE_PROPERTIES)
        set_target_properties("${DIRTY_ARG_MODULE_OR_EXECUTABLE_NAME}" PROPERTIES ${ARG_MODULE_OR_EXECUTABLE_PROPERTIES})
    endif()
endfunction()

function(eightgine_add_module)
    set(ONE_VALUE_ARGS
        MODULE_NAME
        MODULE_TYPE
        MODULE_LIB_DIR MODULE_BIN_DIR
    )
    set(MULTI_VALUE_ARGS
        MODULE_INCLUDE_DIR
        MODULE_SOURCES_DIR MODULE_SOURCES_FILES
        MODULE_DEFINITIONS
        MODULE_PROPERTIES
    )
    cmake_parse_arguments("ARG" "" "${ONE_VALUE_ARGS}" "${MULTI_VALUE_ARGS}" ${ARGN})

    if(NOT ARG_MODULE_TYPE)
        set(ARG_MODULE_TYPE ${EIGHTGINE_DEFAULT_MODULE_TYPE})
    endif()

    eightgine_get_module_or_executable(ARG_MODULE_NAME)

    add_library("${DIRTY_ARG_MODULE_NAME}" ${ARG_MODULE_TYPE})

    if(WIN32)
        set(MODULE_EXPORT "__declspec(dllexport)")
        set(MODULE_IMPORT "__declspec(dllimport)")
    else()
        set(MODULE_EXPORT "__attribute__((visibility(\"default\")))")
        set(MODULE_IMPORT "")
    endif()

    string(TOUPPER "${ARG_MODULE_NAME}" MODULE_NAME_UPPER)
    set(MODULE_NAME_API "${MODULE_NAME_UPPER}_API")

    if(ARG_MODULE_TYPE STREQUAL "INTERFACE")
        set(MODULE_DEFAULT_DEFINITIONS INTERFACE "${MODULE_NAME_API}=${MODULE_IMPORT}")
        target_link_libraries("${DIRTY_ARG_MODULE_NAME}" INTERFACE "${ARG_MODULE_NAME}")
    elseif(ARG_MODULE_TYPE STREQUAL "SHARED")
        set(MODULE_DEFAULT_DEFINITIONS PRIVATE "${MODULE_NAME_API}=${MODULE_EXPORT}" INTERFACE "${MODULE_NAME_API}=${MODULE_IMPORT}")
    elseif(ARG_MODULE_TYPE STREQUAL "STATIC")
        set(MODULE_DEFAULT_DEFINITIONS PUBLIC "${MODULE_NAME_API}=")
    endif()

    eightgine_configure_module_or_executable(MODULE_OR_EXECUTABLE_NAME "${ARG_MODULE_NAME}"
        MODULE_OR_EXECUTABLE_LIB_DIR "${ARG_MODULE_LIB_DIR}" MODULE_OR_EXECUTABLE_BIN_DIR "${ARG_MODULE_BIN_DIR}"
        MODULE_OR_EXECUTABLE_INCLUDE_DIR ${ARG_MODULE_INCLUDE_DIR}
        MODULE_OR_EXECUTABLE_SOURCES_DIR ${ARG_MODULE_SOURCES_DIR} MODULE_OR_EXECUTABLE_SOURCES_FILES ${ARG_MODULE_SOURCES_FILES}
        MODULE_OR_EXECUTABLE_DEFINITIONS
            ${MODULE_DEFAULT_DEFINITIONS}
            ${ARG_MODULE_DEFINITIONS}
        MODULE_OR_EXECUTABLE_PROPERTIES
            OUTPUT_NAME "${ARG_MODULE_NAME}"
            ${ARG_MODULE_PROPERTIES}
    )
endfunction()

function(eightgine_add_executable)
    set(ONE_VALUE_ARGS
        EXECUTABLE_NAME
    )
    set(MULTI_VALUE_ARGS
        EXECUTABLE_INCLUDE_DIR
        EXECUTABLE_SOURCES_DIR EXECUTABLE_SOURCES_FILES
        EXECUTABLE_DEFINITIONS
        EXECUTABLE_PROPERTIES
    )
    cmake_parse_arguments("ARG" "" "${ONE_VALUE_ARGS}" "${MULTI_VALUE_ARGS}" ${ARGN})

    eightgine_set_module_or_executable(ARG_EXECUTABLE_NAME)

    add_executable("${DIRTY_ARG_EXECUTABLE_NAME}")

    if(WIN32)
        set(DEFAULT_EXECUTABLE_PROPERTIES WIN32_EXECUTABLE TRUE)
    elseif(APPLE)
        set(DEFAULT_EXECUTABLE_PROPERTIES MACOSX_BUNDLE TRUE)
    endif()

    eightgine_configure_module_or_executable(MODULE_OR_EXECUTABLE_NAME "${ARG_EXECUTABLE_NAME}"
        MODULE_OR_EXECUTABLE_INCLUDE_DIR ${ARG_EXECUTABLE_INCLUDE_DIR}
        MODULE_OR_EXECUTABLE_SOURCES_DIR ${ARG_EXECUTABLE_SOURCES_DIR} MODULE_OR_EXECUTABLE_SOURCES_FILES ${ARG_EXECUTABLE_SOURCES_FILES}
        MODULE_OR_EXECUTABLE_DEFINITIONS ${ARG_EXECUTABLE_DEFINITIONS}
        MODULE_OR_EXECUTABLE_PROPERTIES
            OUTPUT_NAME "${ARG_EXECUTABLE_NAME}"
            DEBUG_POSTFIX "${CMAKE_DEBUG_POSTFIX}"
            RELWITHDEBINFO_POSTFIX "${CMAKE_RELWITHDEBINFO_POSTFIX}"
            ${DEFAULT_EXECUTABLE_PROPERTIES}
            ${ARG_EXECUTABLE_PROPERTIES}
    )
endfunction()

function(eightgine_add_thirdparty)
    set(ONE_VALUE_ARGS
        THIRDPARTY_NAME
        THIRDPARTY_DIR
    )
    cmake_parse_arguments("ARG" "" "${ONE_VALUE_ARGS}" "" ${ARGN})

    get_filename_component(THIRDPARTY_DIR_NAME "${ARG_THIRDPARTY_DIR}" NAME)

    add_subdirectory("${ARG_THIRDPARTY_DIR}/${ARG_THIRDPARTY_NAME}"
        "${CMAKE_BINARY_DIR}/${THIRDPARTY_DIR_NAME}/${ARG_THIRDPARTY_NAME}"
        EXCLUDE_FROM_ALL
    )
endfunction()

function(eightgine_link_dependency)
    set(ONE_VALUE_ARGS
        MODULE_OR_EXECUTABLE_NAME
        DEPENDENCY_NAME
        DEPENDENCY_LIB_DIR DEPENDENCY_BIN_DIR
    )
    set(MULTI_VALUE_ARGS
        DEPENDENCY_INCLUDE_DIR
    )
    cmake_parse_arguments("ARG" "" "${ONE_VALUE_ARGS}" "${MULTI_VALUE_ARGS}" ${ARGN})

    eightgine_get_module_or_executable(ARG_MODULE_OR_EXECUTABLE_NAME)
    eightgine_get_module_or_executable_access(ARG_MODULE_OR_EXECUTABLE_NAME)
    eightgine_get_module_or_executable(ARG_DEPENDENCY_NAME)

    target_link_libraries("${DIRTY_ARG_MODULE_OR_EXECUTABLE_NAME}" ${ARG_MODULE_OR_EXECUTABLE_NAME_ACCESS} "${DIRTY_ARG_DEPENDENCY_NAME}")

    if(NOT ARG_DEPENDENCY_BIN_DIR AND TARGET "${DIRTY_ARG_DEPENDENCY_NAME}")
        get_target_property(ARG_DEPENDENCY_BIN_DIR "${DIRTY_ARG_DEPENDENCY_NAME}" MODULE_OR_EXECUTABLE_BIN_DIR)
    endif()

    eightgine_configure_module_or_executable(MODULE_OR_EXECUTABLE_NAME "${ARG_MODULE_OR_EXECUTABLE_NAME}"
        MODULE_OR_EXECUTABLE_LIB_DIR "${ARG_DEPENDENCY_LIB_DIR}" MODULE_OR_EXECUTABLE_BIN_DIR "${ARG_DEPENDENCY_BIN_DIR}"
        MODULE_OR_EXECUTABLE_INCLUDE_DIR ${ARG_DEPENDENCY_INCLUDE_DIR}
    )

    if(ARG_DEPENDENCY_BIN_DIR)
        eightgine_install_dependency(MODULE_OR_EXECUTABLE_NAME "${ARG_MODULE_OR_EXECUTABLE_NAME}"
            DEPENDENCY_NAME "${ARG_DEPENDENCY_NAME}"
            DEPENDENCY_BIN_DIR "${ARG_DEPENDENCY_BIN_DIR}"
        )
    endif()
endfunction()
