#ifndef EIGHTGINEPLATFORM_PMODULE_CONTROLLER_INTERFACE_HPP
#define EIGHTGINEPLATFORM_PMODULE_CONTROLLER_INTERFACE_HPP

#include <string> // string
#include <filesystem> // filesystem::path
#include <optional> // optional

struct EIGHTGINEPLATFORM_API PModuleControllerInterface
{
    virtual ~PModuleControllerInterface() = default;

    virtual void* LoadModule(std::filesystem::path const& sModuleFilePathNoFileExtention) = 0;
    virtual void* GetFunction(void* pModuleHandler, std::string const& sFunctionName) = 0;
    virtual bool UnloadModule(void* pModuleHandler) = 0;
    virtual std::optional<std::string> ExtractErrorMessage() = 0;
};

#endif // EIGHTGINEPLATFORM_PMODULE_CONTROLLER_INTERFACE_HPP