#ifndef ENGINE_LLIGHTING_MODULE_HPP
#define ENGINE_LLIGHTING_MODULE_HPP

#include <CModuleInterface.hpp>

struct EIGHTGINELIGHTING_API LLightingModule : public CModuleInterface
{
    void StartupModule(CEngine const* pEngineContext) override;
    void ShutdownModule() override;
};

#endif // ENGINE_LLIGHTING_MODULE_HPP
