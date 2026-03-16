#ifndef ENGINE_PPARTICLES_MODULE_HPP
#define ENGINE_PPARTICLES_MODULE_HPP

#include <CModuleInterface.hpp>

struct EIGHTGINEPARTICLES_API PParticlesModule : public CModuleInterface
{
    void StartupModule(CEngine const* pEngineContext) override;
    void ShutdownModule() override;
};

#endif // ENGINE_PPARTICLES_MODULE_HPP
