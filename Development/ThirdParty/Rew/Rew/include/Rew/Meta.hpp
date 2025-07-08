#ifndef REW_META_HPP
#define REW_META_HPP

#include <string> // string
#include <any> // any

#include <Rew/Attribute.hpp>

#include <Rew/Detail/Meta.hpp>
#include <Rew/Detail/Macro.hpp> // REW_DEPAREN

// .meta(external_name, meta_expression)
#define CUSTOM_META(touch_expression, meta_pointer, external_name, ... /*meta_expression*/) \
    { \
        auto xxitem = meta_pointer->find(external_name); \
        if (xxitem == nullptr) xxitem = meta_pointer->add(external_name, { external_name, std::any(__VA_ARGS__) }); \
        injection.template meta<CleanR, decltype(::rew::meta::decltype_value(__VA_ARGS__))>(*xxitem); \
        REW_DEPAREN(touch_expression); \
    }

#define META(external_name, ... /*meta_expression*/) CUSTOM_META((xxsubmeta = &xxitem->meta), xxmeta, external_name, __VA_ARGS__)
#define SUBMETA(external_name, ... /*meta_expression*/) CUSTOM_META((), xxsubmeta, external_name, __VA_ARGS__)

namespace rew
{

struct meta_t
{
    std::string const name;
    std::any value;
    attribute_t<meta_t> meta;
};

} // namespace rew

#endif // REW_META_HPP
