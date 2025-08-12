#include <GameModule.hpp>

#include <CModuleRegistry.hpp>

#include <cstdio> // printf

EIGHTGINE_REGISTER_MODULE(GameModule)

void GameModule::OnLoad()
{
    printf("%s\n", "Hello, GameModule!");
}

void GameModule::OnProcess()
{
}

void GameModule::OnUnload()
{
}
