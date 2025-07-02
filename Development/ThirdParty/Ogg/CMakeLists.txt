# [[Binaries]]
if(BUILD_SHARED_LIBS)
    eightgine_add_module(MODULE_NAME "ogg"
        MODULE_ALIAS "Ogg::ogg"
        MODULE_TYPE SHARED
        MODULE_API_DEFINITION OFF
    )
else()
    eightgine_add_module(MODULE_NAME "ogg"
        MODULE_ALIAS "Ogg::ogg"
        MODULE_TYPE STATIC
        MODULE_API_DEFINITION OFF
    )
endif()

eightgine_configure_module_or_executable(MODULE_OR_EXECUTABLE_NAME "ogg"
    MODULE_OR_EXECUTABLE_SOURCES_DIR "${CMAKE_CURRENT_LIST_DIR}/src"
    MODULE_OR_EXECUTABLE_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/include"
)
