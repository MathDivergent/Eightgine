#ifndef REW_BUILTIN_FUNCTION_HPP
#define REW_BUILTIN_FUNCTION_HPP

#include <functional> // function

#include <Rew/Reflectable.hpp>
#include <Rew/Common.hpp>

#ifdef REW_FULLY_ENABLE
// as function return type
#include <Rew/BuiltIn/typeinfo.hpp>
#endif // REW_FULLY_ENABLE

TEMPLATE_REFLECTABLE_CLEAN
(
    (template <typename ReturnType, typename... ArgumentTypes>),
    (std::function<ReturnType(ArgumentTypes...)>), std::function<rew::clean_of<ReturnType(ArgumentTypes...)>>
)

REFLECTABLE_DECLARATION(std::function<void()>)
    BUILTIN_REFLECTABLE()
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE_DECLARATION
(
    (template <typename ReturnType, typename... ArgumentTypes>),
    std::function<ReturnType(ArgumentTypes...)>
)
    BUILTIN_REFLECTABLE()
    REFLECTABLE_NAME("std::function<" + rew::name_of<ReturnType(ArgumentTypes...)>() + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE
(
    (template <typename ReturnType, typename... ArgumentTypes>),
    std::function<ReturnType(ArgumentTypes...)>
)
    FACTORY(R())
    FACTORY(R(std::nullptr_t))
    FACTORY(R(R const&))
    FUNCTION(operator=, R&(R const&))
    FUNCTION(operator=, R&(std::nullptr_t))

    #ifdef REW_FULLY_ENABLE
    FUNCTION(swap)
    #endif // REW_FULLY_ENABLE

    FUNCTION(operator bool)
    FUNCTION(operator())

    #ifdef REW_FULLY_ENABLE
    FUNCTION(target_type)
    #endif // REW_FULLY_ENABLE
REFLECTABLE_INIT()

#endif // REW_BUILTIN_FUNCTION_HPP
