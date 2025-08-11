#ifndef EIGHTGINEPLATFORMWINDOWS_FILE_SYSTEM_WINDOWS_HPP
#define EIGHTGINEPLATFORMWINDOWS_FILE_SYSTEM_WINDOWS_HPP

#include <Platform.hpp>

struct EIGHTGINEPLATFORMWINDOWS_API CFileSystemWindows : public CFileSystemInterface
{
    std::filesystem::path ProjectExecutableDir() override;
    std::filesystem::path ProjectPlugInsDir() override;
    std::filesystem::path ProjectResourcesDir() override;
};

#endif // EIGHTGINEPLATFORMWINDOWS_FILE_SYSTEM_WINDOWS_HPP
