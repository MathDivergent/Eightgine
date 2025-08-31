# [[Defaults]]
option(BUILD_TESTING "" OFF) # readonly
option(BUILD_EXAMPLES "" OFF) # readonly


# [[Subdirectories]]
add_subdirectory("iniparser" EXCLUDE_FROM_ALL)


# [[Binaries]]
if(BUILD_SHARED_LIBS)
    eightgine_add_module(MODULE_NAME "iniparser"
        MODULE_TYPE INTERFACE
        MODULE_API_DEFINITION OFF
    )
else()
    eightgine_add_module(MODULE_NAME "iniparser"
        MODULE_TYPE INTERFACE
        MODULE_API_DEFINITION OFF
    )
endif()

eightgine_configure_module_or_executable(MODULE_OR_EXECUTABLE_NAME "iniparser"
    MODULE_OR_EXECUTABLE_INCLUDE_DIR "iniparser/src"
)


# [[Dependencies]]
if(BUILD_SHARED_LIBS)
    eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "iniparser" DEPENDENCY_NAME "iniparser-shared")
else()
    eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "iniparser" DEPENDENCY_NAME "iniparser-static")
endif()