# [[Defaults]]
option(EIGHTSER_BUILD_SHARED_LIBS "" ON)
option(EIGHTSER_BUILD_TEST_LIBS "" ${EIGHTGINE_WITH_EDITOR})

option(EIGHTSER_RTTI_ENABLE "" ON) # readonly TODO: switch to OFF


# [[Subdirectories]]
add_subdirectory("Eightser" EXCLUDE_FROM_ALL)

# On Windows, export all symbols; keep EIGHTSER_API empty for GCC/Clang ABI compatibility (GCC PR 89088).
if(EIGHTGINE_PLATFORM_WINDOWS)
    set_target_properties(Eightser PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)
    target_compile_options(Eightser PRIVATE $<$<CXX_COMPILER_ID:GNU,Clang>:-UEIGHTSER_API -DEIGHTSER_API=>)
endif()


# [[Binaries]]
eightgine_add_module(MODULE_NAME "Eightser"
    MODULE_TYPE INTERFACE
    MODULE_DEFAULT_DEFINITIONS OFF
    MODULE_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Eightser/include"
)


# [[Dependencies]]
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "Eightser" DEPENDENCY_NAME "Eightser")

if(EIGHTSER_BUILD_TEST_LIBS)
    eightgine_add_dependency(DEPENDENCY_NAME "EightserTests")
    eightgine_configure_module_or_executable(MODULE_OR_EXECUTABLE_NAME "EightserTests" MODULE_OR_EXECUTABLE_DESTINATION_DIR "${PROJECT_PLUGINS_DIR}")
endif()
