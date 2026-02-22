# [[Defaults]]
option(BUILD_DEMOS "" OFF)

if(BUILD_SHARED_LIBS)
    option(BUILD_STATIC "" OFF)
else()
    option(BUILD_STATIC "" ON)
endif()

option(BUILD_SHARED "" ${BUILD_SHARED_LIBS})

option(INSTALL_STATIC "" OFF)
option(INSTALL_DEMOS "" OFF)


# [[Subdirectories]]
add_subdirectory("Chipmunk2D" EXCLUDE_FROM_ALL)

if(BUILD_SHARED_LIBS)
    target_compile_options(chipmunk PRIVATE $<$<CXX_COMPILER_ID:GNU,Clang>:-w>) # disable warnings
else()
    target_compile_options(chipmunk_static PRIVATE $<$<CXX_COMPILER_ID:GNU,Clang>:-w>) # disable warnings
endif()


# [[Binaries]]
eightgine_add_module(MODULE_NAME "chipmunk"
    MODULE_TYPE INTERFACE
    MODULE_API_DEFINITION OFF
    MODULE_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Chipmunk2D/include"
)


# [[Dependencies]]
if(BUILD_SHARED_LIBS)
    eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "chipmunk" DEPENDENCY_NAME "chipmunk")
else()
    eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "chipmunk" DEPENDENCY_NAME "chipmunk_static")
endif()
