# [[Binaries]]
eightgine_add_module(MODULE_NAME "EightgineEditor"
    MODULE_TYPE SHARED
    MODULE_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include"
    MODULE_SOURCES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src" "${CMAKE_CURRENT_SOURCE_DIR}/include"
)


# [[Dependencies]]
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "EightgineEditor" DEPENDENCY_NAME "EightgineCore")
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "EightgineEditor" DEPENDENCY_NAME "EightgineInteractive")

if(EIGHTGINE_WITH_EDITOR)
    eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "EightgineEditor" DEPENDENCY_NAME "Eightest")
endif()
