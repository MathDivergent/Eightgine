#ifndef EIGHTGINEPLATFORM_WINDOWS_PFILE_SYSTEM_WINDOWS_HPP
#define EIGHTGINEPLATFORM_WINDOWS_PFILE_SYSTEM_WINDOWS_HPP

#include <PFileSystemInterface.hpp>

struct EIGHTGINEPLATFORM_API PFileSystemWindows : public PFileSystemInterface
{
    std::filesystem::path ProjectExecutableDir() override;
    std::filesystem::path ProjectPlugInsDir() override;
    std::filesystem::path ProjectResourcesDir() override;
};

#endif // EIGHTGINEPLATFORM_WINDOWS_PFILE_SYSTEM_WINDOWS_HPP
