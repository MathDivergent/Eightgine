# [[Binaries]]
eightgine_add_module(MODULE_NAME "EightgineCore"
    MODULE_SOURCES_DIR "${CMAKE_CURRENT_LIST_DIR}"
    MODULE_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}"
)

eightgine_add_thirdparty(THIRDPARTY_NAME "cJSON" THIRDPARTY_DIR "${EIGHTGINE_THIRDPARTY_DIR}")
eightgine_add_thirdparty(THIRDPARTY_NAME "SDL2" THIRDPARTY_DIR "${EIGHTGINE_THIRDPARTY_DIR}")
eightgine_add_thirdparty(THIRDPARTY_NAME "SDL2_image" THIRDPARTY_DIR "${EIGHTGINE_THIRDPARTY_DIR}")
#eightgine_add_thirdparty(THIRDPARTY_NAME "SDL2_mixer" THIRDPARTY_DIR "${EIGHTGINE_THIRDPARTY_DIR}")
eightgine_add_thirdparty(THIRDPARTY_NAME "SDL2_ttf" THIRDPARTY_DIR "${EIGHTGINE_THIRDPARTY_DIR}")
eightgine_add_thirdparty(THIRDPARTY_NAME "SDL2_net" THIRDPARTY_DIR "${EIGHTGINE_THIRDPARTY_DIR}")
eightgine_add_thirdparty(THIRDPARTY_NAME "Automation" THIRDPARTY_DIR "${EIGHTGINE_THIRDPARTY_DIR}")


# [[Dependencies]]
eightgine_link_dependency(MODULE_OR_EXECUTABLE_NAME "EightgineCore" DEPENDENCY_NAME "cJSON")
eightgine_link_dependency(MODULE_OR_EXECUTABLE_NAME "EightgineCore" DEPENDENCY_NAME "SDL2")
eightgine_link_dependency(MODULE_OR_EXECUTABLE_NAME "EightgineCore" DEPENDENCY_NAME "SDL2_image")
#eightgine_link_dependency(MODULE_OR_EXECUTABLE_NAME "EightgineCore" DEPENDENCY_NAME "SDL2_mixer")
eightgine_link_dependency(MODULE_OR_EXECUTABLE_NAME "EightgineCore" DEPENDENCY_NAME "SDL2_ttf")
eightgine_link_dependency(MODULE_OR_EXECUTABLE_NAME "EightgineCore" DEPENDENCY_NAME "SDL2_net")
eightgine_link_dependency(MODULE_OR_EXECUTABLE_NAME "EightgineCore" DEPENDENCY_NAME "Automation")
