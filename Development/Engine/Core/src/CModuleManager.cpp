#include <CModuleManager.hpp>
#include <CModuleInterface.hpp>

#include <PPlatform.hpp>
#include <PModuleControllerInterface.hpp>

std::vector<std::unique_ptr<CModuleInterface>> CModuleManager::RegisteredModules;

void CModuleManager::RegisterModule(CModuleInterface* (*hModuleImplementationFactory)(void))
{
    if (hModuleImplementationFactory == nullptr)
    {
        return;
    }

    CModuleInterface* pModuleImplementation = hModuleImplementationFactory();
    pModuleImplementation->ModuleHandle = PPlatform::ModuleController->ModuleHandle((void*)hModuleImplementationFactory);

    RegisteredModules.emplace_back(pModuleImplementation);
}
