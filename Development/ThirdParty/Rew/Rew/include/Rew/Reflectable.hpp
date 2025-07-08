#ifndef REW_REFLECTABLE_HPP
#define REW_REFLECTABLE_HPP

#include <cstddef> // size_t

#include <Rew/Registry.hpp>
#include <Rew/Injection.hpp>
#include <Rew/Parent.hpp>
#include <Rew/Factory.hpp>
#include <Rew/Function.hpp>
#include <Rew/Property.hpp>
#include <Rew/Deleter.hpp>
#include <Rew/Meta.hpp>

#include <Rew/Detail/Meta.hpp>
#include <Rew/Detail/Macro.hpp>

#define TEMPLATE_REFLECTABLE_DECLARATION(object_template_header, ... /*reflectable_type*/) \
    REW_DEPAREN(object_template_header) struct xxrew_traits<__VA_ARGS__> { \
        using R = typename ::xxrew_alias<__VA_ARGS__>::R; \
        LAZY_REFLECTABLE()

#define CONDITIONAL_REFLECTABLE_DECLARATION(... /*reflectable_type_condition*/) \
    template <typename DirtyR> struct xxrew_traits<DirtyR, std::enable_if_t<__VA_ARGS__>> { \
        using R = typename ::xxrew_alias<DirtyR>::R; \
        LAZY_REFLECTABLE()

#define REFLECTABLE_DECLARATION(... /*reflectable_type*/) \
    template <> struct xxrew_traits<__VA_ARGS__> { \
        using R = typename ::xxrew_alias<__VA_ARGS__>::R; \
        static constexpr auto alias = #__VA_ARGS__;

#define REFLECTABLE_REGISTRY(... /*reflectable_registry_address*/)  static auto registry() { return __VA_ARGS__; }
#define REFLECTABLE_NAME(... /*reflectable_name_string*/) static auto name() { return __VA_ARGS__; }
#define LAZY_REFLECTABLE() struct lazy;
#define BUILTIN_REFLECTABLE() struct builtin;

#define REFLECTABLE_DECLARATION_INIT() \
    };


#define TEMPLATE_REFLECTABLE(object_template_header, ... /*reflectable_type*/) \
    REW_DEPAREN(object_template_header) struct xxrew<__VA_ARGS__> { \
        using R = __VA_ARGS__; \
        using CleanR = typename ::xxrew_alias<R>::R; \
        REW_REFLECTABLE_BODY()

#define CONDITIONAL_REFLECTABLE(... /*reflectable_type_condition*/) \
    template <typename R> struct xxrew<R, std::enable_if_t<__VA_ARGS__>> { \
        using CleanR = typename ::xxrew_alias<R>::R; \
        REW_REFLECTABLE_BODY()

#define REFLECTABLE(... /*reflectable_type*/) \
    template <> struct xxrew<__VA_ARGS__> { \
        using R = __VA_ARGS__; \
        using CleanR = typename ::xxrew_alias<R>::R; \
        REW_REFLECTABLE_BODY()

#define REW_REFLECTABLE_BODY() \
    template <class InjectionType> static void evaluate(InjectionType&& injection) { \
        auto xxtype = rew::find_or_add_type<R>(); \
        auto xxreflection = xxtype->reflection; (void)xxreflection; \
        auto xxmeta = &xxreflection->meta; (void)xxmeta; \
        rew::attribute_t<rew::meta_t>* xxsubmeta = nullptr; (void)xxsubmeta; \
        rew::add_default_injection_set<R>(xxtype); \
        injection.template type<R>(*xxtype); \

#ifdef REW_DISABLE_REFLECTION_FIXTURE
    #define REFLECTABLE_INIT() \
            } \
        };
#else
    #define REFLECTABLE_INIT() \
            } \
            inline static auto xxfixture = (rew::reflectable<R>(), true); \
        };
#endif // REW_DISABLE_REFLECTION_FIXTURE


#define REFLECTABLE_INJECTION_DECLARATION(injection_index, ... /*reflectable_type*/) \
    template <> struct xxrew_injection<injection_index> { using R = __VA_ARGS__; }; \
        REFLECTABLE_DECLARATION(__VA_ARGS__)


#define TEMPLATE_REFLECTABLE_CLEAN(object_template_header, object_type, ... /*clean_reflectable_type*/) \
    REW_DEPAREN(object_template_header) struct xxrew_alias<REW_DEPAREN(object_type)> { using R = __VA_ARGS__; };

#define REFLECTABLE_CLEAN(alias_type, ... /*clean_reflectable_type*/) \
    template <> struct xxrew_alias<alias_type> { using R = __VA_ARGS__; };

#define TEMPLATE_REFLECTABLE_USING(alias_object_template_header, alias_type, alias_object_type, ... /*clean_reflectable_type*/) \
    REW_DEPAREN(alias_object_template_header) struct alias_type : rew::meta::inherits<__VA_ARGS__> {}; \
    TEMPLATE_REFLECTABLE_CLEAN(alias_object_template_header, alias_object_type, __VA_ARGS__)

#define REFLECTABLE_USING(alias_type, ... /*clean_reflectable_type*/) \
    struct alias_type : rew::meta::inherits<__VA_ARGS__> {}; \
    REFLECTABLE_CLEAN(alias_type, __VA_ARGS__)


#define REFLECTABLE_ACCESS() template <typename, typename> friend struct xxrew;


namespace rew
{

// useful for name generation (reflectable declaration)
template <typename ReflectableType>
std::string name_of()
{
    using reflectable_traits = ::xxrew_traits<ReflectableType>;
    if constexpr (meta::is_custom_name<ReflectableType>::value)
    {
        return reflectable_traits::name();
    }
    else
    {
        return reflectable_traits::alias;
    }
}

template <typename ReflectableType>
using clean_of = typename ::xxrew_alias<ReflectableType>::R;

template <typename ReflectableType>
void reflectable()
{
    static auto lock = false; if (lock) return;
    lock = true;

    ::xxrew<ReflectableType>::evaluate(injectable_t{});
}

template <typename ReflectableType>
ReflectableType&& reflectable(ReflectableType&& object)
{
    reflectable<std::decay_t<ReflectableType>>();
    return std::forward<ReflectableType>(object);
}

template <typename DirtyReflectableType>
type_t* find_or_add_type()
{
    using dirty_reflectable_type = typename std::conditional_t
    <
        std::is_reference_v<DirtyReflectableType>,
        meta::to_reflectable_reference<DirtyReflectableType>,
        std::conditional_t
        <
            std::is_pointer_v<DirtyReflectableType>,
            meta::to_reflectable_pointer<DirtyReflectableType>,
            meta::to_reflectable_object<DirtyReflectableType>
        >
    >::type;

    using reflectable_type = typename ::xxrew_alias<dirty_reflectable_type>::R;
    using reflectable_traits = ::xxrew_traits<dirty_reflectable_type>;

    if constexpr (meta::is_lazy<dirty_reflectable_type>::value)
    {
        reflectable<dirty_reflectable_type>();
    }

    auto xxname = name_of<dirty_reflectable_type>();
    auto xxregistry = &global;

    if constexpr (meta::is_custom_registry<dirty_reflectable_type>::value)
    {
        xxregistry = reflectable_traits::registry();
    }

    auto xxtype = xxregistry->all[xxname];
    if (xxtype == nullptr)
    {
        xxtype = xxregistry->template add<reflectable_type, dirty_reflectable_type>(xxname);
    }

    return xxtype;
}

template <typename ReflectableType>
type_t* type_of()
{
    static auto type = find_or_add_type<ReflectableType>();
    return type;
}

template <typename ReflectableType, typename ParentReflectableType>
parent_t* find_or_add_parent(reflection_t* reflection)
{
    static_assert(std::is_base_of_v<ParentReflectableType, ReflectableType>);

    auto xxname = name_of<ParentReflectableType>();

    auto xxmeta = reflection->parent.find(xxname);
    if (xxmeta == nullptr) xxmeta = reflection->parent.add
    (
        xxname,
        {
            xxname,
            find_or_add_type<ParentReflectableType>(),
            handler_parent_cast<ReflectableType, ParentReflectableType>()
        }
    );

    return xxmeta;
}

namespace detail
{

template <typename... ArgumentTypes, typename ReturnType>
auto function_argument_types(ReturnType(*unused)(ArgumentTypes...))
{
    return std::vector<type_t*>({ find_or_add_type<ArgumentTypes>()... });
}

template <typename... ArgumentTypes, typename ReturnType>
auto function_return_type(ReturnType(*unused)(ArgumentTypes...))
{
    return find_or_add_type<ReturnType>();
}

} // namespace detail

template <typename DirtyFactoryType>
factory_t* find_or_add_factory(reflection_t* reflection)
{
    using function_traits = meta::function_traits<DirtyFactoryType>;
    using dirty_type = typename function_traits::dirty_type;
    using dirty_pointer = typename function_traits::dirty_pointer;
    using pointer = typename function_traits::pointer;

    auto xxname = name_of<dirty_type>();

    auto xxmeta = reflection->factory.find(xxname);
    if (xxmeta == nullptr) xxmeta = reflection->factory.add
    (
        xxname,
        {
            xxname,
            handler_factory_call(pointer{}),
            detail::function_argument_types(dirty_pointer{}),
            detail::function_return_type(dirty_pointer{})
        }
    );

    return xxmeta;
}

template <typename DirtyFunctionType = void, typename FunctionType>
function_t* find_or_add_function(reflection_t* reflection, std::string const& name, FunctionType pointer)
{
    using function_traits = meta::function_traits
    <
        typename std::conditional_t
        <
            std::is_void_v<DirtyFunctionType>,
            meta::type_identity<FunctionType>,
            meta::mark_dirty<FunctionType, DirtyFunctionType>
        >::type
    >;

    using dirty_type = typename function_traits::dirty_type;
    using dirty_pointer = typename function_traits::dirty_pointer;

    auto xxfunction = reflection->function.find(name);
    if (xxfunction == nullptr) xxfunction = reflection->function.add(name, {});

    auto xxoverload = name_of<dirty_type>();

    auto xxmeta = xxfunction->find(xxoverload);
    if (xxmeta == nullptr) xxmeta = xxfunction->add
    (
        xxoverload,
        {
            xxoverload,
            handler_function_call(pointer),
            detail::function_argument_types(dirty_pointer{}),
            detail::function_return_type(dirty_pointer{}),
            pointer
        }
    );

    return xxmeta;
}

template <typename DirtyPropertyType = void, typename GetterType, typename SetterType>
property_t* find_or_add_property(reflection_t* reflection, std::string const& name,
                                 GetterType ipointer, SetterType opointer)
{
    using property_traits = meta::property_traits
    <
        typename std::conditional_t
        <
            std::is_void_v<DirtyPropertyType>,
            meta::type_identity<GetterType>,
            meta::mark_dirty<GetterType, DirtyPropertyType>
        >::type
    >;

    using dirty_type = typename property_traits::type;

    auto xxmeta = reflection->property.find(name);
    if (xxmeta == nullptr) xxmeta = reflection->property.add
    (
        name,
        {
            name,
            find_or_add_type<dirty_type>(),
            handler_property_get(ipointer),
            handler_property_set(opointer),
            handler_property_context(ipointer),
            property_pointer(ipointer, opointer)
        }
    );

    return xxmeta;
}

template <typename DirtyDeleterType>
deleter_t* find_or_add_deleter(reflection_t* reflection)
{
    using deleter_traits = meta::deleter_traits<DirtyDeleterType>;
    using dirty_type = typename deleter_traits::dirty_type;
    using pointer = typename deleter_traits::pointer;

    auto xxname = name_of<dirty_type>();

    auto xxmeta = reflection->deleter.find(xxname);
    if (xxmeta == nullptr) xxmeta = reflection->deleter.add
    (
        xxname,
        {
            xxname,
            handler_deleter_call(pointer{})
        }
    );

    return xxmeta;
}

template <typename MetaType>
meta_t* find_or_add_meta(attribute_t<meta_t>& meta, std::string const& name, MetaType&& value)
{
    auto xxmeta = meta.find(name);
    if (xxmeta == nullptr) xxmeta = meta.add(name, { name, value });
    return xxmeta;
}

template <typename ReflectableType, class InjectionType>
injection_t* find_or_add_injection(type_t* type)
{
    static_assert(std::is_base_of_v<injectable_t, InjectionType>);

    auto xxtype = find_or_add_type<InjectionType>();

    auto xxmeta = type->injection.find(xxtype->name);
    if (xxmeta == nullptr) xxmeta = type->injection.add
    (
        xxtype->name,
        {
            xxtype->name,
            xxtype,
            handler_injection_call<ReflectableType, InjectionType>()
        }
    );

    return xxmeta;
}

template <typename ReflectableType,
          std::size_t InjectionIndexValue = 0,
          std::size_t DefaultInjectionCountValue = REW_DEFAULT_INJECTION_COUNT>
void add_default_injection_set(type_t* type)
{
    using reflectable_traits = ::xxrew_injection<InjectionIndexValue>;
    if constexpr (meta::is_complete<reflectable_traits>::value)
    {
        find_or_add_injection<ReflectableType, typename reflectable_traits::R>(type);
        if constexpr (InjectionIndexValue < DefaultInjectionCountValue)
        {
            add_default_injection_set<ReflectableType, InjectionIndexValue + 1>(type);
        }
    }
}

} // namespace rew

#endif // REW_REFLECTABLE_HPP
