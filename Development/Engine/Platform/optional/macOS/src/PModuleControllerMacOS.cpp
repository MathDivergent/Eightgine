#include <PModuleControllerMacOS.hpp>
#include <PPlatform.hpp>

#include <dlfcn.h> // dlopen, RTLD_NOW, dlsym, dlclose

EIGHTGINE_REGISTRY_PLATFORM(ModuleController, PModuleControllerMacOS)


void* PModuleControllerMacOS::LoadModule(std::string const& sModuleName)
{
    return dlopen(/*filename*/(sModuleName + ".dylib").c_str(), /*flags*/RTLD_NOW);
}

void* PModuleControllerMacOS::GetFunction(void* pModuleHandler, std::string const& sFunctionName)
{
    return dlsym(/*handle*/pModuleHandler, /*symbol*/sFunctionName.c_str());
}

bool PModuleControllerMacOS::UnloadModule(void* pModuleHandler)
{
    if (pModuleHandler == NULL)
    {
        return false;
    }
    else
    {
        return dlclose(/*handle*/pModuleHandler) == 0;
    }
}
