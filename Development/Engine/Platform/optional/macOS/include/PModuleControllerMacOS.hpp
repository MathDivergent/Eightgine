#ifndef EIGHTGINEPLATFORM_MACOS_PMODULE_CONTROLLER_MACOS_HPP
#define EIGHTGINEPLATFORM_MACOS_PMODULE_CONTROLLER_MACOS_HPP

#include <PModuleControllerInterface.hpp>

struct EIGHTGINEPLATFORM_API PModuleControllerWindows : public PModuleControllerInterface
{
    void* LoadModule(std::string const& sModuleName) override;
    void* GetFunction(void* pModule, std::string const& sFunctionName) override;
    bool UnloadModule(void* pModule) override;
};

#endif // EIGHTGINEPLATFORM_MACOS_PMODULE_CONTROLLER_MACOS_HPP
