#ifndef ENGINE_EEDITOR_MODULE_HPP
#define ENGINE_EEDITOR_MODULE_HPP

#include <CModuleInterface.hpp>

struct EIGHTGINEEDITOR_API EEditorModule : public CModuleInterface
{
    void StartupModule(CEngine const* pEngineContext) override;
    void ShutdownModule() override;
};

#endif // ENGINE_EEDITOR_MODULE_HPP
