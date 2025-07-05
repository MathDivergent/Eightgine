# [[Binaries]]
eightgine_add_module(MODULE_NAME "Platforms-Linux-Minimal" MODULE_TYPE INTERFACE MODULE_API_DEFINITION OFF)


# [[Dependencies]]
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "Platforms-Linux-Minimal" DEPENDENCY_NAME "m")
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "Platforms-Linux-Minimal" DEPENDENCY_NAME "pthread")
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "Platforms-Linux-Minimal" DEPENDENCY_NAME "dl")
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "Platforms-Linux-Minimal" DEPENDENCY_NAME "rt")


# [[Binaries]]
eightgine_add_module(MODULE_NAME "Platforms-Linux-Graphics" MODULE_TYPE INTERFACE MODULE_API_DEFINITION OFF)


# [[Dependencies]]
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "Platforms-Linux-Graphics" DEPENDENCY_NAME "Xext")
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "Platforms-Linux-Graphics" DEPENDENCY_NAME "Xrandr")
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "Platforms-Linux-Graphics" DEPENDENCY_NAME "Xcursor")
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "Platforms-Linux-Graphics" DEPENDENCY_NAME "Xi")
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "Platforms-Linux-Graphics" DEPENDENCY_NAME "wayland-client")
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "Platforms-Linux-Graphics" DEPENDENCY_NAME "wayland-cursor")
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "Platforms-Linux-Graphics" DEPENDENCY_NAME "wayland-egl")


# [[Binaries]]
eightgine_add_module(MODULE_NAME "Platforms-Linux-Audio" MODULE_TYPE INTERFACE MODULE_API_DEFINITION OFF)


# [[Dependencies]]
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "Platforms-Linux-Audio" DEPENDENCY_NAME "asound")
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "Platforms-Linux-Audio" DEPENDENCY_NAME "pulse")
