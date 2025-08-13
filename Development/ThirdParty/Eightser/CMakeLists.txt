# [[Defaults]]
option(EIGHTSER_BUILD_SHARED_LIBS "" ${BUILD_SHARED_LIBS})
option(EIGHTSER_BUILD_TEST_LIBS "" ${EIGHTGINE_WITH_EDITOR})

option(EIGHTSER_RTTI_ENABLE "" ON) # readonly


# [[Subdirectories]]
add_subdirectory("Eightser")


# [[Binaries]]
eightgine_add_module(MODULE_NAME "Eightser"
    MODULE_TYPE INTERFACE
    MODULE_API_DEFINITION OFF
    MODULE_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Eightser/include"
)


# [[Dependencies]]
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "Eightser" DEPENDENCY_NAME "Eightser")

if(EIGHTSER_BUILD_TEST_LIBS)
    eightgine_configure_module_or_executable(MODULE_OR_EXECUTABLE_NAME "EightserTests" MODULE_OR_EXECUTABLE_DESTINATION_DIR "${PROJECT_PLUGINS_DIR}")
endif()
