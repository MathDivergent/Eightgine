#ifndef ENGINE_IINPUT_MODULE_HPP
#define ENGINE_IINPUT_MODULE_HPP

#include <CModuleInterface.hpp>

struct EIGHTGINEINPUT_API IInputModule : public CModuleInterface
{
    void OnLoad() override;
    void OnProcess() override;
    void OnUnload() override;
};

#endif // ENGINE_IINPUT_MODULE_HPP
