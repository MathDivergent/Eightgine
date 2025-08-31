#include <PPlatform.hpp>
#include <PFileSystemInterface.hpp>

#include <string> // string
#include <cstring> // strlen

#include <limits.h> // PATH_MAX
#include <stdlib.h> // realpath
#include <unistd.h> // ssize_t, readlink

struct PFileSystemLinux : public PFileSystemInterface
{
    std::filesystem::path ProjectExecutableDir() override;
    std::filesystem::path ProjectPlugInsDir() override;
    std::filesystem::path ProjectResourcesDir() override;
};

EIGHTGINE_REGISTER_PLATFORM(FileSystem, PFileSystemLinux)


std::filesystem::path PFileSystemLinux::ProjectExecutableDir()
{
    std::string sExecutablePathBuffer(PATH_MAX, '\0');

    ssize_t iExecutablePathLength = readlink(/*pathname*/"/proc/self/exe", /*buf*/sExecutablePathBuffer.data(), /*bufsiz*/sExecutablePathBuffer.size());
    if (iExecutablePathLength == -1)
    {
        return {};
    }

    sExecutablePathBuffer.resize((std::size_t)iExecutablePathLength); // shrink

    std::string sRealExecutablePathBuffer(PATH_MAX, '\0');
    if (realpath(/*path*/sExecutablePathBuffer.c_str(), /*resolved_path*/sRealExecutablePathBuffer.data()) == NULL)
    {
        return {};
    }

    std::size_t uRealExecutablePathLength = std::strlen(sRealExecutablePathBuffer.c_str());
    sRealExecutablePathBuffer.resize(uRealExecutablePathLength); // shrink
    return std::filesystem::path(sRealExecutablePathBuffer).parent_path();
}

std::filesystem::path PFileSystemLinux::ProjectPlugInsDir()
{
    return ProjectExecutableDir().parent_path() / EIGHTGINE_PLUGINS_DIR_NAME;
}

std::filesystem::path PFileSystemLinux::ProjectResourcesDir()
{
    return ProjectExecutableDir().parent_path() / EIGHTGINE_RESOURCES_DIR_NAME;
}
