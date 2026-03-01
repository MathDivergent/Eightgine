# [[Subdirectories]]
add_subdirectory("SDL2_net" EXCLUDE_FROM_ALL)

target_compile_options(SDL2_net PRIVATE $<$<CXX_COMPILER_ID:GNU,Clang>:-w>) # disable warnings


# [[Binaries]]
eightgine_add_module(MODULE_NAME "SDL2_net"
    MODULE_TYPE INTERFACE
    MODULE_DEFAULT_DEFINITIONS OFF
    MODULE_DEFAULT_OPTIONS OFF
    MODULE_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/SDL2_net"
)


# [[Dependencies]]
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "SDL2_net" DEPENDENCY_NAME "SDL2_net")
