#ifndef REW_PARENT_HPP
#define REW_PARENT_HPP

#include <string> // string
#include <any> // any
#include <functional> // function

#include <Rew/Attribute.hpp>

// .parent<R, reflectable_type>()
#define PARENT(... /*reflectable_type*/) \
    { \
        auto xxparent = rew::find_or_add_parent<CleanR, __VA_ARGS__>(xxreflection); \
        injection.template parent<CleanR, __VA_ARGS__>(*xxparent); \
        xxmeta = &xxparent->meta; \
    }

namespace rew
{

struct type_t;
struct meta_t;

struct parent_t
{
    std::string const name;
    type_t* const type = nullptr;
    std::function<std::any(std::any const& child_context)> const cast = nullptr;
    attribute_t<meta_t> meta;
};

template <typename ReflectableType, typename ParentReflectableType>
auto handler_parent_cast()
{
    return [](std::any const& child_context) -> std::any
    {
        return static_cast<ParentReflectableType*>(std::any_cast<ReflectableType*>(child_context));
    };
}

} // namespace rew

#endif // REW_PARENT_HPP
