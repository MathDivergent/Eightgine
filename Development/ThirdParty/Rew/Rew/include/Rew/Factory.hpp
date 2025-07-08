#ifndef REW_FACTORY_HPP
#define REW_FACTORY_HPP

#include <string> // string
#include <vector> // vector
#include <any> // any
#include <functional> // function

#include <Rew/Attribute.hpp>
#include <Rew/Utility.hpp>

// .factory<function_type>()
#define FACTORY(... /*function_type*/) \
    { \
        using xxtraits = rew::meta::function_traits<__VA_ARGS__>; \
        auto xxfactory = rew::find_or_add_factory<typename xxtraits::dirty_pointer>(xxreflection); \
        injection.template factory<CleanR, typename xxtraits::pointer>(*xxfactory); \
        xxmeta = &xxfactory->meta; \
    }

namespace rew
{

struct type_t;
struct meta_t;

struct factory_t
{
    std::string const name;
    std::function<std::any(std::vector<std::any> const& args)> const call = nullptr;
    std::vector<type_t*> const arguments;
    type_t* const result = nullptr;
    attribute_t<meta_t> meta;
};

namespace detail
{

template <typename ReflectableType, typename... ArgumentTypes, std::size_t... ArgumentIndexValues>
auto handler_factory_call_impl(std::index_sequence<ArgumentIndexValues...>)
{
    return [](std::vector<std::any> const& arguments) -> std::any
    {
        if constexpr (std::is_aggregate_v<ReflectableType>)
        {
            return std::any{ std::in_place_type<ReflectableType>, utility::forward<ArgumentTypes>(arguments[ArgumentIndexValues])... };
        }
        else
        {
            return std::make_any<ReflectableType>( utility::forward<ArgumentTypes>(arguments[ArgumentIndexValues])... );
        }
    };
}

} // namespace detail

template <typename ReflectableType, typename... ArgumentTypes>
auto handler_factory_call(ReflectableType(*)(ArgumentTypes...))
{
    return detail::handler_factory_call_impl<ReflectableType, ArgumentTypes...>
    (
        std::index_sequence_for<ArgumentTypes...>{}
    );
}

} // namespace rew

#endif // REW_FACTORY_HPP
