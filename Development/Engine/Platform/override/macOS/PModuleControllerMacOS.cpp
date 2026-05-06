#include <PPlatform.hpp>
#include <PModuleControllerInterface.hpp>

#include <dlfcn.h> // dlopen, RTLD_NOW, dlclose, dlsym, Dl_info, dladdr, RTLD_NOLOAD, dlerror

struct PModuleControllerMacOS : public PModuleControllerInterface
{
    void* LoadModule(std::filesystem::path const& sModuleFilePathNoFileExtension) override;
    bool UnloadModule(void* pModuleHandle) override;

    void* ModuleSymbol(void* pModuleHandle, std::string const& sSymbolName) override;
    void* ModuleHandle(void* pModuleSymbol) override;

    std::optional<std::string> ExtractError() override;
};

EIGHTGINE_REGISTER_PLATFORM(PModuleControllerMacOS)


void* PModuleControllerMacOS::LoadModule(std::filesystem::path const& sModuleFilePathNoFileExtension)
{
    std::filesystem::path sModuleFilePath = sModuleFilePathNoFileExtension;
    sModuleFilePath.replace_extension("dylib");
    return dlopen(/*filename*/sModuleFilePath.c_str(), /*flags*/RTLD_NOW);
}

bool PModuleControllerMacOS::UnloadModule(void* pModuleHandle)
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

void* PModuleControllerMacOS::ModuleSymbol(void* pModuleHandle, std::string const& sSymbolName)
{
    return dlsym(/*handle*/pModuleHandle, /*symbol*/sSymbolName.c_str());
}

void* PModuleControllerMacOS::ModuleHandle(void* pModuleSymbol)
{
    Dl_info aInfo;
    if (!dladdr(/*addr*/pModuleSymbol, /*info*/&aInfo))
    {
        return NULL;
    }
    else
    {
        void* const pModuleHandle = dlopen(/*filename*/aInfo.dli_fname, /*flags*/RTLD_NOW | RTLD_NOLOAD);
        UnloadModule(pModuleHandle);
        return pModuleHandle;
    }
}

std::optional<std::string> PModuleControllerMacOS::ExtractError()
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
