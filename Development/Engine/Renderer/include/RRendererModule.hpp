#ifndef ENGINE_RRENDERER_MODULE_HPP
#define ENGINE_RRENDERER_MODULE_HPP

#include <CModuleInterface.hpp>

struct EIGHTGINERENDERER_API RRendererModule : public CModuleInterface
{
    void OnLoad() override;
    void OnProcess() override;
    void OnUnload() override;
};

#endif // ENGINE_RRENDERER_MODULE_HPP
