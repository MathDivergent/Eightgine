# [[Subdirectories]]
add_subdirectory(SDL2_mixer EXCLUDE_FROM_ALL)


# [[Binaries]]
eightgine_add_module(MODULE_NAME "SDL2_mixer"
    MODULE_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/SDL2_mixer/include"
    MODULE_TYPE INTERFACE
)

# [[Dependencies]]
eightgine_link_dependency(MODULE_OR_EXECUTABLE_NAME "SDL2_mixer" DEPENDENCY_NAME "SDL2_mixer-static")