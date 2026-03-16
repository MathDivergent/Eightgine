#ifndef EIGHTGINECORE_CMODULE_MANAGER_HPP
#define EIGHTGINECORE_CMODULE_MANAGER_HPP

#include <string_view> // string_view
#include <list> // list
#include <memory> // unique_ptr

#define EIGHTGINE_MODULE_FACTORY(tModuleType) \
    extern "C" EIGHTGINE_API CModuleInterface* ModuleFactory() \
    { \
        return new tModuleType; \
    }

struct CModuleInterface;

struct EIGHTGINECORE_API CModuleManager
{
    using ModuleFactoryH = CModuleInterface* (*)(void);

    static constexpr std::string_view sModuleFactoryFunctionName = "ModuleFactory";
    static std::list<std::unique_ptr<CModuleInterface>> cModules;
};

#endif // EIGHTGINECORE_CMODULE_MANAGER_HPP
