#ifndef ENGINE_OOBJECTS_MODULE_HPP
#define ENGINE_OOBJECTS_MODULE_HPP

#include <CModuleInterface.hpp>

struct EIGHTGINEOBJECTS_API OObjectsModule : public CModuleInterface
{
    void StartupModule(CEngine const* pEngineContext) override;
    void ShutdownModule() override;
};

#endif // ENGINE_OOBJECTS_MODULE_HPP
