# [[Subdirectories]]
add_subdirectory("freetype" EXCLUDE_FROM_ALL)


# [[Binaries]]
eightgine_add_module(MODULE_NAME "freetype"
    MODULE_ALIAS "Freetype::Freetype"
    MODULE_TYPE INTERFACE
    MODULE_API_DEFINITION OFF
    MODULE_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/freetype/include"
)


# [[Dependencies]]
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "freetype" DEPENDENCY_NAME "freetype")
