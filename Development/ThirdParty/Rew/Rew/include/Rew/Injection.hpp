#ifndef REW_INJECTION_HPP
#define REW_INJECTION_HPP

#include <string> // string
#include <any> // any
#include <functional> // function

#include <Rew/Reflection.hpp>
#include <Rew/Utility.hpp>

#ifndef REW_DEFAULT_INJECTION_COUNT
    #define REW_DEFAULT_INJECTION_COUNT 4
#endif // REW_INJECTION_MAX_KEY_SIZE

template <std::size_t InjectionIndexValue>
struct xxrew_injection;

namespace rew
{

struct type_t;
struct parent_t;
struct factory_t;
struct function_t;
struct property_t;
struct meta_t;
struct deleter_t;

struct injectable_t
{
    template <typename ReflectableType>
    void type(rew::type_t& type) {}

    template <typename ReflectableType, typename ParentReflectableType>
    void parent(rew::parent_t& parent) {}

    template <typename ReflectableType, typename FunctionType>
    void factory(rew::factory_t& factory) {}

    template <typename ReflectableType, typename FunctionType>
    void function(rew::function_t& function) {}

    template <typename ReflectableType, typename GetterType, typename SetterType>
    void property(rew::property_t& property) {}

    template <typename ReflectableType, typename MetaType>
    void meta(rew::meta_t& meta) {}

    template <typename ReflectableType, typename FunctionType>
    void deleter(rew::deleter_t& deleter) {}
};

struct injection_t
{
    std::string const name;
    type_t* const type = nullptr;
    std::function<void(std::any const& injectable_context)> const call = nullptr;
};

template <typename ReflectionType, class InjectionType>
auto handler_injection_call()
{
    return [](std::any const& injectable_context)
    {
        ::xxrew<ReflectionType>::evaluate(utility::forward<InjectionType&>(injectable_context));
    };
}

} // namespace rew

#endif // REW_INJECTION_HPP
