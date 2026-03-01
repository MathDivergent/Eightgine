#ifndef EIGHTGINECORE_CMODULE_MANAGER_HPP
#define EIGHTGINECORE_CMODULE_MANAGER_HPP

#include <vector> // vector

#define EIGHTGINE_REGISTER_MODULE(tModuleType) \
    struct tModuleType##Register \
    { \
        tModuleType##Register() \
        { \
            CModuleManager::Global()->RegisterModule(new tModuleType()); \
        } \
    } xx##tModuleType##Register;


struct CModuleInterface;

struct EIGHTGINECORE_API CModuleManager
{
    std::vector<CModuleInterface*> RegisteredModules;

    static CModuleManager* Global();

    void RegisterModule(CModuleInterface* pModuleImplementation);
};

#endif // EIGHTGINECORE_CMODULE_MANAGER_HPP
