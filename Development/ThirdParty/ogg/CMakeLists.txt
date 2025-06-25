# [[Defaults]]
set(THIRDPARTY_OGG_BUILD_SHARED_LIBS ON)


# [[Binaries]]
if(THIRDPARTY_OGG_BUILD_SHARED_LIBS)
    eightgine_add_module(MODULE_NAME "ogg" MODULE_TYPE SHARED)
else()
    eightgine_add_module(MODULE_NAME "ogg" MODULE_TYPE STATIC)
endif()

eightgine_configure_module_or_executable(MODULE_OR_EXECUTABLE_NAME "ogg"
    MODULE_OR_EXECUTABLE_SOURCES_DIR "${CMAKE_CURRENT_LIST_DIR}/src"
    MODULE_OR_EXECUTABLE_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/include"
)
