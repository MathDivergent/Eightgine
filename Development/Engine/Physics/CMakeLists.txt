# [[Binaries]]
eightgine_add_module(MODULE_NAME "EightginePhysics"
    MODULE_TYPE SHARED
    MODULE_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include"
    MODULE_SOURCES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src" "${CMAKE_CURRENT_SOURCE_DIR}/include"
)


# [[Dependencies]]
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "EightginePhysics" DEPENDENCY_NAME "EightgineCore")

if(TRUE) # TODO: provide choosing
    eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "EightginePhysics" DEPENDENCY_NAME "box2d" DEPENDENCY_SCOPE PRIVATE)
else()
    eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "EightginePhysics" DEPENDENCY_NAME "chipmunk" DEPENDENCY_SCOPE PRIVATE)
endif()

if(EIGHTGINE_WITH_EDITOR)
    eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "EightginePhysics" DEPENDENCY_NAME "Eightest")
endif()
