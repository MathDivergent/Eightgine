# [[Binaries]]
eightgine_add_module(MODULE_NAME "EightgineCore"
    MODULE_TYPE SHARED
    MODULE_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include" INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/override"
    MODULE_SOURCES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src" "${CMAKE_CURRENT_SOURCE_DIR}/include"
)


# [[Dependencies]]
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "EightgineCore" DEPENDENCY_NAME "EightginePlatform")

# TODO: hide crypto into another module
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "EightgineCore" DEPENDENCY_NAME "mbedtls" DEPENDENCY_SCOPE PRIVATE)

# TODO: hide formats into other modules
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "EightgineCore" DEPENDENCY_NAME "zlib" DEPENDENCY_SCOPE PRIVATE)
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "EightgineCore" DEPENDENCY_NAME "cJSON" DEPENDENCY_SCOPE PRIVATE)
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "EightgineCore" DEPENDENCY_NAME "iniparser" DEPENDENCY_SCOPE PRIVATE)

eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "EightgineCore" DEPENDENCY_NAME "Eightmory")
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "EightgineCore" DEPENDENCY_NAME "Eightrefl")
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "EightgineCore" DEPENDENCY_NAME "Eightser")

if(EIGHTGINE_WITH_EDITOR)
    eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "EightgineCore" DEPENDENCY_NAME "Eightest")
endif()
