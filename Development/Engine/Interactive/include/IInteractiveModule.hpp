#ifndef ENGINE_IINTERACTIVE_MODULE_HPP
#define ENGINE_IINTERACTIVE_MODULE_HPP

#include <CModuleInterface.hpp>

struct EIGHTGINEINTERACTIVE_API IInteractiveModule : public CModuleInterface
{
    void StartupModule(CEngine const* pEngineContext) override;
    void ShutdownModule() override;
};

#endif // ENGINE_IINTERACTIVE_MODULE_HPP
