#ifndef ENGINE_PPARTICLES_MODULE_HPP
#define ENGINE_PPARTICLES_MODULE_HPP

#include <CModuleInterface.hpp>

struct EIGHTGINEPARTICLES_API PParticlesModule : public CModuleInterface
{
    void OnLoad() override;
    void OnProcess() override;
    void OnUnload() override;
};

#endif // ENGINE_PPARTICLES_MODULE_HPP
