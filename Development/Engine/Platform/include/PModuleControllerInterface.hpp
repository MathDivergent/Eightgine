#ifndef EIGHTGINEPLATFORM_PMODULE_CONTROLLER_INTERFACE_HPP
#define EIGHTGINEPLATFORM_PMODULE_CONTROLLER_INTERFACE_HPP

#include <string> // string

struct EIGHTGINEPLATFORM_API PModuleControllerInterface
{
    virtual ~PModuleControllerInterface() = default;

    virtual void* LoadModule(std::string const& sModuleName) = 0;
    virtual void* GetFunction(void* pModuleHandler, std::string const& sFunctionName) = 0;
    virtual bool UnloadModule(void* pModuleHandler) = 0;
};

#endif // EIGHTGINEPLATFORM_PMODULE_CONTROLLER_INTERFACE_HPP