#ifndef EIGHTGINECORE_CMODULE_INTERFACE_HPP
#define EIGHTGINECORE_CMODULE_INTERFACE_HPP

#include <string> // string

struct CEngine;

struct EIGHTGINECORE_API CModuleInterface
{
    std::string sModuleName;
    void* pModuleHandle = nullptr;

    virtual ~CModuleInterface() = default;

    virtual void StartupModule(CEngine const* pEngineContext) = 0;
    virtual void ShutdownModule() = 0;
};

#endif // EIGHTGINECORE_CMODULE_INTERFACE_HPP
