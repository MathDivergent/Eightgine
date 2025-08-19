# [[Defaults]]
option(ENABLE_CJSON_UTILS "" ON)
option(ENABLE_CJSON_TEST "" OFF) # readonly
option(ENABLE_FUZZING "" OFF) # readonly


# [[Subdirectories]]
add_subdirectory("cJSON" EXCLUDE_FROM_ALL)

target_compile_options(cjson PRIVATE $<$<CXX_COMPILER_ID:GNU,Clang>:-w>) # disable warnings


# [[Binaries]]
eightgine_add_module(MODULE_NAME "cJSON"
    MODULE_TYPE INTERFACE
    MODULE_API_DEFINITION OFF
    MODULE_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/cJSON"
)


# [[Dependencies]]
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "cJSON" DEPENDENCY_NAME "cjson" DEPENDENCY_SCOPE INTERFACE)
