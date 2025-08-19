# [[Defaults]]
option(ENTT_BUILD_TESTING "" OFF) # readonly
option(ENTT_INCLUDE_HEADERS "" ON) # readonly
option(ENTT_INCLUDE_NATVIS "" OFF) # readonly


# [[Subdirectories]]
add_subdirectory("entt" EXCLUDE_FROM_ALL)


# [[Binaries]]
eightgine_add_module(MODULE_NAME "entt"
    MODULE_TYPE INTERFACE
    MODULE_API_DEFINITION OFF
    MODULE_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/ennt/src"
)


# [[Dependencies]]
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "entt" DEPENDENCY_NAME "EnTT")