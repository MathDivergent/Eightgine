# [[Binaries]]
eightgine_add_module(MODULE_NAME "EightgineNetwork"
    MODULE_TYPE SHARED
    MODULE_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include"
    MODULE_SOURCES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src" "${CMAKE_CURRENT_SOURCE_DIR}/include"
)


# [[Dependencies]]
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "EightgineNetwork" DEPENDENCY_NAME "EightgineCore")

eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "EightgineNetwork" DEPENDENCY_NAME "SDL2_net" DEPENDENCY_SCOPE PRIVATE)
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "EightgineNetwork" DEPENDENCY_NAME "mbedtls" DEPENDENCY_SCOPE PRIVATE)

if(EIGHTGINE_WITH_EDITOR)
    eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "EightgineNetwork" DEPENDENCY_NAME "Eightest")
endif()
