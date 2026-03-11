#include <PPlatform.hpp>

#include <PModuleControllerInterface.hpp>
#include <PFileSystemInterface.hpp>

std::unique_ptr<PModuleControllerInterface> PPlatform::ModuleController;
std::unique_ptr<PFileSystemInterface> PPlatform::FileSystem;

void PPlatform::RegisterPlatform(PModuleControllerInterface* implementation)
{
    ModuleController.reset(implementation);
}

void PPlatform::RegisterPlatform(PFileSystemInterface* implementation)
{
    FileSystem.reset(implementation);
}