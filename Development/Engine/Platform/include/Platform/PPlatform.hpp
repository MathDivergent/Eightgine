#ifndef EIGHTGINEPLATFORM_PPLATFORM_HPP
#define EIGHTGINEPLATFORM_PPLATFORM_HPP

#include <string> // string
#include <filesystem> // filesystem

#define EIGHTGINE_REGISTER_PLATFORM(interface, name) \
    static struct name##Register \
    { \
        name##Register() \
        { \
            PPlatform::Global()->interface = new name(); \
        } \
    } xx##name##Register;


struct PModuleControllerInterface;
struct PFileSystemInterface;

struct EIGHTGINEPLATFORM_API PPlatform
{
    PModuleControllerInterface* ModuleController = nullptr;
    PFileSystemInterface* FileSystem = nullptr;

    static PPlatform* Global();
};

#endif // EIGHTGINEPLATFORM_PLATFORM_HPP
