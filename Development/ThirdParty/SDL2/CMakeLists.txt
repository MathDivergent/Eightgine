# [[Defaults]]
if(BUILD_SHARED_LIBS)
    option(SDL_STATIC "" OFF)
else()
    option(SDL_STATIC "" ON)
endif()

option(SDL_SHARED "" ${BUILD_SHARED_LIBS})


# [[Subdirectories]]
add_subdirectory("SDL2" EXCLUDE_FROM_ALL)


# [[Binaries]]
eightgine_add_module(MODULE_NAME "SDL2"
    MODULE_TYPE INTERFACE
    MODULE_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/SDL2/include"
    MODULE_DEFINITIONS INTERFACE SDL_MAIN_HANDLED
)


# [[Dependencies]]
if(BUILD_SHARED_LIBS)
    eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "SDL2" DEPENDENCY_NAME "SDL2")
else()
    eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "SDL2" DEPENDENCY_NAME "SDL2-static")
endif()

if(UNIX)
    eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "SDL2" DEPENDENCY_NAME "glibc")
    # eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "SDL2" DEPENDENCY_NAME "X11")
    eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "SDL2" DEPENDENCY_NAME "Wayland")
    # eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "SDL2" DEPENDENCY_NAME "GL")
endif()
