#ifndef ENGINE_RRENDERER_MODULE_HPP
#define ENGINE_RRENDERER_MODULE_HPP

#include <CModuleInterface.hpp>

struct EIGHTGINERENDERER_API RRendererModule : public CModuleInterface
{
    void StartupModule(CEngine const* pEngineContext) override;
    void ShutdownModule() override;
};

#endif // ENGINE_RRENDERER_MODULE_HPP
