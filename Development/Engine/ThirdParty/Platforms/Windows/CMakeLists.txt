# [[Defaults]]
get_filename_component(CXXCOMPILER_BIN_DIR "${CMAKE_CXX_COMPILER}" DIRECTORY)


# [[Binaries]]
eightgine_add_module(MODULE_NAME "PlatformsWindowsExecutable" MODULE_TYPE INTERFACE MODULE_API_DEFINITION OFF)


if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    # [[Binaries]]
    eightgine_add_module(MODULE_NAME "libstdc++-6" MODULE_TYPE INTERFACE MODULE_API_DEFINITION OFF MODULE_BIN_DIR "${CXXCOMPILER_BIN_DIR}")
    eightgine_add_module(MODULE_NAME "libgcc_s_seh-1" MODULE_TYPE INTERFACE MODULE_API_DEFINITION OFF MODULE_BIN_DIR "${CXXCOMPILER_BIN_DIR}")
    eightgine_add_module(MODULE_NAME "libwinpthread-1" MODULE_TYPE INTERFACE MODULE_API_DEFINITION OFF MODULE_BIN_DIR "${CXXCOMPILER_BIN_DIR}")


    # [[Dependencies]]
    eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "PlatformsWindowsExecutable" DEPENDENCY_NAME "libstdc++-6")
    eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "PlatformsWindowsExecutable" DEPENDENCY_NAME "libgcc_s_seh-1")
    eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "PlatformsWindowsExecutable" DEPENDENCY_NAME "libwinpthread-1")


elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    # [[Binaries]]
    eightgine_add_module(MODULE_NAME "libc++" MODULE_TYPE INTERFACE MODULE_API_DEFINITION OFF MODULE_BIN_DIR "${CXXCOMPILER_BIN_DIR}")
    eightgine_add_module(MODULE_NAME "libunwind" MODULE_TYPE INTERFACE MODULE_API_DEFINITION OFF MODULE_BIN_DIR "${CXXCOMPILER_BIN_DIR}")


    # [[Dependencies]]
    eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "PlatformsWindowsExecutable" DEPENDENCY_NAME "libc++")
    eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "PlatformsWindowsExecutable" DEPENDENCY_NAME "libunwind")


else()
    message(WARNING "UNKNOWN COMPILER: ${CMAKE_CXX_COMPILER_ID}")
endif()
