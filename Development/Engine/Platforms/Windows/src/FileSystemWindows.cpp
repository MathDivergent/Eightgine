#include <FileSystemWindows.hpp>

#include <string> // wstring
#include <filesystem> // filesystem

#include <windows.h> // GetModuleFileNameW, MAX_PATH

std::filesystem::path CFileSystemWindows::ProjectExecutableDir()
{
    std::wstring sExecutablePathBuffer(MAX_PATH, L'\0');

    DWORD const iExecutablePathLength = GetModuleFileNameW
    (
        nullptr, // hModule
        sExecutablePathBuffer.data(), // lpFilename
        MAX_PATH // nSize
    );

    sExecutablePathBuffer.resize(iExecutablePathLength); // shrink

    return std::filesystem::absolute(sExecutablePathBuffer);
}

std::filesystem::path CFileSystemWindows::ProjectPlugInsDir()
{
    return ProjectExecutableDir().parent_path() / L"PlugIns";
}

std::filesystem::path CFileSystemWindows::ProjectResourcesDir()
{
    return ProjectExecutableDir().parent_path() / L"Resources";
}
