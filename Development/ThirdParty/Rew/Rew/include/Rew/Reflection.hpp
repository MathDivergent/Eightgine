#ifndef REW_REFLECTION_HPP
#define REW_REFLECTION_HPP

#include <string> // string

#include <Rew/Attribute.hpp>

template <typename ReflectableType, typename enable = void>
struct xxrew;

namespace rew
{

struct parent_t;
struct function_t;
struct factory_t;
struct property_t;
struct deleter_t;
struct meta_t;

struct reflection_t
{
    std::string const name;

    attribute_t<parent_t> parent;
    attribute_t<factory_t> factory;
    attribute_t<attribute_t<function_t>> function;
    attribute_t<property_t> property;
    attribute_t<deleter_t> deleter;
    attribute_t<meta_t> meta;
};

} // namespace rew

#endif // REW_REFLECTION_HPP
