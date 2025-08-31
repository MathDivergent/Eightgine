#include <PPlatform.hpp>
#include <PFileSystemInterface.hpp>

#include <string> // string
#include <cstring> // strlen

#include <limits.h> // PATH_MAX
#include <stdlib.h> // realpath
#include <mach-o/dyld.h> // uint32_t, _NSGetExecutablePath

struct PFileSystemMacOS : public PFileSystemInterface
{
    std::filesystem::path ProjectExecutableDir() override;
    std::filesystem::path ProjectPlugInsDir() override;
    std::filesystem::path ProjectResourcesDir() override;
};

EIGHTGINE_REGISTER_PLATFORM(FileSystem, PFileSystemMacOS)


std::filesystem::path PFileSystemMacOS::ProjectExecutableDir()
{
    std::string sExecutablePathBuffer(PATH_MAX, '\0');
    uint32_t uExecutablePathLength = (uint32_t)sExecutablePathBuffer.size();

    if (_NSGetExecutablePath(/*buf*/sExecutablePathBuffer.data(), /*bufsize*/&uExecutablePathLength) == -1)
    {
        return {};
    }

    sExecutablePathBuffer.resize((std::size_t)uExecutablePathLength); // shrink

    std::string sRealExecutablePathBuffer(PATH_MAX, '\0');
    if (realpath(/*path*/sExecutablePathBuffer.c_str(), /*resolved_path*/sRealExecutablePathBuffer.data()) == NULL)
    {
        return {};
    }

    std::size_t uRealExecutablePathLength = std::strlen(sRealExecutablePathBuffer.c_str());
    sRealExecutablePathBuffer.resize(uRealExecutablePathLength); // shrink
    return std::filesystem::path(sRealExecutablePathBuffer).parent_path();
}

std::filesystem::path PFileSystemMacOS::ProjectPlugInsDir()
{
    return ProjectExecutableDir().parent_path() / EIGHTGINE_PLUGINS_DIR_NAME;
}

std::filesystem::path PFileSystemMacOS::ProjectResourcesDir()
{
    return ProjectExecutableDir().parent_path() / EIGHTGINE_RESOURCES_DIR_NAME;
}
