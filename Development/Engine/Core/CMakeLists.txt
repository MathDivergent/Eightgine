# [[Binaries]]
eightgine_add_module(MODULE_NAME "EightgineCore"
    MODULE_SOURCES_DIR "${CMAKE_CURRENT_LIST_DIR}"
    MODULE_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}"
)

eightgine_add_thirdparty(THIRDPARTY_NAME "cJSON"
    THIRDPARTY_DIR "${EIGHTGINE_THIRDPARTY_DIR}"
)

eightgine_add_thirdparty(THIRDPARTY_NAME "SDL2"
    THIRDPARTY_DIR "${EIGHTGINE_THIRDPARTY_DIR}"
)

eightgine_add_module(MODULE_NAME "Automation"
    MODULE_SOURCES_DIR "${EIGHTGINE_THIRDPARTY_DIR}/Automation/src"
    MODULE_INCLUDE_DIR "${EIGHTGINE_THIRDPARTY_DIR}/Automation/include"
)


# [[Dependencies]]
eightgine_link_dependency(MODULE_OR_EXECUTABLE_NAME "EightgineCore"
    DEPENDENCY_NAME "SDL2"
)

# eightgine_link_dependency(MODULE_OR_EXECUTABLE_NAME "EightgineCore"
#     DEPENDENCY_NAME "SDL2_image"
#     DEPENDENCY_INCLUDE_DIR "${EIGHTGINE_THIRDPARTY_DIR}/SDL2_image/include" "${EIGHTGINE_THIRDPARTY_DIR}/SDL2_image/include/SDL2"
#     DEPENDENCY_LIB_DIR "${EIGHTGINE_THIRDPARTY_DIR}/SDL2_image/lib"
#     DEPENDENCY_BIN_DIR "${EIGHTGINE_THIRDPARTY_DIR}/SDL2_image/bin"
# )

# eightgine_link_dependency(MODULE_OR_EXECUTABLE_NAME "EightgineCore"
#     DEPENDENCY_NAME "glfw3"
#     DEPENDENCY_INCLUDE_DIR "${EIGHTGINE_THIRDPARTY_DIR}/GLFW/include"
#     DEPENDENCY_LIB_DIR "${EIGHTGINE_THIRDPARTY_DIR}/GLFW/lib"
#     DEPENDENCY_BIN_DIR "${EIGHTGINE_THIRDPARTY_DIR}/GLFW/bin"
# )

eightgine_link_dependency(MODULE_OR_EXECUTABLE_NAME "EightgineCore"
    DEPENDENCY_NAME "Automation"
)

eightgine_link_dependency(MODULE_OR_EXECUTABLE_NAME "EightgineCore"
    DEPENDENCY_NAME "cJSON"
)
