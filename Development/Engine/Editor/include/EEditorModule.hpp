#ifndef ENGINE_EEDITOR_MODULE_HPP
#define ENGINE_EEDITOR_MODULE_HPP

#include <CModuleInterface.hpp>

struct EIGHTGINEEDITOR_API EEditorModule : public CModuleInterface
{
    void OnLoad() override;
    void OnProcess() override;
    void OnUnload() override;
};

#endif // ENGINE_EEDITOR_MODULE_HPP
