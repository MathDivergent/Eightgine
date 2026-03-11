#ifndef EIGHTGINECORE_CMODULE_MANAGER_HPP
#define EIGHTGINECORE_CMODULE_MANAGER_HPP

#include <vector> // vector
#include <memory> // unique_ptr

#define EIGHTGINE_REGISTER_MODULE(tModuleType) \
    struct tModuleType##Register \
    { \
        static CModuleInterface* tModuleType##ImplementationFactory() \
        { \
            return new tModuleType(); \
        } \
        tModuleType##Register() \
        { \
            CModuleManager::RegisterModule(&tModuleType##ImplementationFactory); \
        } \
    } xx##tModuleType##Register;


struct CModuleInterface;

struct EIGHTGINECORE_API CModuleManager
{
    static std::vector<std::unique_ptr<CModuleInterface>> RegisteredModules;

    static void RegisterModule(CModuleInterface* (*hModuleImplementationFactory)(void));
};

#endif // EIGHTGINECORE_CMODULE_MANAGER_HPP
