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
    MODULE_API_DEFINITION OFF
    MODULE_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/SDL2/include"
    MODULE_DEFINITIONS INTERFACE SDL_MAIN_HANDLED
)


# [[Dependencies]]
if(BUILD_SHARED_LIBS)
    eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "SDL2" DEPENDENCY_NAME "SDL2")
else()
    eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "SDL2" DEPENDENCY_NAME "SDL2-static")
endif()

if(EIGHTGINE_PLATFORM_LINUX)
    eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "SDL2" DEPENDENCY_NAME "PlatformsLinuxMinimal")
    eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "SDL2" DEPENDENCY_NAME "PlatformsLinuxGraphics")
elseif(EIGHTGINE_PLATFORM_MACOS)
    eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "SDL2" DEPENDENCY_NAME "PlatformsMacOSMinimal")
    eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "SDL2" DEPENDENCY_NAME "PlatformsMacOSGraphics")
endif()
