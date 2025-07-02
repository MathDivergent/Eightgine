# [[Binaries]]
if(BUILD_SHARED_LIBS)
    eightgine_add_module(MODULE_NAME "opusfile"
        MODULE_ALIAS "OpusFile::opusfile"
        MODULE_TYPE SHARED
        MODULE_API_DEFINITION OFF
    )
else()
    eightgine_add_module(MODULE_NAME "opusfile"
        MODULE_ALIAS "OpusFile::opusfile"
        MODULE_TYPE STATIC
        MODULE_API_DEFINITION OFF
    )
endif()

eightgine_configure_module_or_executable(MODULE_OR_EXECUTABLE_NAME "opusfile"
    MODULE_OR_EXECUTABLE_SOURCES_DIR "${CMAKE_CURRENT_LIST_DIR}/src"
    MODULE_OR_EXECUTABLE_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/include"
)


# [[Dependencies]]
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "opusfile" DEPENDENCY_NAME "ogg")
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "opusfile" DEPENDENCY_NAME "opus")
