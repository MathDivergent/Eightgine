#ifndef EIGHTGINEPLATFORM_PMODULE_CONTROLLER_INTERFACE_HPP
#define EIGHTGINEPLATFORM_PMODULE_CONTROLLER_INTERFACE_HPP

#include <filesystem> // filesystem::path
#include <string> // string
#include <optional> // optional

struct EIGHTGINEPLATFORM_API PModuleControllerInterface
{
    virtual ~PModuleControllerInterface() = default;

    virtual void* LoadModule(std::filesystem::path const& sModuleFilePathNoFileExtention) = 0;
    virtual bool UnloadModule(void* pModuleHandle) = 0;

    virtual void* ModuleSymbol(void* pModuleHandle, std::string const& sSymbolName) = 0;
    virtual void* ModuleHandle(void* pModuleSymbol) = 0;

    virtual std::optional<std::string> ExtractError() = 0;
};

#endif // EIGHTGINEPLATFORM_PMODULE_CONTROLLER_INTERFACE_HPP
