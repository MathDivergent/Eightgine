#include <PPlatform.hpp>
#include <PFileSystemInterface.hpp>

#include <windows.h> // MAX_PATH, DWORD, GetModuleFileNameW

struct PFileSystemWindows : public PFileSystemInterface
{
    std::filesystem::path ProjectExecutableDir() override;
    std::filesystem::path ProjectPlugInsDir() override;
    std::filesystem::path ProjectResourcesDir() override;
};

EIGHTGINE_REGISTER_PLATFORM(FileSystem, PFileSystemWindows)


std::filesystem::path PFileSystemWindows::ProjectExecutableDir()
{
    std::wstring sExecutablePathBuffer(MAX_PATH, L'\0');

    DWORD const uExecutablePathLength = GetModuleFileNameW(/*hModule*/NULL, /*lpFilename*/sExecutablePathBuffer.data(), /*nSize*/(DWORD)sExecutablePathBuffer.size());
    if (uExecutablePathLength == 0)
    {
        return {};
    }

    sExecutablePathBuffer.resize((std::size_t)uExecutablePathLength); // shrink
    return std::filesystem::path(sExecutablePathBuffer).parent_path();
}

std::filesystem::path PFileSystemWindows::ProjectPlugInsDir()
{
    return ProjectExecutableDir().parent_path() / EIGHTGINE_PLUGINS_DIR_NAME;
}

std::filesystem::path PFileSystemWindows::ProjectResourcesDir()
{
    return ProjectExecutableDir().parent_path() / EIGHTGINE_RESOURCES_DIR_NAME;
}
