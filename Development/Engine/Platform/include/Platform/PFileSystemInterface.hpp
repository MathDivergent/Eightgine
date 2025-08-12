#ifndef EIGHTGINEPLATFORM_PFILE_SYSTEM_HPP
#define EIGHTGINEPLATFORM_PFILE_SYSTEM_HPP

#include <filesystem> // filesystem

struct EIGHTGINEPLATFORM_API PFileSystemInterface
{
    virtual ~PFileSystemInterface() = default;

    virtual std::filesystem::path ProjectExecutableDir() = 0;
    virtual std::filesystem::path ProjectPlugInsDir() = 0;
    virtual std::filesystem::path ProjectResourcesDir() = 0;
};

#endif // EIGHTGINEPLATFORM_PFILE_SYSTEM_HPP
