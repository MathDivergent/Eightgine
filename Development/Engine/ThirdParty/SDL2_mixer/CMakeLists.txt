# [[Defaults]]
option(SDL2MIXER_DEPS_SHARED "" ${BUILD_SHARED_LIBS})
option(SDL2MIXER_VENDORED "" OFF)

option(SDL2MIXER_FLAC "" OFF)
option(SDL2MIXER_GME "" OFF)
option(SDL2MIXER_MOD "" OFF)
option(SDL2MIXER_MP3 "" ON)
option(SDL2MIXER_MIDI "" OFF)
option(SDL2MIXER_OPUS "" ON)

set(SDL2MIXER_VORBIS "VORBISFILE" CACHE STRING "")

option(SDL2MIXER_WAVE "" ON)
option(SDL2MIXER_WAVPACK "" ON)


# [[Subdirectories]]
add_subdirectory("SDL2_mixer" EXCLUDE_FROM_ALL)

target_compile_definitions(SDL2_mixer PRIVATE "WAVPACK_HEADER=\"wavpack.h\"")
target_compile_definitions(SDL2_mixer PRIVATE "OPUSFILE_HEADER=\"opusfile.h\"")


# [[Binaries]]
eightgine_add_module(MODULE_NAME "SDL2_mixer"
    MODULE_TYPE INTERFACE
    MODULE_API_DEFINITION OFF
    MODULE_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/SDL2_mixer/include"
)


# [[Dependencies]]
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "SDL2_mixer" DEPENDENCY_NAME "SDL2_mixer")

if(SDL2MIXER_OPUS)
    eightgine_add_dependency(DEPENDENCY_NAME "opusfile")
endif()

if(SDL2MIXER_WAVPACK)
    eightgine_add_dependency(DEPENDENCY_NAME "wavpack")
endif()

if(SDL2MIXER_VORBIS STREQUAL "VORBISFILE")
    eightgine_add_dependency(DEPENDENCY_NAME "ogg")
    eightgine_add_dependency(DEPENDENCY_NAME "vorbis")
endif()

if(EIGHTGINE_PLATFORM_LINUX)
    eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "SDL2_mixer" DEPENDENCY_NAME "PlatformsLinuxAudio")
elseif(EIGHTGINE_PLATFORM_MACOS)
    eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "SDL2_mixer" DEPENDENCY_NAME "PlatformsMacOSAudio")
endif()
