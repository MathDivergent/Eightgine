# [[Defaults]]
option(EIGHTMORY_BUILD_SHARED_LIBS "" ON)
option(EIGHTMORY_BUILD_TEST_LIBS "" ${EIGHTGINE_WITH_EDITOR})


# [[Subdirectories]]
add_subdirectory("Eightmory" EXCLUDE_FROM_ALL)


# [[Binaries]]
eightgine_add_module(MODULE_NAME "Eightmory"
    MODULE_TYPE INTERFACE
    MODULE_API_DEFINITION OFF
    MODULE_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Eightmory/include"
)


# [[Dependencies]]
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "Eightmory" DEPENDENCY_NAME "Eightmory")

if(EIGHTMORY_BUILD_TEST_LIBS)
    eightgine_add_dependency(DEPENDENCY_NAME "EightmoryTests")
    eightgine_configure_module_or_executable(MODULE_OR_EXECUTABLE_NAME "EightmoryTests" MODULE_OR_EXECUTABLE_DESTINATION_DIR "${PROJECT_PLUGINS_DIR}")
endif()
