# [[Defaults]]
option(REW_BUILD_SHARED_LIBS "" ON)


# [[Subdirectories]]
add_subdirectory("Rew" EXCLUDE_FROM_ALL)


# [[Binaries]]
eightgine_add_module(MODULE_NAME "Rew"
    MODULE_TYPE INTERFACE
    MODULE_API_DEFINITION OFF
    MODULE_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/Rew/include"
)


# [[Dependencies]]
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "Rew" DEPENDENCY_NAME "Rew")
