# [[Subdirectories]]
add_subdirectory("opus" EXCLUDE_FROM_ALL)

target_compile_options(opus PRIVATE $<$<CXX_COMPILER_ID:GNU,Clang>:-w>) # disable warnings


# [[Binaries]]
eightgine_add_module(MODULE_NAME "opus"
    MODULE_TYPE INTERFACE
    MODULE_DEFAULT_DEFINITIONS OFF
    MODULE_DEFAULT_OPTIONS OFF
    MODULE_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/opus/include"
)


# [[Dependencies]]
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "opus" DEPENDENCY_NAME "opus")
