#ifndef ENGINE_LLIGHTING_MODULE_HPP
#define ENGINE_LLIGHTING_MODULE_HPP

#include <CModuleInterface.hpp>

struct EIGHTGINELIGHTING_API LLightingModule : public CModuleInterface
{
    void OnLoad() override;
    void OnProcess() override;
    void OnUnload() override;
};

#endif // ENGINE_LLIGHTING_MODULE_HPP
