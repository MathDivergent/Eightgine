# [[Subdirectories]]
if(EIGHTGINE_PLATFORM_WINDOWS)
    add_subdirectory("Platforms/Windows" EXCLUDE_FROM_ALL)
elseif(EIGHTGINE_PLATFORM_LINUX)
    add_subdirectory("Platforms/Linux" EXCLUDE_FROM_ALL)
else(EIGHTGINE_PLATFORM_MACOS)
    add_subdirectory("Platforms/macOS" EXCLUDE_FROM_ALL)
endif()

add_subdirectory("cJSON" EXCLUDE_FROM_ALL)
add_subdirectory("lua" EXCLUDE_FROM_ALL)

add_subdirectory("Ogg" EXCLUDE_FROM_ALL)
add_subdirectory("Vorbis" EXCLUDE_FROM_ALL)
add_subdirectory("Opus" EXCLUDE_FROM_ALL)
add_subdirectory("OpusFile" EXCLUDE_FROM_ALL)
add_subdirectory("WavPack" EXCLUDE_FROM_ALL)
add_subdirectory("Freetype" EXCLUDE_FROM_ALL)
add_subdirectory("BoringSSL" EXCLUDE_FROM_ALL)

add_subdirectory("SDL2" EXCLUDE_FROM_ALL)
add_subdirectory("SDL2_image" EXCLUDE_FROM_ALL)
add_subdirectory("SDL2_mixer" EXCLUDE_FROM_ALL)
add_subdirectory("SDL2_ttf" EXCLUDE_FROM_ALL)
add_subdirectory("SDL2_net" EXCLUDE_FROM_ALL)

add_subdirectory("Box2D" EXCLUDE_FROM_ALL)

add_subdirectory("Rew" EXCLUDE_FROM_ALL)
add_subdirectory("SF" EXCLUDE_FROM_ALL)

if(EIGHTGINE_DEBUG)
    add_subdirectory("Eightest" EXCLUDE_FROM_ALL)
endif()
