# [[Subdirectories]]
add_subdirectory("cJSON" EXCLUDE_FROM_ALL)
add_subdirectory("SDL2" EXCLUDE_FROM_ALL)
add_subdirectory("SDL2_image" EXCLUDE_FROM_ALL)

add_subdirectory("ogg" EXCLUDE_FROM_ALL)
add_subdirectory("opus" EXCLUDE_FROM_ALL)
add_subdirectory("opusfile" EXCLUDE_FROM_ALL)
add_subdirectory("wavpack" EXCLUDE_FROM_ALL)
add_subdirectory("SDL2_mixer" EXCLUDE_FROM_ALL)

#add_subdirectory("SDL2_ttf" EXCLUDE_FROM_ALL)
add_subdirectory("SDL2_net")

if(EIGHTGINE_DEBUG)
    add_subdirectory("Eightest" EXCLUDE_FROM_ALL)
endif()
