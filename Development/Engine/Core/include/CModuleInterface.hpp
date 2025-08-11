#ifndef EIGHTGINECORE_CMODULE_MODULE_HPP
#define EIGHTGINECORE_CMODULE_MODULE_HPP

struct EIGHTGINECORE_API CModuleInterface
{
    virtual ~CModuleInterface() = default;

    virtual void OnLoad() = 0;
    virtual void OnProcess() = 0;
    virtual void OnUnload() = 0;
};

#endif // EIGHTGINECORE_CMODULE_MODULE_HPP
