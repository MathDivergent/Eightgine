# [[Root]]
project(RewTesting)


# [[Subdirectories]]
add_subdirectory("Automation")


# [[Binaries]]
file(GLOB_RECURSE PROJECT_TEST_SOURCES "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp" "${CMAKE_CURRENT_LIST_DIR}/src/*.hpp")
add_executable("${PROJECT_NAME}" ${PROJECT_TEST_SOURCES})


# [[Dependencies]]
target_link_libraries("${PROJECT_NAME}" PRIVATE Automation Rew)
target_include_directories("${PROJECT_NAME}" PRIVATE "${CMAKE_CURRENT_LIST_DIR}/src")


# [[Definitions]]
# we should define this macro to enable additional checks for testing
target_compile_definitions(Rew PUBLIC
    REW_FULLY_ENABLE
    REW_RTTI_ALL_ENABLE
    # REW_DEV_ENABLE
)
