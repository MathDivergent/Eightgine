# [[Binaries]]
eightgine_add_module(MODULE_NAME "EmptyProjectCore"
    MODULE_SOURCES_DIR "${CMAKE_CURRENT_SOURCE_DIR}"
    MODULE_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}"
)


# [[Dependencies]]
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "EmptyProjectCore"
    DEPENDENCY_NAME "EightgineCore"
)
