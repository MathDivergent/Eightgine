#ifndef REW_DEV_HPP
#define REW_DEV_HPP

#ifdef REW_DEV_ENABLE
#include <Rew/Reflectable.hpp>
#include <Rew/Common.hpp>

#include <Rew/BuiltIn/string.hpp>
#include <Rew/BuiltIn/unordered_map.hpp>

namespace rew
{

extern registry_t dev;

} // namespace rew

TEMPLATE_REFLECTABLE_DECLARATION((template <typename MetaType>), rew::attribute_t<MetaType>)
    REFLECTABLE_REGISTRY(&::rew::dev)
    REFLECTABLE_NAME("rew::attribute_t<" + rew::name_of<MetaType>() + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE((template <typename MetaType>), rew::attribute_t<MetaType>)
    FUNCTION(find)
    FUNCTION(add)
    PROPERTY(all)
REFLECTABLE_INIT()

REFLECTABLE_DECLARATION(rew::parent_t)
    REFLECTABLE_REGISTRY(&::rew::dev)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE_DECLARATION(rew::factory_t)
    REFLECTABLE_REGISTRY(&::rew::dev)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE_DECLARATION(rew::function_t)
    REFLECTABLE_REGISTRY(&::rew::dev)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE_DECLARATION(rew::property_t)
    REFLECTABLE_REGISTRY(&::rew::dev)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE_DECLARATION(rew::deleter_t)
    REFLECTABLE_REGISTRY(&::rew::dev)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE_DECLARATION(rew::meta_t)
    REFLECTABLE_REGISTRY(&::rew::dev)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE_DECLARATION(rew::reflection_t)
    REFLECTABLE_REGISTRY(&::rew::dev)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE_DECLARATION(rew::injectable_t)
    REFLECTABLE_REGISTRY(&::rew::dev)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE_DECLARATION(rew::injection_t)
    REFLECTABLE_REGISTRY(&::rew::dev)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE_DECLARATION(rew::type_t)
    REFLECTABLE_REGISTRY(&::rew::dev)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE_DECLARATION(rew::registry_t)
    REFLECTABLE_REGISTRY(&::rew::dev)
REFLECTABLE_DECLARATION_INIT()
#endif // REW_DEV_ENABLE

#endif // REW_DEV_HPP
