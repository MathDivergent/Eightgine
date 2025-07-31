# [[Defaults]]
# for 'OFF' value install NASM before:
# Windows: download and install from https://www.nasm.us/pub/nasm/releasebuilds
# Linux: sudo apt install nasm
# MacOS: brew install nasm
option(OPENSSL_NO_ASM "" ON)


# [[Subdirectories]]
add_subdirectory("BoringSSL" EXCLUDE_FROM_ALL)


# [[Binaries]]
eightgine_add_module(MODULE_NAME "BoringSSL"
    MODULE_TYPE INTERFACE
    MODULE_API_DEFINITION OFF
    MODULE_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/BoringSSL/include"
)


# [[Dependencies]]
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "BoringSSL" DEPENDENCY_NAME "ssl")
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "BoringSSL" DEPENDENCY_NAME "crypto")
