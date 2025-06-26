# [[Defaults]]
set(THIRDPARTY_FREETYPE_BUILD_SHARED_LIBS ${BUILD_SHARED_LIBS})


# [[Subdirectories]]
add_subdirectory("freetype" EXCLUDE_FROM_ALL)


# [[Binaries]]
eightgine_add_module(MODULE_NAME "freetype"
    MODULE_ALIAS "Freetype::Freetype"
    MODULE_TYPE INTERFACE
    MODULE_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/include"
)

# [[Dependencies]]
eightgine_link_dependency(MODULE_OR_EXECUTABLE_NAME "freetype" DEPENDENCY_NAME "freetype")
