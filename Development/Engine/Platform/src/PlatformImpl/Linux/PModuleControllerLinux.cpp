#include <PPlatform.hpp>
#include <PModuleControllerInterface.hpp>

#include <dlfcn.h> // dlopen, RTLD_NOW, dlsym, dlclose

struct PModuleControllerLinux : public PModuleControllerInterface
{
    void* LoadModule(std::string const& sModuleName) override;
    void* GetFunction(void* pModule, std::string const& sFunctionName) override;
    bool UnloadModule(void* pModule) override;
};

EIGHTGINE_REGISTER_PLATFORM(ModuleController, PModuleControllerLinux)


void* PModuleControllerLinux::LoadModule(std::string const& sModuleName)
{
    return dlopen(/*filename*/(sModuleName + ".so").c_str(), /*flags*/RTLD_NOW);
}

void* PModuleControllerLinux::GetFunction(void* pModuleHandler, std::string const& sFunctionName)
{
    return dlsym(/*handle*/pModuleHandler, /*symbol*/sFunctionName.c_str());
}

bool PModuleControllerLinux::UnloadModule(void* pModuleHandler)
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
