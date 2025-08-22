# [[Root]]
cmake_minimum_required(VERSION 3.16)
project(EmptyProject)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_SHARED_LIBRARY_PREFIX "")
set(CMAKE_DEBUG_POSTFIX "-Debug")
set(CMAKE_RELWITHDEBINFO_POSTFIX "-RelWithDebInfo")
set(CMAKE_MINSIZEREL_POSTFIX "-MinSizeRel")


# [[Options]]
option(EIGHTGINE_WITH_EDITOR "Build with the Eightgine Editor" ON)
option(EIGHTGINE_WITH_CONSOLE "Build with the Eightgine Console" OFF)
option(EIGHTGINE_OVERRIDE_PLATFORM "Build with the Eightgine custom Platform" OFF)
option(BUILD_SHARED_LIBS "Build shared libraies by Default" ON)


# [[Includes]]
include("${CMAKE_SOURCE_DIR}/CMakeBase.cmake")


# [[Defaults]]
set(ENGINE_DIR_NAME "Engine") # readonly
set(GAME_DIR_NAME "Game")

set(PROJECT_DIR_NAME "${PROJECT_NAME}")
set(RESOURCES_DIR_NAME "Resources")
set(PLUGINS_DIR_NAME "PlugIns")

set(DEVELOPMENT_DIR_NAME "Development") # readonly

if(DEFINED ENV{Eightgine})
    set(EIGHTGINE_DIR "$ENV{Eightgine}") # readonly
    string(REPLACE "\\" "/" EIGHTGINE_DIR ${EIGHTGINE_DIR})
else()
    message(FATAL_ERROR "MISSING ENV: Eightgine")
endif()

set(PROJECT_DIR "${CMAKE_SOURCE_DIR}") # readonly
set(PROJECT_DEVELOPMENT_ENGINE_DIR "${PROJECT_DIR}/${DEVELOPMENT_DIR_NAME}/${ENGINE_DIR_NAME}") # readonly
set(PROJECT_DEVELOPMENT_GAME_DIR "${PROJECT_DIR}/${DEVELOPMENT_DIR_NAME}/${GAME_DIR_NAME}") # readonly
set(PROJECT_PLUGINS_DIR "${PROJECT_DIR}/${PLUGINS_DIR_NAME}") # readonly
set(PROJECT_RESOURCES_DIR "${PROJECT_DIR}/${RESOURCES_DIR_NAME}") # readonly

if(EIGHTGINE_PLATFORM_WINDOWS)
    set(PROJECT_RUNTIME_DIR "${PROJECT_DIR}/Windows") # readonly
    set(PROJECT_LIBRARY_DIR "${PROJECT_DIR}/Windows") # readonly
elseif(EIGHTGINE_PLATFORM_LINUX)
    set(PROJECT_RUNTIME_DIR "${PROJECT_DIR}/Linux") # readonly
    set(PROJECT_LIBRARY_DIR "${PROJECT_DIR}/Linux") # readonly
elseif(EIGHTGINE_PLATFORM_MACOS)
    set(PROJECT_RUNTIME_DIR "${PROJECT_DIR}/macOS") # readonly
    set(PROJECT_LIBRARY_DIR "${PROJECT_DIR}/Frameworks") # readonly
endif()


# [[CMakeDefaults]]
foreach(BUILD_TYPE_POSTFIX IN LISTS EIGHTGINE_BUILD_TYPE_POSTFIXES)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY${BUILD_TYPE_POSTFIX} "${PROJECT_RUNTIME_DIR}") # readonly
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY${BUILD_TYPE_POSTFIX} "${PROJECT_LIBRARY_DIR}") # readonly
endforeach()

set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE) # readonly
set(CMAKE_INSTALL_RPATH "${EIGHTGINE_RPATH}") # readonly
if(EIGHTGINE_PLATFORM_MACOS)
    set(CMAKE_INSTALL_NAME_DIR "@rpath") # readonly
endif()


# [[Definitions]]
if(EIGHTGINE_WITH_EDITOR)
    add_compile_definitions("EIGHTGINE_WITH_EDITOR=1")
else()
    add_compile_definitions("EIGHTGINE_WITH_EDITOR=0")
endif()

if(EIGHTGINE_WITH_CONSOLE)
    add_compile_definitions("EIGHTGINE_WITH_CONSOLE=1")
else()
    add_compile_definitions("EIGHTGINE_WITH_CONSOLE=0")
endif()

add_compile_definitions("EIGHTGINE_RESOURCES_DIR_NAME=\"${RESOURCES_DIR_NAME}\"")
add_compile_definitions("EIGHTGINE_PLUGINS_DIR_NAME=\"${PLUGINS_DIR_NAME}\"")
add_compile_definitions("EIGHTGINE_BUILD_POSTFIX=\"${EIGHTGINE_BIULD_POSTFIX}\"")


# [[Subdirectories]]
eightgine_add_symlink(ORIGINAL_NAME "${EIGHTGINE_DIR}/${DEVELOPMENT_DIR_NAME}/${ENGINE_DIR_NAME}" LINK_NAME "${PROJECT_DEVELOPMENT_ENGINE_DIR}")
add_subdirectory("${PROJECT_DEVELOPMENT_ENGINE_DIR}" "${CMAKE_BINARY_DIR}/${ENGINE_DIR_NAME}")

add_subdirectory("${PROJECT_DEVELOPMENT_GAME_DIR}")


# [[Binaries]]
set(PROJECT_JAUNCHER_CPP "${CMAKE_BINARY_DIR}/Launcher.cpp")
file(WRITE "${PROJECT_JAUNCHER_CPP}" "#include <CLauncherImpl.hpp>")

eightgine_add_executable(EXECUTABLE_NAME "${PROJECT_NAME}" EXECUTABLE_SOURCES_FILES "${PROJECT_JAUNCHER_CPP}")


# [[Dependencies]]
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "${PROJECT_NAME}" DEPENDENCY_NAME "EightgineCore")

if(EIGHTGINE_PLATFORM_WINDOWS)
    eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "${PROJECT_NAME}" DEPENDENCY_NAME "PlatformsWindowsExecutable")
endif()
