# [[Defaults]]
option(SF_BUILD_SHARED_LIBS "" ${BUILD_SHARED_LIBS})


# [[Subdirectories]]
add_subdirectory("SF" EXCLUDE_FROM_ALL)


# [[Binaries]]
eightgine_add_module(MODULE_NAME "SF"
    MODULE_TYPE INTERFACE
    MODULE_API_DEFINITION OFF
    MODULE_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/SF/include"
)


# [[Dependencies]]
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "SF" DEPENDENCY_NAME "SF")
