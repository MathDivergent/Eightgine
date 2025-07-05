# [[Binaries]]
eightgine_add_module(MODULE_NAME "Platforms-macOS-Minimal" MODULE_TYPE INTERFACE MODULE_API_DEFINITION OFF)


# [[Dependencies]]
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "Platforms-macOS-Minimal" DEPENDENCY_NAME "-framework CoreFoundation")
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "Platforms-macOS-Minimal" DEPENDENCY_NAME "-framework CoreServices")


# [[Binaries]]
eightgine_add_module(MODULE_NAME "Platforms-macOS-Graphics" MODULE_TYPE INTERFACE MODULE_API_DEFINITION OFF)


# [[Dependencies]]
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "Platforms-macOS-Graphics" DEPENDENCY_NAME "-framework IOKit")
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "Platforms-macOS-Graphics" DEPENDENCY_NAME "-framework CoreVideo")
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "Platforms-macOS-Graphics" DEPENDENCY_NAME "-framework Cocoa")
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "Platforms-macOS-Graphics" DEPENDENCY_NAME "-framework ImageIO")


# [[Binaries]]
eightgine_add_module(MODULE_NAME "Platforms-macOS-Audio" MODULE_TYPE INTERFACE MODULE_API_DEFINITION OFF)


# [[Dependencies]]
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "Platforms-macOS-Audio" DEPENDENCY_NAME "-framework CoreAudio")
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "Platforms-macOS-Audio" DEPENDENCY_NAME "-framework Carbon")
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "Platforms-macOS-Audio" DEPENDENCY_NAME "-framework AudioToolbox")
