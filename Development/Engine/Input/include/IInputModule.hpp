#ifndef ENGINE_IINPUT_MODULE_HPP
#define ENGINE_IINPUT_MODULE_HPP

#include <CModuleInterface.hpp>

struct EIGHTGINEINPUT_API IInputModule : public CModuleInterface
{
    void StartupModule(CEngine const* pEngineContext) override;
    void ShutdownModule() override;
};

#endif // ENGINE_IINPUT_MODULE_HPP
