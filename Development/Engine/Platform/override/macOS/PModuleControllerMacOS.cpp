#include <PPlatform.hpp>
#include <PModuleControllerInterface.hpp>

#include <dlfcn.h> // dlopen, RTLD_NOW, dlsym, dlclose

struct PModuleControllerMacOS : public PModuleControllerInterface
{
    void* LoadModule(std::filesystem::path const& sModuleFilePathNoFileExtention) override;
    void* GetFunction(void* pModule, std::string const& sFunctionName) override;
    bool UnloadModule(void* pModule) override;
    std::optional<std::string> ExtractErrorMessage() override;
};

EIGHTGINE_REGISTER_PLATFORM(PModuleControllerMacOS)


void* PModuleControllerMacOS::LoadModule(std::filesystem::path const& sModuleFilePathNoFileExtention)
{
    std::filesystem::path sModuleFilePath = sModuleFilePathNoFileExtention;
    sModuleFilePath.replace_extension("dylib");
    return dlopen(/*filename*/sModuleFilePath.c_str(), /*flags*/RTLD_NOW);
}

void* PModuleControllerMacOS::GetFunction(void* pModuleHandler, std::string const& sFunctionName)
{
    return dlsym(/*handle*/pModuleHandler, /*symbol*/sFunctionName.c_str());
}

bool PModuleControllerMacOS::UnloadModule(void* pModuleHandler)
{
    if (pModuleHandler == NULL)
    {
        return false;
    }
    else
    {
        return dlclose(/*handle*/pModuleHandler) == 0;
    }
}

std::optional<std::string> PModuleControllerMacOS::ExtractErrorMessage()
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