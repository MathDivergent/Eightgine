# [[Subdirectories]]
if(EIGHTGINE_PLATFORM_WINDOWS)
    add_subdirectory("Windows")
elseif(EIGHTGINE_PLATFORM_LINUX)
    add_subdirectory("Linux")
elseif(EIGHTGINE_PLATFORM_MACOS)
    add_subdirectory("macOS")
endif()
