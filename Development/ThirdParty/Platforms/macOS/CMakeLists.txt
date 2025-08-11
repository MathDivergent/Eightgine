# [[Binaries]]
eightgine_add_module(MODULE_NAME "PlatformsMacOSMinimal" MODULE_TYPE INTERFACE MODULE_API_DEFINITION OFF)


# [[Dependencies]]
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "PlatformsMacOSMinimal" DEPENDENCY_NAME "-framework CoreFoundation")
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "PlatformsMacOSMinimal" DEPENDENCY_NAME "-framework CoreServices")


# [[Binaries]]
eightgine_add_module(MODULE_NAME "PlatformsMacOSGraphics" MODULE_TYPE INTERFACE MODULE_API_DEFINITION OFF)


# [[Dependencies]]
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "PlatformsMacOSGraphics" DEPENDENCY_NAME "-framework IOKit")
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "PlatformsMacOSGraphics" DEPENDENCY_NAME "-framework CoreVideo")
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "PlatformsMacOSGraphics" DEPENDENCY_NAME "-framework Cocoa")
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "PlatformsMacOSGraphics" DEPENDENCY_NAME "-framework ImageIO")


# [[Binaries]]
eightgine_add_module(MODULE_NAME "PlatformsMacOSAudio" MODULE_TYPE INTERFACE MODULE_API_DEFINITION OFF)


# [[Dependencies]]
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "PlatformsMacOSAudio" DEPENDENCY_NAME "-framework CoreAudio")
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "PlatformsMacOSAudio" DEPENDENCY_NAME "-framework Carbon")
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "PlatformsMacOSAudio" DEPENDENCY_NAME "-framework AudioToolbox")
