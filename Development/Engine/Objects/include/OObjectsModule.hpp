#ifndef ENGINE_OOBJECTS_MODULE_HPP
#define ENGINE_OOBJECTS_MODULE_HPP

#include <CModuleInterface.hpp>

struct EIGHTGINEOBJECTS_API OObjectsModule : public CModuleInterface
{
    void OnLoad() override;
    void OnProcess() override;
    void OnUnload() override;
};

#endif // ENGINE_OOBJECTS_MODULE_HPP
