#ifndef EIGHTGINECORE_MODULE_HPP
#define EIGHTGINECORE_MODULE_HPP

#include <vector> // vector

#define EIGHTGINE_REGISTRY_MODULE(name) static auto xx##name##Register = CModuleRegistry::Global()->RegisterModule(new name());


struct EIGHTGINECORE_API CModuleInterface
{
    virtual ~CModuleInterface() = default;

    virtual void OnLoad() = 0;
    virtual void OnProcess() = 0;
    virtual void OnUnload() = 0;
};

struct EIGHTGINECORE_API CModuleRegistry
{
    std::vector<CModuleInterface*> All;

    static CModuleRegistry* Global();

    bool RegisterModule(CModuleInterface* module);
};

#endif // EIGHTGINECORE_MODULE_HPP
