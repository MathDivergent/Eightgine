#include <CModuleManager.hpp>
#include <CModuleInterface.hpp>

CModuleManager* CModuleManager::Global()
{
    static CModuleManager self; return &self;
}

void CModuleManager::RegisterModule(CModuleInterface* pModuleImplementation)
{
    if (pModuleImplementation == nullptr)
    {
        return;
    }

    RegisteredModules.push_back(pModuleImplementation);
}
