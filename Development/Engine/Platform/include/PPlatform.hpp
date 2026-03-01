#ifndef EIGHTGINEPLATFORM_PPLATFORM_HPP
#define EIGHTGINEPLATFORM_PPLATFORM_HPP

#define EIGHTGINE_REGISTER_PLATFORM(tPlatformImplementationType) \
    struct tPlatformImplementationType##Register \
    { \
        tPlatformImplementationType##Register() \
        { \
            PPlatform::Global()->RegisterPlatform(new tPlatformImplementationType()); \
        } \
    } xx##tPlatformImplementationType##Register;


struct PModuleControllerInterface;
struct PFileSystemInterface;

struct EIGHTGINEPLATFORM_API PPlatform
{
    PModuleControllerInterface* ModuleController = nullptr;
    PFileSystemInterface* FileSystem = nullptr;

    static PPlatform* Global();

    void RegisterPlatform(PModuleControllerInterface* implementation);
    void RegisterPlatform(PFileSystemInterface* implementation);
};

#endif // EIGHTGINEPLATFORM_PLATFORM_HPP
