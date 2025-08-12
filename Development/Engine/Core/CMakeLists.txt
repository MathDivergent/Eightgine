# [[Binaries]]
eightgine_add_module(MODULE_NAME "EightgineCore"
    MODULE_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include"
    MODULE_SOURCES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src" "${CMAKE_CURRENT_SOURCE_DIR}/include"
)


# [[Dependencies]]
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "EightgineCore" DEPENDENCY_NAME "EightginePlatform")
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "EightgineCore" DEPENDENCY_NAME "cJSON")

eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "EightgineCore" DEPENDENCY_NAME "SDL2")
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "EightgineCore" DEPENDENCY_NAME "SDL2_image")
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "EightgineCore" DEPENDENCY_NAME "SDL2_mixer")
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "EightgineCore" DEPENDENCY_NAME "SDL2_ttf")
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "EightgineCore" DEPENDENCY_NAME "SDL2_net")

#eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "EightgineCore" DEPENDENCY_NAME "BoringSSL")

eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "EightgineCore" DEPENDENCY_NAME "box2d")
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "EightgineCore" DEPENDENCY_NAME "lua")

eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "EightgineCore" DEPENDENCY_NAME "Eightmory")
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "EightgineCore" DEPENDENCY_NAME "Eightrefl")
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "EightgineCore" DEPENDENCY_NAME "Eightser")

if(EIGHTGINE_WITH_EDITOR)
    eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "EightgineCore" DEPENDENCY_NAME "Eightest")
endif()
