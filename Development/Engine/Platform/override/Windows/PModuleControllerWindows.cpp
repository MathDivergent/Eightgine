#include <PPlatform.hpp>
#include <PModuleControllerInterface.hpp>

#include <windows.h> // LoadLibraryA, HMODULE, GetProcAddress, FreeLibrary

struct PModuleControllerWindows : public PModuleControllerInterface
{
    void* LoadModule(std::filesystem::path const& sModuleFilePathNoFileExtention) override;
    void* GetFunction(void* pModule, std::string const& sFunctionName) override;
    bool UnloadModule(void* pModule) override;
    std::optional<std::string> ExtractErrorMessage() override;
};

EIGHTGINE_REGISTER_PLATFORM(PModuleControllerWindows)


void* PModuleControllerWindows::LoadModule(std::filesystem::path const& sModuleFilePathNoFileExtention)
{
    std::filesystem::path sModuleFilePath = sModuleFilePathNoFileExtention;
    sModuleFilePath.replace_extension("dll");
    return (void*)LoadLibraryA(/*lpLibFileName*/sModuleFilePath.c_str());
}

void* PModuleControllerWindows::GetFunction(void* pModuleHandler, std::string const& sFunctionName)
{
    return (void*)GetProcAddress(/*hModule*/(HMODULE)pModuleHandler, /*lpProcName*/sFunctionName.c_str());
}

bool PModuleControllerWindows::UnloadModule(void* pModuleHandler)
{
    if (pModuleHandler == NULL)
    {
        return false;
    }
    else
    {
        return (bool)FreeLibrary(/*hLibModule*/(HMODULE)pModuleHandler);
    }
}

std::optional<std::string> PModuleControllerWindows::ExtractErrorMessage()
{
    if (DWORD const uErrorCode = GetLastError())
    {
        std::string sErrorMessage(512, '\0');
        DWORD const uMessageSize = FormatMessageA
        (
            /*dwFlags*/FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
            /*lpSource*/NULL,
            /*dwMessageId*/uErrorCode, /*dwLanguageId*/MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            /*lpBuffer*/sErrorMessage.data(), /*nSize*/(DWORD)sErrorMessage.size(),
            /*Arguments*/nullptr
        );

        if (uMessageSize == 0)
        {
            sErrorMessage = "UnknownError: " + std::to_string(uErrorCode);
        }
        else
        {
            sErrorMessage.resize(uMessageSize);
        }

        SetLastError(0);
        return sErrorMessage;
    }
    else
    {
        return std::nullopt;
    }
}