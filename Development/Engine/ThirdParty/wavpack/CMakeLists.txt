# [[Subdirectories]]
add_subdirectory("wavpack" EXCLUDE_FROM_ALL)


# [[Binaries]]
eightgine_add_module(MODULE_NAME "wavpack"
    MODULE_TYPE INTERFACE
    MODULE_DEFAULT_DEFINITIONS OFF
    MODULE_DEFAULT_OPTIONS OFF
    MODULE_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/wavpack/include"
)


# [[Dependencies]]
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "wavpack" DEPENDENCY_NAME "wavpack")
