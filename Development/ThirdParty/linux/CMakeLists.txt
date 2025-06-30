# [[Binaries]]
eightgine_add_module(MODULE_NAME "glibc" MODULE_TYPE INTERFACE)
eightgine_add_module(MODULE_NAME "X11" MODULE_TYPE INTERFACE)
eightgine_add_module(MODULE_NAME "Wayland" MODULE_TYPE INTERFACE)


# [[Dependencies]]
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "glibc" DEPENDENCY_NAME "m")
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "glibc" DEPENDENCY_NAME "pthread")
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "glibc" DEPENDENCY_NAME "dl")
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "glibc" DEPENDENCY_NAME "rt")

eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "X11" DEPENDENCY_NAME "X11")
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "X11" DEPENDENCY_NAME "Xext")
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "X11" DEPENDENCY_NAME "Xrandr")
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "X11" DEPENDENCY_NAME "Xcursor")
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "X11" DEPENDENCY_NAME "Xi")

eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "Wayland" DEPENDENCY_NAME "wayland-client")
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "Wayland" DEPENDENCY_NAME "wayland-cursor")
eightgine_add_dependency(MODULE_OR_EXECUTABLE_NAME "Wayland" DEPENDENCY_NAME "wayland-egl")
