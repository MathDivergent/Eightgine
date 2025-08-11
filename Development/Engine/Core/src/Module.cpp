#include <Module.hpp>

CModuleRegistry* CModuleRegistry::Global()
{
    static CModuleRegistry self; return &self;
}

bool CModuleRegistry::RegisterModule(CModuleInterface* module)
{
    All.push_back(module);
    return true;
}
