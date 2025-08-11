#include <PModuleControllerWindows.hpp>
#include <PPlatform.hpp>

#include <windows.h> // LoadLibraryA, HMODULE, GetProcAddress, FreeLibrary

EIGHTGINE_REGISTRY_PLATFORM(ModuleController, PModuleControllerWindows)


void* PModuleControllerWindows::LoadModule(std::string const& sModuleName)
{
    return (void*)LoadLibraryA(/*lpLibFileName*/(sModuleName + ".dll").c_str());
}

void* PModuleControllerWindows::GetFunction(void* pModuleHandler, std::string const& sFunctionName)
{
    return (void*)GetProcAddress(/*hModule*/(HMODULE)pModuleHandler, /*lpProcName*/sFunctionName.c_str());
}

bool PModuleControllerWindows::UnloadModule(void* pModuleHandler)
{
    if (pModuleHandler == NULL)
    {
        return false;
    }
    else
    {
        return (bool)FreeLibrary(/*hLibModule*/(HMODULE)pModuleHandler);
    }
}
