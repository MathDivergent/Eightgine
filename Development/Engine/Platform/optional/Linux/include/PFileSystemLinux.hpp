#ifndef EIGHTGINEPLATFORM_LINUX_PFILE_SYSTEM_LINUX_HPP
#define EIGHTGINEPLATFORM_LINUX_PFILE_SYSTEM_LINUX_HPP

#include <PFileSystemInterface.hpp>

struct EIGHTGINEPLATFORM_API PFileSystemLinux : public PFileSystemInterface
{
    std::filesystem::path ProjectExecutableDir() override;
    std::filesystem::path ProjectPlugInsDir() override;
    std::filesystem::path ProjectResourcesDir() override;
};

#endif // EIGHTGINEPLATFORM_LINUX_PFILE_SYSTEM_LINUX_HPP
