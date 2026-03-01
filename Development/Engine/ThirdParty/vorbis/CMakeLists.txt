# [[Defaults]]
option(VORBIS_VORBISENC "" OFF)


# [[Subdirectories]]
add_subdirectory("vorbis" EXCLUDE_FROM_ALL)


# [[Binaries]]
eightgine_add_module(MODULE_NAME "vorbis"
    MODULE_TYPE INTERFACE
    MODULE_DEFAULT_DEFINITIONS OFF
    MODULE_DEFAULT_OPTIONS OFF
    MODULE_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/vorbis/include"
)


# [[Dependencies]]
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "vorbis" DEPENDENCY_NAME "vorbis")
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "vorbis" DEPENDENCY_NAME "vorbisfile")
