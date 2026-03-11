#ifndef ENGINE_PPHYSICS_MODULE_HPP
#define ENGINE_PPHYSICS_MODULE_HPP

#include <CModuleInterface.hpp>

struct EIGHTGINEPHYSICS_API PPhysicsModule : public CModuleInterface
{
    void StartupModule(CEngine const* pEngineContext) override;
    void ShutdownModule() override;
};

#endif // ENGINE_PPHYSICS_MODULE_HPP
