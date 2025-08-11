#ifndef EIGHTGINECORE_PLATFORM_HPP
#define EIGHTGINECORE_PLATFORM_HPP

#include <filesystem> // filesystem

struct EIGHTGINECORE_API CFileSystemInterface
{
    virtual ~CFileSystemInterface() = default;

    virtual std::filesystem::path ProjectExecutableDir() = 0;
    virtual std::filesystem::path ProjectPlugInsDir() = 0;
    virtual std::filesystem::path ProjectResourcesDir() = 0;
};

struct EIGHTGINECORE_API CPlatform
{
    static CFileSystemInterface* FileSystem;
};

#endif // EIGHTGINECORE_PLATFORM_HPP
