# [[Binaries]]
eightgine_add_module(MODULE_NAME "EightgineCore"
    MODULE_SOURCES_DIR "${CMAKE_CURRENT_LIST_DIR}"
    MODULE_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}"
)


# [[Dependencies]]
eightgine_link_dependency(MODULE_OR_EXECUTABLE_NAME "EightgineCore" DEPENDENCY_NAME "cJSON")
eightgine_link_dependency(MODULE_OR_EXECUTABLE_NAME "EightgineCore" DEPENDENCY_NAME "SDL2")
eightgine_link_dependency(MODULE_OR_EXECUTABLE_NAME "EightgineCore" DEPENDENCY_NAME "SDL2_image")
eightgine_link_dependency(MODULE_OR_EXECUTABLE_NAME "EightgineCore" DEPENDENCY_NAME "SDL2_mixer")
#eightgine_link_dependency(MODULE_OR_EXECUTABLE_NAME "EightgineCore" DEPENDENCY_NAME "SDL2_ttf")
eightgine_link_dependency(MODULE_OR_EXECUTABLE_NAME "EightgineCore" DEPENDENCY_NAME "SDL2_net")

if(EIGHTGINE_DEBUG)
    eightgine_link_dependency(MODULE_OR_EXECUTABLE_NAME "EightgineCore" DEPENDENCY_NAME "Eightest")
endif()
