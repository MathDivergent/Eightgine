#include <CModuleManager.hpp>
#include <CModuleInterface.hpp>

CModuleManager* CModuleManager::Global()
{
    static CModuleManager self; return &self;
}

void CModuleManager::RegisterModule(CModuleInterface* module)
{
    if (module == nullptr)
    {
        return;
    }

    Modules.push_back(module);
}
