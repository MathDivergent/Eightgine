#ifndef ENGINE_NNETWORK_MODULE_HPP
#define ENGINE_NNETWORK_MODULE_HPP

#include <CModuleInterface.hpp>

struct EIGHTGINENETWORK_API NNetworkModule : public CModuleInterface
{
    void OnLoad() override;
    void OnProcess() override;
    void OnUnload() override;
};

#endif // ENGINE_NNETWORK_MODULE_HPP
