# [[Defaults]]
set(THIRDPARTY_OPUS_BUILD_SHARED_LIBS ${BUILD_SHARED_LIBS})


# [[Subdirectories]]
add_subdirectory("opus" EXCLUDE_FROM_ALL)


# [[Binaries]]
eightgine_add_module(MODULE_NAME "opus"
    MODULE_ALIAS "Opus::opus"
    MODULE_TYPE INTERFACE
    MODULE_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/include"
)

# [[Dependencies]]
eightgine_link_dependency(MODULE_OR_EXECUTABLE_NAME "opus" DEPENDENCY_NAME "opus")
