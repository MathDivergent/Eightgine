#include <CModuleRegistry.hpp>

CModuleRegistry* CModuleRegistry::Global()
{
    static CModuleRegistry self; return &self;
}

void CModuleRegistry::RegisterModule(CModuleInterface* module)
{
    if (module == nullptr)
    {
        return;
    }

    All.push_back(module);
}