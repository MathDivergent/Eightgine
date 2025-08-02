# [[Defaults]]
option(EIGHTREFL_BUILD_SHARED_LIBS "" ON)
option(EIGHTREFL_BUILD_TEST_LIBS "" ${EIGHTGINE_WITH_EDITOR})


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

if(EIGHTGINE_WITH_EDITOR)
    eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "Eightrefl" DEPENDENCY_NAME "EightreflTests")
endif()
