# [[Defaults]]
option(EIGHTREFL_BUILD_SHARED_LIBS "" ON)
option(EIGHTREFL_BUILD_TEST_LIBS "" ${EIGHTGINE_WITH_EDITOR})

option(EIGHTREFL_RTTI_ENABLE "" ON) # readonly TODO: switch to OFF


# [[Subdirectories]]
add_subdirectory("Eightrefl" EXCLUDE_FROM_ALL)


# [[Binaries]]
eightgine_add_module(MODULE_NAME "Eightrefl"
    MODULE_TYPE INTERFACE
    MODULE_API_DEFINITION OFF
    MODULE_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Eightrefl/include"
)


# [[Dependencies]]
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "Eightrefl" DEPENDENCY_NAME "Eightrefl")

if(EIGHTREFL_BUILD_TEST_LIBS)
    eightgine_add_dependency(DEPENDENCY_NAME "EightreflTests")
    eightgine_configure_module_or_executable(MODULE_OR_EXECUTABLE_NAME "EightreflTests" MODULE_OR_EXECUTABLE_DESTINATION_DIR "${PROJECT_PLUGINS_DIR}")
endif()
