# [[Defaults]]
option(EIGHTEST_BUILD_SHARED_LIBS "" ON)


# [[Subdirectories]]
add_subdirectory("Eightest" EXCLUDE_FROM_ALL)


# [[Binaries]]
eightgine_add_module(MODULE_NAME "Eightest"
    MODULE_TYPE INTERFACE
    MODULE_DEFAULT_DEFINITIONS OFF
    MODULE_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Eightest/include"
)


# [[Dependencies]]
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "Eightest" DEPENDENCY_NAME "Eightest")
