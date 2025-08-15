# [[Defaults]]
option(ENABLE_TESTING "" OFF) # readonly
option(ENABLE_PROGRAMS "" OFF) # readonly

if(BUILD_SHARED_LIBS)
    option(USE_STATIC_MBEDTLS_LIBRARY "" OFF)
else()
    option(USE_STATIC_MBEDTLS_LIBRARY "" ON)
endif()

option(USE_SHARED_MBEDTLS_LIBRARY "" ${BUILD_SHARED_LIBS})


# [[Subdirectories]]
add_subdirectory("mbedtls" EXCLUDE_FROM_ALL)


# [[Binaries]]
eightgine_add_module(MODULE_NAME "mbedtls"
    MODULE_TYPE INTERFACE
    MODULE_API_DEFINITION OFF
    MODULE_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/mbedtls/include"
)


# [[Dependencies]]
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "mbedtls" DEPENDENCY_NAME "MbedTLS::mbedtls")
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "mbedtls" DEPENDENCY_NAME "MbedTLS::mbedx509")
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "mbedtls" DEPENDENCY_NAME "MbedTLS::mbedcrypto")
