# [[Defaults]]
set(THIRDPARTY_OPUSFILE_BUILD_SHARED_LIBS OFF)


# [[Binaries]]
if(THIRDPARTY_OPUSFILE_BUILD_SHARED_LIBS)
    eightgine_add_module(MODULE_NAME "opusfile"
        MODULE_ALIAS "OpusFile::opusfile"
        MODULE_TYPE SHARED
    )
else()
    eightgine_add_module(MODULE_NAME "opusfile"
        MODULE_ALIAS "OpusFile::opusfile"
        MODULE_TYPE STATIC
    )
endif()

eightgine_configure_module_or_executable(MODULE_OR_EXECUTABLE_NAME "opusfile"
    MODULE_OR_EXECUTABLE_SOURCES_DIR "${CMAKE_CURRENT_LIST_DIR}/src"
    MODULE_OR_EXECUTABLE_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/include"
)


# [[Dependencies]]
eightgine_link_dependency(MODULE_OR_EXECUTABLE_NAME "opusfile" DEPENDENCY_NAME "ogg")
eightgine_link_dependency(MODULE_OR_EXECUTABLE_NAME "opusfile" DEPENDENCY_NAME "opus")
