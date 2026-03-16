# [[Binaries]]
eightgine_add_module(MODULE_NAME "EightgineObjects"
    MODULE_TYPE SHARED
    MODULE_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include"
    MODULE_SOURCES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src" "${CMAKE_CURRENT_SOURCE_DIR}/include"
)


# [[Dependencies]]
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "EightgineObjects" DEPENDENCY_NAME "EightgineCore")

if(FALSE) # TODO: provide choosing
    eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "EightgineObjects" DEPENDENCY_NAME "entt" DEPENDENCY_SCOPE PRIVATE)
endif()

if(EIGHTGINE_WITH_EDITOR)
    eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "EightgineCore" DEPENDENCY_NAME "Eightest")
endif()
