# [[Binaries]]
eightgine_add_module(MODULE_NAME "EightgineScripting"
    MODULE_TYPE SHARED
    MODULE_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include"
    MODULE_SOURCES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src" "${CMAKE_CURRENT_SOURCE_DIR}/include"
)


# [[Dependencies]]
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "EightgineScripting" DEPENDENCY_NAME "EightgineCore")

eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "EightgineScripting" DEPENDENCY_NAME "cJSON" DEPENDENCY_SCOPE PRIVATE)
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "EightgineScripting" DEPENDENCY_NAME "lua" DEPENDENCY_SCOPE PRIVATE)
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "EightgineScripting" DEPENDENCY_NAME "iniparser" DEPENDENCY_SCOPE PRIVATE)

if(EIGHTGINE_WITH_EDITOR)
    eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "EightgineScripting" DEPENDENCY_NAME "Eightest")
endif()
