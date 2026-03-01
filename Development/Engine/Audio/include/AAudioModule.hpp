#ifndef ENGINE_AAUDIO_MODULE_HPP
#define ENGINE_AAUDIO_MODULE_HPP

#include <CModuleInterface.hpp>

struct EIGHTGINEAUDIO_API AAudioModule : public CModuleInterface
{
    void OnLoad() override;
    void OnProcess() override;
    void OnUnload() override;
};

#endif // ENGINE_AAUDIO_MODULE_HPP
