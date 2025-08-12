#include <PPlatform.hpp>
#include <PModuleControllerInterface.hpp>

#include <windows.h> // LoadLibraryA, HMODULE, GetProcAddress, FreeLibrary

struct PModuleControllerWindows : public PModuleControllerInterface
{
    void* LoadModule(std::string const& sModuleName) override;
    void* GetFunction(void* pModule, std::string const& sFunctionName) override;
    bool UnloadModule(void* pModule) override;
};

EIGHTGINE_REGISTER_PLATFORM(ModuleController, PModuleControllerWindows)


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
