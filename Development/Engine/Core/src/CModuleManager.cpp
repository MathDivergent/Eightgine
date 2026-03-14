#include <CModuleManager.hpp>
#include <CModuleInterface.hpp>

std::list<std::unique_ptr<CModuleInterface>> CModuleManager::cModules;
