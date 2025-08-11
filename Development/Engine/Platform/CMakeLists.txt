# [[Binaries]]
eightgine_add_module(MODULE_NAME "EightginePlatform"
    MODULE_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include"
    MODULE_SOURCES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src" "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

if(NOT EIGHTGINE_OVERRIDE_PLATFORM)
    add_subdirectory("optional")
endif()
