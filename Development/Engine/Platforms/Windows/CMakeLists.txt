# [[Binaries]]
eightgine_add_module(MODULE_NAME "EightginePlatformWindows"
    MODULE_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include"
    MODULE_SOURCES_DIR "${CMAKE_CURRENT_SOURCE_DIR}"
)


# [[Dependencies]]
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "EightginePlatformWindows" DEPENDENCY_NAME "EightgineCore")
