#ifndef GAME_GAME_MODULE_HPP
#define GAME_GAME_MODULE_HPP

#include <CModuleInterface.hpp>

struct GAME_API GameModule : public CModuleInterface
{
    void OnLoad() override;
    void OnProcess() override;
    void OnUnload() override;
};

#endif // GAME_GAME_MODULE_HPP
