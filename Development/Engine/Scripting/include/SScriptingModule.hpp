#ifndef ENGINE_SSCRIPTING_MODULE_HPP
#define ENGINE_SSCRIPTING_MODULE_HPP

#include <CModuleInterface.hpp>

struct EIGHTGINESCRIPTING_API SScriptingModule : public CModuleInterface
{
    void OnLoad() override;
    void OnProcess() override;
    void OnUnload() override;
};

#endif // ENGINE_SSCRIPTING_MODULE_HPP
