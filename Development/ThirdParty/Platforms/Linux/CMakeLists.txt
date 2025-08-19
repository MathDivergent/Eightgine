# [[Binaries]]
eightgine_add_module(MODULE_NAME "PlatformsLinuxMinimal" MODULE_TYPE INTERFACE MODULE_API_DEFINITION OFF)


# [[Dependencies]]
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "PlatformsLinuxMinimal" DEPENDENCY_NAME "m")
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "PlatformsLinuxMinimal" DEPENDENCY_NAME "pthread")
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "PlatformsLinuxMinimal" DEPENDENCY_NAME "dl")
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "PlatformsLinuxMinimal" DEPENDENCY_NAME "rt")


# [[Binaries]]
eightgine_add_module(MODULE_NAME "PlatformsLinuxGraphics" MODULE_TYPE INTERFACE MODULE_API_DEFINITION OFF)


# [[Dependencies]]
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "PlatformsLinuxGraphics" DEPENDENCY_NAME "Xext")
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "PlatformsLinuxGraphics" DEPENDENCY_NAME "Xrandr")
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "PlatformsLinuxGraphics" DEPENDENCY_NAME "Xcursor")
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "PlatformsLinuxGraphics" DEPENDENCY_NAME "Xi")
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "PlatformsLinuxGraphics" DEPENDENCY_NAME "wayland-client")
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "PlatformsLinuxGraphics" DEPENDENCY_NAME "wayland-cursor")
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "PlatformsLinuxGraphics" DEPENDENCY_NAME "wayland-egl")


# [[Binaries]]
eightgine_add_module(MODULE_NAME "PlatformsLinuxAudio" MODULE_TYPE INTERFACE MODULE_API_DEFINITION OFF)


# [[Dependencies]]
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "PlatformsLinuxAudio" DEPENDENCY_NAME "asound")
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "PlatformsLinuxAudio" DEPENDENCY_NAME "pulse")
