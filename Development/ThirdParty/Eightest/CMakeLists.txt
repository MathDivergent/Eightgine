# [[Defaults]]
set(THIRDPARTY_EIGHTEST_BUILD_SHARED_LIBS ON)


# [[Binaries]]
if(THIRDPARTY_EIGHTEST_BUILD_SHARED_LIBS)
    eightgine_add_module(MODULE_NAME "Eightest" MODULE_TYPE SHARED)
else()
    eightgine_add_module(MODULE_NAME "Eightest" MODULE_TYPE STATIC)
endif()

eightgine_configure_module_or_executable(MODULE_OR_EXECUTABLE_NAME "Eightest"
    MODULE_OR_EXECUTABLE_SOURCES_DIR "${CMAKE_CURRENT_LIST_DIR}/src"
    MODULE_OR_EXECUTABLE_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/include" "${CMAKE_CURRENT_LIST_DIR}/include/Eightest"
)
