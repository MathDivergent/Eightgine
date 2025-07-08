#ifndef REW_DELETER_HPP
#define REW_DELETER_HPP

#include <string> // string
#include <any> // any
#include <functional> // function

#include <Rew/Attribute.hpp>
#include <Rew/Utility.hpp>

// .deleter<R, function_type>()
#define DELETER(... /*function_type*/) \
    { \
        using xxtraits = rew::meta::deleter_traits<__VA_ARGS__>; \
        auto xxdeleter = rew::find_or_add_deleter<typename xxtraits::dirty_pointer>(xxreflection); \
        injection.template deleter<CleanR, typename xxtraits::pointer>(*xxdeleter); \
        xxmeta = &xxdeleter->meta; \
    }

namespace rew
{

struct meta_t;

struct deleter_t
{
    std::string const name;
    std::function<void(std::any const& context)> const call = nullptr;
    attribute_t<meta_t> meta;
};

template <typename ReflectableType>
auto handler_deleter_call(void(*)(ReflectableType*))
{
    return [](std::any const& context)
    {
        std::any_cast<ReflectableType*>(context)->~ReflectableType();
    };
}

template <typename CustomDeleterType, typename ReflectableType>
auto handler_deleter_call(CustomDeleterType(*)(ReflectableType*))
{
    return [](std::any const& context)
    {
        CustomDeleterType(std::any_cast<ReflectableType*>(context));
    };
}

} // namespace rew

#endif // REW_DELETER_HPP
