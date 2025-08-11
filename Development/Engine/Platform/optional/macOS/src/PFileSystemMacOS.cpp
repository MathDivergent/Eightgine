#include <PFileSystemMacOS.hpp>
#include <PPlatform.hpp>

#include <string> // string, strlen

#include <mach-o/dyld.h> // PATH_MAX, uint32_t, _NSGetExecutablePath
#include <stdlib.h> // realpath

EIGHTGINE_REGISTRY_PLATFORM(FileSystem, PFileSystemMacOS)


std::filesystem::path PFileSystemMacOS::ProjectExecutableDir()
{
    std::string sExecutablePathBuffer(PATH_MAX, '\0');
    uint32_t uExecutablePathLength = (uint32_t)sExecutablePathBuffer.size();

    if (_NSGetExecutablePath(/*buf*/sExecutablePathBuffer.data(), /*bufsize*/&uExecutablePathLength) == -1)
    {
        return {};
    }

    sExecutablePathBuffer.resize((std::size_t)uExecutablePathLength);

    std::string sRealExecutablePathBuffer(PATH_MAX, '\0');
    if (realpath(/*path*/sExecutablePathBuffer.c_str(), /*resolved_path*/sRealExecutablePathBuffer.data()) == NULL)
    {
        return {};
    }

    std::size_t uRealExecutablePathLength = std::strlen(sRealExecutablePathBuffer.c_str());
    sRealExecutablePathBuffer.resize(uRealExecutablePathLength);
    return std::filesystem::path(sRealExecutablePathBuffer).parent_path();
}

std::filesystem::path PFileSystemMacOS::ProjectPlugInsDir()
{
    return ProjectExecutableDir().parent_path() / "PlugIns";
}

std::filesystem::path PFileSystemMacOS::ProjectResourcesDir()
{
    return ProjectExecutableDir().parent_path() / "Resources";
}
