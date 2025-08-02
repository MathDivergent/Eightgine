# [[Defaults]]
option(EIGHTSER_BUILD_SHARED_LIBS "" ${BUILD_SHARED_LIBS})
option(EIGHTSER_BUILD_TEST_LIBS "" ${EIGHTGINE_WITH_EDITOR})


# [[Subdirectories]]
add_subdirectory("Eightser" EXCLUDE_FROM_ALL)


# [[Binaries]]
eightgine_add_module(MODULE_NAME "Eightser"
    MODULE_TYPE INTERFACE
    MODULE_API_DEFINITION OFF
    MODULE_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Eightser/include"
)


# [[Dependencies]]
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "Eightser" DEPENDENCY_NAME "Eightser")

if(EIGHTGINE_WITH_EDITOR)
    eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "Eightser" DEPENDENCY_NAME "EightserTests")
endif()
