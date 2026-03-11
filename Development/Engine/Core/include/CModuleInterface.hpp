#ifndef EIGHTGINECORE_CMODULE_INTERFACE_HPP
#define EIGHTGINECORE_CMODULE_INTERFACE_HPP

struct CEngine;

struct EIGHTGINECORE_API CModuleInterface
{
    virtual ~CModuleInterface() = default;

    virtual void StartupModule(CEngine const* pEngineContext) = 0;
    virtual void ShutdownModule() = 0;

    void* ModuleHandle = nullptr;
};

#endif // EIGHTGINECORE_CMODULE_INTERFACE_HPP
