#ifndef EIGHTGINEPLATFORM_PPLATFORM_HPP
#define EIGHTGINEPLATFORM_PPLATFORM_HPP

#include <memory> // unique_ptr

#define EIGHTGINE_REGISTER_PLATFORM(tPlatformImplementationType) \
    struct tPlatformImplementationType##Register \
    { \
        tPlatformImplementationType##Register() \
        { \
            PPlatform::RegisterPlatform(new tPlatformImplementationType()); \
        } \
    } xx##tPlatformImplementationType##Register;


struct PModuleControllerInterface;
struct PFileSystemInterface;

struct EIGHTGINEPLATFORM_API PPlatform
{
    static std::unique_ptr<PModuleControllerInterface> ModuleController;
    static std::unique_ptr<PFileSystemInterface> FileSystem;

    static void RegisterPlatform(PModuleControllerInterface* implementation);
    static void RegisterPlatform(PFileSystemInterface* implementation);
};

#endif // EIGHTGINEPLATFORM_PLATFORM_HPP
