#ifndef ENGINE_NNETWORK_MODULE_HPP
#define ENGINE_NNETWORK_MODULE_HPP

#include <CModuleInterface.hpp>

struct EIGHTGINENETWORK_API NNetworkModule : public CModuleInterface
{
    void StartupModule(CEngine const* pEngineContext) override;
    void ShutdownModule() override;
};

#endif // ENGINE_NNETWORK_MODULE_HPP
