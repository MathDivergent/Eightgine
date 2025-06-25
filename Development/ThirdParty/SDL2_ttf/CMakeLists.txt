# [[Subdirectories]]
add_subdirectory("SDL2_ttf" EXCLUDE_FROM_ALL)


# [[Binaries]]
eightgine_add_module(MODULE_NAME "SDL2_ttf"
    MODULE_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/SDL2_ttf/include"
    MODULE_TYPE INTERFACE
)

# [[Dependencies]]
eightgine_link_dependency(MODULE_OR_EXECUTABLE_NAME "SDL2_ttf" DEPENDENCY_NAME "SDL2_ttf-static")