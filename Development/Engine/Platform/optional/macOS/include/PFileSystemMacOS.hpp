#ifndef EIGHTGINEPLATFORM_MACOS_PFILE_SYSTEM_MACOS_HPP
#define EIGHTGINEPLATFORM_MACOS_PFILE_SYSTEM_MACOS_HPP

#include <PFileSystemInterface.hpp>

struct EIGHTGINEPLATFORM_API PFileSystemMacOS : public PFileSystemInterface
{
    std::filesystem::path ProjectExecutableDir() override;
    std::filesystem::path ProjectPlugInsDir() override;
    std::filesystem::path ProjectResourcesDir() override;
};

#endif // EIGHTGINEPLATFORM_MACOS_PFILE_SYSTEM_MACOS_HPP
