#ifndef EIGHTGINECORE_CMODULE_MANAGER_HPP
#define EIGHTGINECORE_CMODULE_MANAGER_HPP

#include <vector> // vector

#define EIGHTGINE_REGISTER_MODULE(name) \
    static struct name##Register \
    { \
        name##Register() \
        { \
            CModuleManager::Global()->RegisterModule(new name()); \
        } \
    } xx##name##Register;


struct CModuleInterface;

struct EIGHTGINECORE_API CModuleManager
{
    std::vector<CModuleInterface*> Modules;

    static CModuleManager* Global();

    void RegisterModule(CModuleInterface* module);
};

#endif // EIGHTGINECORE_CMODULE_MANAGER_HPP
