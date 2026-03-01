# [[Defaults]]
option(ZLIB_BUILD_EXAMPLES "" OFF)


# [[Subdirectories]]
add_subdirectory("zlib" EXCLUDE_FROM_ALL)


# [[Binaries]]
eightgine_add_module(MODULE_NAME "zlib"
    MODULE_TYPE INTERFACE
    MODULE_DEFAULT_DEFINITIONS OFF
    MODULE_DEFAULT_OPTIONS OFF
    MODULE_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/zlib"
)


# [[Dependencies]]
if(BUILD_SHARED_LIBS)
    eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "zlib" DEPENDENCY_NAME "zlib")
else()
    eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "zlib" DEPENDENCY_NAME "zlibstatic")
endif()
