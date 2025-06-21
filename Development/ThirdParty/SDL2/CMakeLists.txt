# [[Subdirectories]]
add_subdirectory(SDL2 EXCLUDE_FROM_ALL)


# [[Binaries]]
eightgine_add_module(MODULE_NAME "SDL2"
    MODULE_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/include" "${CMAKE_CURRENT_LIST_DIR}/include/SDL2"
    MODULE_TYPE INTERFACE
    MODULE_DEFINITIONS INTERFACE SDL_MAIN_HANDLED
)

# [[Dependencies]]
if(UNIX)
    eightgine_link_dependency(MODULE_OR_EXECUTABLE_NAME "SDL2" DEPENDENCY_NAME "pthread")
    eightgine_link_dependency(MODULE_OR_EXECUTABLE_NAME "SDL2" DEPENDENCY_NAME "dl")
    eightgine_link_dependency(MODULE_OR_EXECUTABLE_NAME "SDL2" DEPENDENCY_NAME "m")

    eightgine_link_dependency(MODULE_OR_EXECUTABLE_NAME "SDL2" DEPENDENCY_NAME "X11")
    eightgine_link_dependency(MODULE_OR_EXECUTABLE_NAME "SDL2" DEPENDENCY_NAME "Xext")
    eightgine_link_dependency(MODULE_OR_EXECUTABLE_NAME "SDL2" DEPENDENCY_NAME "Xrandr")
    eightgine_link_dependency(MODULE_OR_EXECUTABLE_NAME "SDL2" DEPENDENCY_NAME "Xcursor")
    eightgine_link_dependency(MODULE_OR_EXECUTABLE_NAME "SDL2" DEPENDENCY_NAME "Xi")

    eightgine_link_dependency(MODULE_OR_EXECUTABLE_NAME "SDL2" DEPENDENCY_NAME "wayland-client")
    eightgine_link_dependency(MODULE_OR_EXECUTABLE_NAME "SDL2" DEPENDENCY_NAME "wayland-cursor")
    eightgine_link_dependency(MODULE_OR_EXECUTABLE_NAME "SDL2" DEPENDENCY_NAME "wayland-egl")

    eightgine_link_dependency(MODULE_OR_EXECUTABLE_NAME "SDL2" DEPENDENCY_NAME "GL")
endif()
