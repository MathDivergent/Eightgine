# [[Defaults]]
option(EIGHTREFL_BUILD_SHARED_LIBS "" ON)


# [[Subdirectories]]
add_subdirectory("Eightrefl" EXCLUDE_FROM_ALL)


# [[Binaries]]
eightgine_add_module(MODULE_NAME "Eightrefl"
    MODULE_TYPE INTERFACE
    MODULE_API_DEFINITION OFF
    MODULE_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/Eightrefl/include"
)


# [[Dependencies]]
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "Eightrefl" DEPENDENCY_NAME "Eightrefl")
