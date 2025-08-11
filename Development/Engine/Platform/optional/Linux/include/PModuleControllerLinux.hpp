#ifndef EIGHTGINEPLATFORM_LINUX_PMODULE_CONTROLLER_LINUX_HPP
#define EIGHTGINEPLATFORM_LINUX_PMODULE_CONTROLLER_LINUX_HPP

#include <PModuleControllerInterface.hpp>

struct EIGHTGINEPLATFORM_API PModuleControllerLinux : public PModuleControllerInterface
{
    void* LoadModule(std::string const& sModuleName) override;
    void* GetFunction(void* pModule, std::string const& sFunctionName) override;
    bool UnloadModule(void* pModule) override;
};

#endif // EIGHTGINEPLATFORM_LINUX_PMODULE_CONTROLLER_LINUX_HPP
