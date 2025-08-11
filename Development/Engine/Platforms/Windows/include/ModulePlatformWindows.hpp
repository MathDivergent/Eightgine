#ifndef EIGHTGINEPLATFORMWINDOWS_MODULE_PLATFORM_WINDOWS_HPP
#define EIGHTGINEPLATFORMWINDOWS_MODULE_PLATFORM_WINDOWS_HPP

#include <Module.hpp>

struct EIGHTGINEPLATFORMWINDOWS_API CModulePlatformWindows : public CModuleInterface
{
    void OnLoad() override;
    void OnProcess() override;
    void OnUnload() override;
};

#endif // EIGHTGINEPLATFORMWINDOWS_MODULE_PLATFORM_WINDOWS_HPP
