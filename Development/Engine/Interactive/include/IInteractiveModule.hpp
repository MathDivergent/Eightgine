#ifndef ENGINE_IINTERACTIVE_MODULE_HPP
#define ENGINE_IINTERACTIVE_MODULE_HPP

#include <CModuleInterface.hpp>

struct EIGHTGINEINTERACTIVE_API IInteractiveModule : public CModuleInterface
{
    void OnLoad() override;
    void OnProcess() override;
    void OnUnload() override;
};

#endif // ENGINE_IINTERACTIVE_MODULE_HPP
