#include <PPlatform.hpp>

#include <PModuleControllerInterface.hpp>
#include <PFileSystemInterface.hpp>

std::unique_ptr<PModuleControllerInterface> PPlatform::pModuleController;
std::unique_ptr<PFileSystemInterface> PPlatform::pFileSystem;

void PPlatform::RegisterPlatform(PModuleControllerInterface* implementation)
{
    pModuleController.reset(implementation);
}

void PPlatform::RegisterPlatform(PFileSystemInterface* implementation)
{
    pFileSystem.reset(implementation);
}
