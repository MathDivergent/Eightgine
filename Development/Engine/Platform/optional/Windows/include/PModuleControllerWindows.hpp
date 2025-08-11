#ifndef EIGHTGINEPLATFORM_WINDOWS_PMODULE_CONTROLLER_WINDOWS_HPP
#define EIGHTGINEPLATFORM_WINDOWS_PMODULE_CONTROLLER_WINDOWS_HPP

#include <PModuleControllerInterface.hpp>

struct EIGHTGINEPLATFORM_API PModuleControllerWindows : public PModuleControllerInterface
{
    void* LoadModule(std::string const& sModuleName) override;
    void* GetFunction(void* pModule, std::string const& sFunctionName) override;
    bool UnloadModule(void* pModule) override;
};

#endif // EIGHTGINEPLATFORM_WINDOWS_PMODULE_CONTROLLER_WINDOWS_HPP
