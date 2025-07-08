#ifndef REW_FUNCTION_HPP
#define REW_FUNCTION_HPP

#include <cstddef> // size_t

#include <string> // string
#include <vector> // vector
#include <any> // any
#include <functional> // function

#include <Rew/Attribute.hpp>
#include <Rew/Utility.hpp>

#include <Rew/Detail/Macro.hpp> // REW_DEPAREN

// .function<R, function_type>(external_name, &scope::internal_name)
#define CUSTOM_FUNCTION(scope, external_name, internal_name, ... /*function_type*/) \
    { \
        using xxaccess = typename rew::meta::access_traits<scope>::template function<__VA_ARGS__>; \
        auto xxpointer = xxaccess::of(&scope::REW_DEPAREN(internal_name)); \
        auto xxfunction = rew::find_or_add_function<__VA_ARGS__>(xxreflection, external_name, xxpointer); \
        injection.template function<CleanR, decltype(xxpointer)>(*xxfunction); \
        xxmeta = &xxfunction->meta; \
    }

#define NAMED_FUNCTION(external_name, internal_name, ... /*function_type*/) CUSTOM_FUNCTION(CleanR, external_name, internal_name, __VA_ARGS__)
#define NAMED_FREE_FUNCTION(external_name, internal_name, ... /*function_type*/) CUSTOM_FUNCTION(, external_name, internal_name, __VA_ARGS__)
#define FUNCTION(name, ... /*function_type*/) NAMED_FUNCTION(REW_TO_STRING(name), name, __VA_ARGS__)
#define FREE_FUNCTION(name, ... /*function_type*/) NAMED_FREE_FUNCTION(REW_TO_STRING(name), name, __VA_ARGS__)

namespace rew
{

struct type_t;
struct meta_t;

struct function_t
{
    std::string const name;
    std::function<std::any(std::any const& context, std::vector<std::any> const& args)> const call = nullptr;
    std::vector<type_t*> const arguments;
    type_t* const result = nullptr;
    std::any const pointer;
    attribute_t<meta_t> meta;
};

namespace detail
{

template <typename ReflectableType, typename ReturnType, typename... ArgumentTypes,
          typename FunctionType, std::size_t... ArgumentIndexValues>
auto handler_member_function_call_impl(FunctionType function, std::index_sequence<ArgumentIndexValues...>)
{
    return [function](std::any const& context, std::vector<std::any> const& arguments) -> std::any
    {
        auto reflectable = std::any_cast<ReflectableType*>(context);
        if constexpr (std::is_void_v<ReturnType>)
        {
            (reflectable->*function)(utility::forward<ArgumentTypes>(arguments[ArgumentIndexValues])...);
            return {};
        }
        else
        {
            return utility::backward
            (
                (reflectable->*function)(utility::forward<ArgumentTypes>(arguments[ArgumentIndexValues])...)
            );
        }
    };
}

template <typename ReturnType, typename... ArgumentTypes, std::size_t... ArgumentIndexValues>
auto handler_free_function_call_impl(ReturnType(*function)(ArgumentTypes...), std::index_sequence<ArgumentIndexValues...>)
{
    return [function](std::any const&, std::vector<std::any> const& arguments) -> std::any
    {
        if constexpr (std::is_void_v<ReturnType>)
        {
            function(utility::forward<ArgumentTypes>(arguments[ArgumentIndexValues])...);
            return {};
        }
        else
        {
            return utility::backward
            (
                function(utility::forward<ArgumentTypes>(arguments[ArgumentIndexValues])...)
            );
        }
    };
}

} // namespace detail

template <typename ReflectableType, typename ReturnType, typename... ArgumentTypes>
auto handler_function_call(ReturnType(ReflectableType::* function)(ArgumentTypes...) const)
{
    return detail::handler_member_function_call_impl<ReflectableType, ReturnType, ArgumentTypes...>
    (
        function, std::index_sequence_for<ArgumentTypes...>{}
    );
}

template <typename ReflectableType, typename ReturnType, typename... ArgumentTypes>
auto handler_function_call(ReturnType(ReflectableType::* function)(ArgumentTypes...) const&)
{
    return detail::handler_member_function_call_impl<ReflectableType, ReturnType, ArgumentTypes...>
    (
        function, std::index_sequence_for<ArgumentTypes...>{}
    );
}

template <typename ReflectableType, typename ReturnType, typename... ArgumentTypes>
auto handler_function_call(ReturnType(ReflectableType::* function)(ArgumentTypes...))
{
    return detail::handler_member_function_call_impl<ReflectableType, ReturnType, ArgumentTypes...>
    (
        function, std::index_sequence_for<ArgumentTypes...>{}
    );
}

template <typename ReflectableType, typename ReturnType, typename... ArgumentTypes>
auto handler_function_call(ReturnType(ReflectableType::* function)(ArgumentTypes...)&)
{
    return detail::handler_member_function_call_impl<ReflectableType, ReturnType, ArgumentTypes...>
    (
        function, std::index_sequence_for<ArgumentTypes...>{}
    );
}

template <typename ReturnType, typename... ArgumentTypes>
auto handler_function_call(ReturnType(*function)(ArgumentTypes...))
{
    return detail::handler_free_function_call_impl(function, std::index_sequence_for<ArgumentTypes...>{});
}

} // namespace rew

#endif // REW_FUNCTION_HPP
