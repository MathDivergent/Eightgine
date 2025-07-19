# [[Defaults]]
option(EIGHTSER_BUILD_SHARED_LIBS "" ${BUILD_SHARED_LIBS})


# [[Subdirectories]]
add_subdirectory("Eightser" EXCLUDE_FROM_ALL)


# [[Binaries]]
eightgine_add_module(MODULE_NAME "Eightser"
    MODULE_TYPE INTERFACE
    MODULE_API_DEFINITION OFF
    MODULE_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/Eightser/include"
)


# [[Dependencies]]
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "Eightser" DEPENDENCY_NAME "Eightser")
