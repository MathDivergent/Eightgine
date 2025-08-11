#include <PFileSystemLinux.hpp>
#include <PPlatform.hpp>

#include <string> // string, strlen

#include <unistd.h> // PATH_MAX, ssize_t, readlink
#include <stdlib.h> // realpath

EIGHTGINE_REGISTRY_PLATFORM(FileSystem, PFileSystemLinux)


std::filesystem::path PFileSystemLinux::ProjectExecutableDir()
{
    std::string sExecutablePathBuffer(PATH_MAX, '\0');

    ssize_t iExecutablePathLength = readlink(/*pathname*/"/proc/self/exe", /*buf*/sExecutablePathBuffer.data(), /*bufsiz*/sExecutablePathBuffer.size());
    if (iExecutablePathLength == -1)
    {
        return {};
    }

    sExecutablePathBuffer.resize((std::size_t)iExecutablePathLength);

    std::string sRealExecutablePathBuffer(PATH_MAX, '\0');
    if (realpath(/*path*/sExecutablePathBuffer.c_str(), /*resolved_path*/sRealExecutablePathBuffer.data()) == NULL)
    {
        return {};
    }

    std::size_t uRealExecutablePathLength = std::strlen(sRealExecutablePathBuffer.c_str());
    sRealExecutablePathBuffer.resize(uRealExecutablePathLength);
    return std::filesystem::path(sRealExecutablePathBuffer).parent_path();
}

std::filesystem::path PFileSystemLinux::ProjectPlugInsDir()
{
    return ProjectExecutableDir().parent_path() / "PlugIns";
}

std::filesystem::path PFileSystemLinux::ProjectResourcesDir()
{
    return ProjectExecutableDir().parent_path() / "Resources";
}
