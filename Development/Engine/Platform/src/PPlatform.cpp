#include <PPlatform.hpp>

PPlatform* PPlatform::Global()
{
    static PPlatform self; return &self;
}

void PPlatform::RegisterPlatform(PModuleControllerInterface* implementation)
{
    ModuleController = implementation;
}

void PPlatform::RegisterPlatform(PFileSystemInterface* implementation)
{
    FileSystem = implementation;
}