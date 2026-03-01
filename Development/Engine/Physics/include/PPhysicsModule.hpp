#ifndef ENGINE_PPHYSICS_MODULE_HPP
#define ENGINE_PPHYSICS_MODULE_HPP

#include <CModuleInterface.hpp>

struct EIGHTGINEPHYSICS_API PPhysicsModule : public CModuleInterface
{
    void OnLoad() override;
    void OnProcess() override;
    void OnUnload() override;
};

#endif // ENGINE_PPHYSICS_MODULE_HPP
