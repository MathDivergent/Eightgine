#ifndef ENGINE_AANIMATIONS_MODULE_HPP
#define ENGINE_AANIMATIONS_MODULE_HPP

#include <CModuleInterface.hpp>

struct EIGHTGINEANIMATIONS_API AAnimationsModule : public CModuleInterface
{
    void StartupModule(CEngine const* pEngineContext) override;
    void ShutdownModule() override;
};

#endif // ENGINE_AANIMATIONS_MODULE_HPP
