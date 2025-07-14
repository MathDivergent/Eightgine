# [[Binaries]]
eightgine_add_module(MODULE_NAME "EmptyProjectCore"
    MODULE_SOURCES_DIR "${CMAKE_CURRENT_LIST_DIR}"
    MODULE_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}"
)


# [[Dependencies]]
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "EmptyProjectCore"
    DEPENDENCY_NAME "EightgineCore"
)
