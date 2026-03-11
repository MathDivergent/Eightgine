#ifndef GAME_GAME_MODULE_HPP
#define GAME_GAME_MODULE_HPP

#include <CModuleInterface.hpp>

struct GAME_API GameModule : public CModuleInterface
{
    void StartupModule(CEngine const* pEngineContext) override;
    void ShutdownModule() override;
};

#endif // GAME_GAME_MODULE_HPP
