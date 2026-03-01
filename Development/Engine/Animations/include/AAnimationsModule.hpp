#ifndef ENGINE_AANIMATIONS_MODULE_HPP
#define ENGINE_AANIMATIONS_MODULE_HPP

#include <CModuleInterface.hpp>

struct EIGHTGINEANIMATIONS_API AAnimationsModule : public CModuleInterface
{
    void OnLoad() override;
    void OnProcess() override;
    void OnUnload() override;
};

#endif // ENGINE_AANIMATIONS_MODULE_HPP
