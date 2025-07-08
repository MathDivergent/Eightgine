#ifndef REW_PROPERTY_HPP
#define REW_PROPERTY_HPP

#include <string> // string
#include <any> // any
#include <utility> // pair
#include <functional> // function
#include <memory> // addressof
#include <type_traits> // is_reference_v

#include <Rew/Attribute.hpp>
#include <Rew/Utility.hpp>

#include <Rew/Detail/Macro.hpp> // REW_DEPAREN

// .property<R, variable_type_or_function_type>(external_name, &scope::internal_iname, &scope::ìnternal_oname)
#define CUSTOM_PROPERTY(scope, external_name, internal_iname, internal_oname, ... /*variable_type_or_function_type*/) \
    { \
        using xxaccess = typename rew::meta::access_traits<scope>::template property<__VA_ARGS__>; \
        auto xxpointer = xxaccess::of(&scope::REW_DEPAREN(internal_iname), &scope::REW_DEPAREN(internal_oname)); \
        auto xxproperty = rew::find_or_add_property<__VA_ARGS__>(xxreflection, external_name, xxpointer.first, xxpointer.second); \
        injection.template property<CleanR, decltype(xxpointer.first), decltype(xxpointer.second)>(*xxproperty); \
        xxmeta = &xxproperty->meta; \
    }

#define NAMED_PROPERTY(external_name, internal_iname, internal_oname, ... /*variable_type_or_function_type*/) \
    CUSTOM_PROPERTY(CleanR, external_name, internal_iname, internal_oname, __VA_ARGS__)

#define NAMED_FREE_PROPERTY(external_name, internal_iname, internal_oname, ... /*variable_type_or_function_type*/) \
    CUSTOM_PROPERTY(, external_name, internal_iname, internal_oname, __VA_ARGS__)

#define PROPERTY(name, ... /*variable_type_or_function_type*/) NAMED_PROPERTY(REW_TO_STRING(name), name, name, __VA_ARGS__)
#define FREE_PROPERTY(name, ... /*variable_type_or_function_type*/) NAMED_FREE_PROPERTY(REW_TO_STRING(name), name, name, __VA_ARGS__)

namespace rew
{

struct type_t;
struct meta_t;

struct property_t
{
    std::string const name;
    type_t* const type = nullptr;
    std::function<void(std::any const& context, std::any& result)> const get = nullptr;
    std::function<void(std::any const& context, std::any const& value)> const set = nullptr;
    std::function<std::any(std::any const& outer_context)> const context = nullptr;
    std::pair<std::any, std::any> const pointer;
    attribute_t<meta_t> meta;
};

namespace detail
{

template <typename ReflectableType, typename GetterType>
auto handler_property_get_impl(GetterType property)
{
    return [property](std::any const& context, std::any& value)
    {
        using property_type = typename meta::property_traits<GetterType>::type;

        value = utility::backward<property_type>
        (
            (std::any_cast<ReflectableType*>(context)->*property)()
        );
    };
}

} // namespace detail

template <typename ReflectableType, typename PropertyType>
auto handler_property_get(PropertyType ReflectableType::* property)
{
    return [property](std::any const& context, std::any& result)
    {
        result = utility::forward<PropertyType>
        (
            std::any_cast<ReflectableType*>(context)->*property
        );
    };
}

template <typename ReflectableType, typename PropertyType>
auto handler_property_get(PropertyType(ReflectableType::* property)(void) const)
{
    return detail::handler_property_get_impl<ReflectableType>(property);
}

template <typename ReflectableType, typename PropertyType>
auto handler_property_get(PropertyType(ReflectableType::* property)(void) const&)
{
    return detail::handler_property_get_impl<ReflectableType>(property);
}

template <typename ReflectableType, typename PropertyType>
auto handler_property_get(PropertyType(ReflectableType::* property)(void))
{
    return detail::handler_property_get_impl<ReflectableType>(property);
}

template <typename ReflectableType, typename PropertyType>
auto handler_property_get(PropertyType(ReflectableType::* property)(void)&)
{
    return detail::handler_property_get_impl<ReflectableType>(property);
}

template <typename PropertyType>
auto handler_property_get(PropertyType* property)
{
    return [property](std::any const&, std::any& result)
    {
        result = utility::forward<PropertyType>(*property);
    };
}

template <typename PropertyType>
auto handler_property_get(PropertyType(*property)(void))
{
    return [property](std::any const&, std::any& result)
    {
        result = utility::backward<PropertyType>(property());
    };
}

namespace detail
{

template <typename ReflectableType, typename SetterType>
auto handler_property_set_impl(SetterType property)
{
    return [property](std::any const& context, std::any const& value)
    {
        using property_type = typename meta::property_traits<SetterType>::type;

        (std::any_cast<ReflectableType*>(context)->*property)(utility::forward<property_type>(value));
    };
}

} // namespace detail

template <typename ReflectableType, typename PropertyType>
auto handler_property_set(PropertyType ReflectableType::* property)
{
    return [property](std::any const& context, std::any const& value)
    {
        std::any_cast<ReflectableType*>(context)->*property = utility::forward<PropertyType>(value);
    };
}

template <typename ReflectableType, typename PropertyType>
auto handler_property_set(PropertyType const ReflectableType::* property)
{
    return nullptr;
}

template <typename ReflectableType, typename PropertyType>
auto handler_property_set(void(ReflectableType::* property)(PropertyType))
{
    return detail::handler_property_set_impl<ReflectableType>(property);
}

template <typename ReflectableType, typename PropertyType>
auto handler_property_set(void(ReflectableType::* property)(PropertyType)&)
{
    return detail::handler_property_set_impl<ReflectableType>(property);
}

template <typename PropertyType>
auto handler_property_set(PropertyType* property)
{
    return [property](std::any const&, std::any const& value)
    {
        *property = utility::forward<PropertyType>(value);
    };
}

template <typename PropertyType>
auto handler_property_set(PropertyType const* property)
{
    return nullptr;
}

template <typename PropertyType>
auto handler_property_set(void(*property)(PropertyType))
{
    return [property](std::any const&, std::any const& value)
    {
        property(utility::forward<PropertyType>(value));
    };
}

template <typename ReflectableType, typename PropertyType>
auto handler_property_set(PropertyType(ReflectableType::* property)(void) const)
{
    return nullptr;
}

template <typename ReflectableType, typename PropertyType>
auto handler_property_set(PropertyType(ReflectableType::* property)(void) const&)
{
    return nullptr;
}

template <typename ReflectableType, typename PropertyType>
auto handler_property_set(PropertyType(ReflectableType::* property)(void))
{
    return nullptr;
}

template <typename ReflectableType, typename PropertyType>
auto handler_property_set(PropertyType(ReflectableType::* property)(void)&)
{
    return nullptr;
}

template <typename PropertyType>
auto handler_property_set(PropertyType(*property)(void))
{
    return nullptr;
}

namespace detail
{

template <typename ReflectableType, typename GetterType>
auto handler_property_context_impl(GetterType property)
{
    using property_type = typename meta::property_traits<GetterType>::type;
    if constexpr (std::is_reference_v<property_type>)
    {
        return [property](std::any const& outer_context) -> std::any
        {
            return const_cast<typename meta::to_reflectable_reference<property_type>::type>
            (
                std::addressof((std::any_cast<ReflectableType*>(outer_context)->*property)())
            );
        };
    }
    else
    {
        return nullptr;
    }
}

} // namespace detail

template <typename ReflectableType, typename PropertyType>
auto handler_property_context(PropertyType ReflectableType::* property)
{
    return [property](std::any const& outer_context) -> std::any
    {
        return const_cast<typename meta::to_reflectable_object<PropertyType>::type*>
        (
            std::addressof(std::any_cast<ReflectableType*>(outer_context)->*property)
        );
    };
}

template <typename ReflectableType, typename PropertyType>
auto handler_property_context(PropertyType(ReflectableType::* property)(void) const)
{
    return detail::handler_property_context_impl<ReflectableType>(property);
}

template <typename ReflectableType, typename PropertyType>
auto handler_property_context(PropertyType(ReflectableType::* property)(void) const&)
{
    return detail::handler_property_context_impl<ReflectableType>(property);
}

template <typename ReflectableType, typename PropertyType>
auto handler_property_context(PropertyType(ReflectableType::* property)(void))
{
    return detail::handler_property_context_impl<ReflectableType>(property);
}

template <typename ReflectableType, typename PropertyType>
auto handler_property_context(PropertyType(ReflectableType::* property)(void)&)
{
    return detail::handler_property_context_impl<ReflectableType>(property);
}

template <typename PropertyType>
auto handler_property_context(PropertyType* property)
{
    return [property](std::any const&) -> std::any
    {
        return const_cast<typename meta::to_reflectable_object<PropertyType>::type*>(property);
    };
}

template <typename PropertyType>
auto handler_property_context(PropertyType(*property)(void))
{
    if constexpr (std::is_reference_v<PropertyType>)
    {
        return [property](std::any const&) -> std::any
        {
            return const_cast<typename meta::to_reflectable_reference<PropertyType>::type>
            (
                std::addressof(property())
            );
        };
    }
    else
    {
        return nullptr;
    }
}

template <typename ipropertyterType, typename opropertyterType>
constexpr auto property_pointer(ipropertyterType iproperty, opropertyterType oproperty)
{
    return std::make_pair(iproperty, oproperty);
}

template <typename ReflectableType, typename PropertyType>
constexpr auto property_pointer(PropertyType const ReflectableType::* iproperty, PropertyType const ReflectableType::* oproperty)
{
    return std::make_pair(iproperty, std::any{});
}

template <typename ReflectableType, typename PropertyType>
constexpr auto property_pointer(PropertyType(ReflectableType::* iproperty)(void) const, PropertyType(ReflectableType::* oproperty)(void) const)
{
    return std::make_pair(iproperty, std::any{});
}

template <typename ReflectableType, typename PropertyType>
constexpr auto property_pointer(PropertyType(ReflectableType::* iproperty)(void) const&, PropertyType(ReflectableType::* oproperty)(void) const&)
{
    return std::make_pair(iproperty, std::any{});
}

template <typename ReflectableType, typename PropertyType>
constexpr auto property_pointer(PropertyType(ReflectableType::* iproperty)(void), PropertyType(ReflectableType::* oproperty)(void))
{
    return std::make_pair(iproperty, std::any{});
}

template <typename ReflectableType, typename PropertyType>
constexpr auto property_pointer(PropertyType(ReflectableType::* iproperty)(void)&, PropertyType(ReflectableType::* oproperty)(void)&)
{
    return std::make_pair(iproperty, std::any{});
}

template <typename PropertyType>
constexpr auto property_pointer(PropertyType(*iproperty)(void), PropertyType(*oproperty)(void))
{
    return std::make_pair(iproperty, std::any{});
}

template <typename PropertyType>
constexpr auto property_pointer(PropertyType const* iproperty, PropertyType const* oproperty)
{
    return std::make_pair(iproperty, std::any{});
}

} // namespace rew

#endif // REW_PROPERTY_HPP
