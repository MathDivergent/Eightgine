# [[Subdirectories]]
add_subdirectory("SDL2_net" EXCLUDE_FROM_ALL)


# [[Binaries]]
eightgine_add_module(MODULE_NAME "SDL2_net"
    MODULE_TYPE INTERFACE
    MODULE_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/SDL2_net/include"
)


# [[Dependencies]]
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "SDL2_net" DEPENDENCY_NAME "SDL2_net")
