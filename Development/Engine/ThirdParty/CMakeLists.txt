# [[Subdirectories]]
if(EIGHTGINE_PLATFORM_WINDOWS)
    add_subdirectory("Platforms/Windows" EXCLUDE_FROM_ALL)
elseif(EIGHTGINE_PLATFORM_LINUX)
    add_subdirectory("Platforms/Linux" EXCLUDE_FROM_ALL)
elseif(EIGHTGINE_PLATFORM_MACOS)
    add_subdirectory("Platforms/macOS" EXCLUDE_FROM_ALL)
endif()

add_subdirectory("cJSON" EXCLUDE_FROM_ALL)
add_subdirectory("lua" EXCLUDE_FROM_ALL)
add_subdirectory("iniparser" EXCLUDE_FROM_ALL)

add_subdirectory("ogg" EXCLUDE_FROM_ALL)
add_subdirectory("vorbis" EXCLUDE_FROM_ALL)
add_subdirectory("opus" EXCLUDE_FROM_ALL)
add_subdirectory("opusfile" EXCLUDE_FROM_ALL)
add_subdirectory("wavpack" EXCLUDE_FROM_ALL)
add_subdirectory("freetype" EXCLUDE_FROM_ALL)

add_subdirectory("SDL2" EXCLUDE_FROM_ALL)
add_subdirectory("SDL2_image" EXCLUDE_FROM_ALL)
add_subdirectory("SDL2_mixer" EXCLUDE_FROM_ALL)
add_subdirectory("SDL2_ttf" EXCLUDE_FROM_ALL)
add_subdirectory("SDL2_net" EXCLUDE_FROM_ALL)

add_subdirectory("box2d" EXCLUDE_FROM_ALL)
add_subdirectory("entt" EXCLUDE_FROM_ALL)

add_subdirectory("mbedtls" EXCLUDE_FROM_ALL)

add_subdirectory("Eightest" EXCLUDE_FROM_ALL)
add_subdirectory("Eightmory" EXCLUDE_FROM_ALL)
add_subdirectory("Eightrefl" EXCLUDE_FROM_ALL)
add_subdirectory("Eightser" EXCLUDE_FROM_ALL)
