#include <PPlatform.hpp>
#include <PModuleControllerInterface.hpp>

#include <dlfcn.h> // dlopen, RTLD_NOW, dlclose, dlsym, Dl_info, dladdr, RTLD_NOLOAD, dlerror

struct PModuleControllerLinux : public PModuleControllerInterface
{
    void* LoadModule(std::filesystem::path const& sModuleFilePathNoFileExtention) override;
    bool UnloadModule(void* pModuleHandle) override;

    void* ModuleSymbol(void* pModuleHandle, std::string const& sSymbolName) override;
    void* ModuleHandle(void* pModuleSymbol) override;

    std::optional<std::string> ExtractError() override;
};

EIGHTGINE_REGISTER_PLATFORM(PModuleControllerLinux)


void* PModuleControllerLinux::LoadModule(std::filesystem::path const& sModuleFilePathNoFileExtention)
{
    std::filesystem::path sModuleFilePath = sModuleFilePathNoFileExtention;
    sModuleFilePath.replace_extension("so");
    return dlopen(/*filename*/sModuleFilePath.c_str(), /*flags*/RTLD_NOW);
}

bool PModuleControllerLinux::UnloadModule(void* pModuleHandle)
{
    if (pModuleHandle == NULL)
    {
        return false;
    }
    else
    {
        return dlclose(/*handle*/pModuleHandle) == 0;
    }
}

void* PModuleControllerLinux::ModuleSymbol(void* pModuleHandle, std::string const& sSymbolName)
{
    return dlsym(/*handle*/pModuleHandle, /*symbol*/sSymbolName.c_str());
}

void* PModuleControllerLinux::ModuleHandle(void* pModuleSymbol)
{
    Dl_info aInfo;
    if (!dladdr(/*addr*/pModuleSymbol, /*info*/&aInfo))
    {
        return NULL;
    }
    else
    {
        return dlopen(/*filename*/aInfo.dli_fname, /*flags*/RTLD_NOLOAD);
    } 
}

std::optional<std::string> PModuleControllerLinux::ExtractError()
{
    if (char const* pExtractedLastError = dlerror())
    {
        return std::string(pExtractedLastError);
    }
    else
    {
        return std::nullopt;
    }
}