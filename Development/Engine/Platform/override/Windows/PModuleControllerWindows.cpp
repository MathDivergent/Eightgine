#include <PPlatform.hpp>
#include <PModuleControllerInterface.hpp>

// LoadLibraryW, FreeLibrary, HMODULE, GetProcAddress, DWORD, FormatMessageA,
// FORMAT_MESSAGE_FROM_SYSTEM, FORMAT_MESSAGE_IGNORE_INSERTS, MAKELANGID, LANG_NEUTRAL, SUBLANG_DEFAULT, SetLastError
#include <windows.h>

struct PModuleControllerWindows : public PModuleControllerInterface
{
    void* LoadModule(std::filesystem::path const& sModuleFilePathNoFileExtention) override;
    bool UnloadModule(void* pModuleHandle) override;

    void* ModuleSymbol(void* pModuleHandle, std::string const& sSymbolName) override;
    void* ModuleHandle(void* pModuleSymbol) override;

    std::optional<std::string> ExtractError() override;
};

EIGHTGINE_REGISTER_PLATFORM(PModuleControllerWindows)


void* PModuleControllerWindows::LoadModule(std::filesystem::path const& sModuleFilePathNoFileExtention)
{
    std::filesystem::path sModuleFilePath = sModuleFilePathNoFileExtention;
    sModuleFilePath.replace_extension("dll");
    return (void*)LoadLibraryW(/*lpLibFileName*/sModuleFilePath.c_str());
}

bool PModuleControllerWindows::UnloadModule(void* pModuleHandle)
{
    if (pModuleHandle == NULL)
    {
        return false;
    }
    else
    {
        return (bool)FreeLibrary(/*hLibModule*/(HMODULE)pModuleHandle);
    }
}

void* PModuleControllerWindows::ModuleSymbol(void* pModuleHandle, std::string const& sSymbolName)
{
    return (void*)GetProcAddress(/*hModule*/(HMODULE)pModuleHandle, /*lpProcName*/sSymbolName.c_str());
}

void* PModuleControllerWindows::ModuleHandle(void* pModuleSymbol)
{
    HMODULE pModuleHandle = NULL;
    BOOL const bSuccess = GetModuleHandleEx
    (
        /*dwFlags*/GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
        /*lpModuleName*/(LPCSTR)&pModuleSymbol,
        /*phModule*/&pModuleHandle
    );

    return bSuccess ? pModuleHandle : NULL;
}

std::optional<std::string> PModuleControllerWindows::ExtractError()
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
