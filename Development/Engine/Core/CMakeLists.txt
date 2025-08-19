# [[Binaries]]
eightgine_add_module(MODULE_NAME "EightgineCore"
    MODULE_TYPE SHARED
    MODULE_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include"
    MODULE_SOURCES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src" "${CMAKE_CURRENT_SOURCE_DIR}/include"
)


# [[Dependencies]]
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "EightgineCore" DEPENDENCY_NAME "EightginePlatform")

eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "EightgineCore" DEPENDENCY_NAME "cJSON" DEPENDENCY_SCOPE PRIVATE)
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "EightgineCore" DEPENDENCY_NAME "lua" DEPENDENCY_SCOPE PRIVATE)

eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "EightgineCore" DEPENDENCY_NAME "SDL2" DEPENDENCY_SCOPE PRIVATE)
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "EightgineCore" DEPENDENCY_NAME "SDL2_image" DEPENDENCY_SCOPE PRIVATE)
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "EightgineCore" DEPENDENCY_NAME "SDL2_mixer" DEPENDENCY_SCOPE PRIVATE)
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "EightgineCore" DEPENDENCY_NAME "SDL2_ttf" DEPENDENCY_SCOPE PRIVATE)
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "EightgineCore" DEPENDENCY_NAME "SDL2_net" DEPENDENCY_SCOPE PRIVATE)

eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "EightgineCore" DEPENDENCY_NAME "box2d" DEPENDENCY_SCOPE PRIVATE)
# eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "EightgineCore" DEPENDENCY_NAME "entt" DEPENDENCY_SCOPE PRIVATE)

eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "EightgineCore" DEPENDENCY_NAME "mbedtls" DEPENDENCY_SCOPE PRIVATE)

eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "EightgineCore" DEPENDENCY_NAME "Eightmory")
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "EightgineCore" DEPENDENCY_NAME "Eightrefl")
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "EightgineCore" DEPENDENCY_NAME "Eightser")

if(EIGHTGINE_WITH_EDITOR)
    eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "EightgineCore" DEPENDENCY_NAME "Eightest")
endif()
