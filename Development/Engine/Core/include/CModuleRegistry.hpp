#ifndef EIGHTGINECORE_CMODULE_REGISTRY_HPP
#define EIGHTGINECORE_CMODULE_REGISTRY_HPP

#include <vector> // vector

#define EIGHTGINE_REGISTRY_MODULE(name) \
    static struct name##Register \
    { \
        name##Register() \
        { \
            CModuleRegistry::Global()->RegisterModule(new name()); \
        } \
    } xx##name##Register;


struct CModuleInterface;

struct EIGHTGINECORE_API CModuleRegistry
{
    std::vector<CModuleInterface*> All;

    static CModuleRegistry* Global();

    void RegisterModule(CModuleInterface* module);
};

#endif // EIGHTGINECORE_CMODULE_REGISTRY_HPP
