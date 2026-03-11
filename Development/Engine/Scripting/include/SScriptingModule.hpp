#ifndef ENGINE_SSCRIPTING_MODULE_HPP
#define ENGINE_SSCRIPTING_MODULE_HPP

#include <CModuleInterface.hpp>

struct EIGHTGINESCRIPTING_API SScriptingModule : public CModuleInterface
{
    void StartupModule(CEngine const* pEngineContext) override;
    void ShutdownModule() override;
};

#endif // ENGINE_SSCRIPTING_MODULE_HPP
