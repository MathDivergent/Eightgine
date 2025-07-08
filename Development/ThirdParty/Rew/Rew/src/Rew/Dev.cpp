#include <Rew/Dev.hpp>

#ifdef REW_DEV_ENABLE
#include <Rew/BuiltIn/string.hpp>
#include <Rew/BuiltIn/any.hpp>
#include <Rew/BuiltIn/function.hpp>
#include <Rew/BuiltIn/vector.hpp>
#include <Rew/BuiltIn/pair.hpp>
#include <Rew/BuiltIn/typeindex.hpp>
#include <Rew/BuiltIn/unordered_map.hpp>

namespace rew
{

registry_t dev;

} // namespace rew

REFLECTABLE(rew::parent_t)
    PROPERTY(name)
    PROPERTY(type)
    PROPERTY(cast)
    PROPERTY(meta)
REFLECTABLE_INIT()

REFLECTABLE(rew::factory_t)
    PROPERTY(name)
    PROPERTY(call)
    PROPERTY(arguments)
    PROPERTY(meta)
REFLECTABLE_INIT()

REFLECTABLE(rew::function_t)
    PROPERTY(name)
    PROPERTY(call)
    PROPERTY(arguments)
    PROPERTY(result)
    PROPERTY(pointer)
    PROPERTY(meta)
REFLECTABLE_INIT()

REFLECTABLE(rew::property_t)
    PROPERTY(name)
    PROPERTY(type)
    PROPERTY(get)
    PROPERTY(set)
    PROPERTY(context)
    PROPERTY(meta)
REFLECTABLE_INIT()

REFLECTABLE(rew::deleter_t)
    PROPERTY(name)
    PROPERTY(call)
    PROPERTY(meta)
REFLECTABLE_INIT()

REFLECTABLE(rew::meta_t)
    PROPERTY(name)
    PROPERTY(value)
    PROPERTY(meta)
REFLECTABLE_INIT()

REFLECTABLE(rew::reflection_t)
    PROPERTY(name)
    PROPERTY(parent)
    PROPERTY(function)
    PROPERTY(factory)
    PROPERTY(property)
    PROPERTY(meta)
REFLECTABLE_INIT()

REFLECTABLE(rew::injection_t)
    PROPERTY(name)
    PROPERTY(call)
REFLECTABLE_INIT()

REFLECTABLE(rew::type_t)
    PROPERTY(name)
    PROPERTY(reflection)
    PROPERTY(registry)
    PROPERTY(size)
    PROPERTY(context)
    PROPERTY(injection)
REFLECTABLE_INIT()

REFLECTABLE(rew::registry_t)
    FACTORY(rew::registry_t())
    FUNCTION(find, rew::type_t*(std::string const&) const)
    FUNCTION(find, rew::type_t*(std::type_index) const)
    PROPERTY(all)
    PROPERTY(rtti_all)
REFLECTABLE_INIT()
#endif // REW_DEV_ENABLE
