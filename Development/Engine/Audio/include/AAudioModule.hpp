#ifndef ENGINE_AAUDIO_MODULE_HPP
#define ENGINE_AAUDIO_MODULE_HPP

#include <CModuleInterface.hpp>

struct EIGHTGINEAUDIO_API AAudioModule : public CModuleInterface
{
    void StartupModule(CEngine const* pEngineContext) override;
    void ShutdownModule() override;
};

#endif // ENGINE_AAUDIO_MODULE_HPP
