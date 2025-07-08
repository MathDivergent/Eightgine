#ifndef REW_BUILTIN_OPTIONAL_HPP
#define REW_BUILTIN_OPTIONAL_HPP

#include <optional> // optional, nullopt_t

#include <Rew/Reflectable.hpp>
#include <Rew/Common.hpp>

REFLECTABLE_DECLARATION(std::nullopt_t)
    BUILTIN_REFLECTABLE()
REFLECTABLE_DECLARATION_INIT()


TEMPLATE_REFLECTABLE_CLEAN
(
    template <typename ValueType>,
    std::optional<ValueType>, std::optional<rew::clean_of<ValueType>>
)

TEMPLATE_REFLECTABLE_DECLARATION(template <typename ValueType>, std::optional<ValueType>)
    BUILTIN_REFLECTABLE()
    REFLECTABLE_NAME("std::optional<" + rew::name_of<ValueType>() + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE(template <typename ValueType>, std::optional<ValueType>)
    FACTORY(R())
    FACTORY(R(std::nullopt_t))
    FACTORY(R(R const&))
    FACTORY(R(typename R::value_type const&))
    FUNCTION(operator=, R&(std::nullopt_t))
    FUNCTION(operator=, R&(R const&))

    #ifdef REW_FULLY_ENABLE
    FUNCTION(operator->, typename R::value_type const*() const)
    FUNCTION(operator->, typename R::value_type*())
    FUNCTION(operator*, typename R::value_type const&() const&)
    FUNCTION(operator*, typename R::value_type&()&)
    #endif // REW_FULLY_ENABLE

    FUNCTION(operator bool)

    #ifdef REW_FULLY_ENABLE
//  FUNCTION(has_value)
    #endif // REW_FULLY_ENABLE

    FUNCTION(value, typename R::value_type&()&)
    FUNCTION(value, typename R::value_type const&() const&)

    #ifdef REW_FULLY_ENABLE
    FUNCTION(value_or, typename R::value_type(typename R::value_type const&) const&)
    FUNCTION(swap)
    #endif // REW_FULLY_ENABLE

//  FUNCTION(reset)
    FUNCTION(emplace, typename R::value_type&(typename R::value_type const&))
REFLECTABLE_INIT()

#endif // REW_BUILTIN_OPTIONAL_HPP
