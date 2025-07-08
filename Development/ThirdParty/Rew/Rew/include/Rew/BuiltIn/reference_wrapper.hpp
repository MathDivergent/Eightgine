#ifndef REW_BUILTIN_REFERENCE_WRAPPER_HPP
#define REW_BUILTIN_REFERENCE_WRAPPER_HPP

#include <functional> // reference_wrapper

#include <Rew/Reflectable.hpp>
#include <Rew/Common.hpp>

TEMPLATE_REFLECTABLE_CLEAN
(
    template <typename ValueType>,
    std::reference_wrapper<ValueType>, std::reference_wrapper<rew::clean_of<ValueType>>
)

TEMPLATE_REFLECTABLE_DECLARATION(template <typename ValueType>, std::reference_wrapper<ValueType>)
    BUILTIN_REFLECTABLE()
    REFLECTABLE_NAME("std::reference_wrapper<" + rew::name_of<ValueType>() + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE(template <typename ValueType>, std::reference_wrapper<ValueType>)
    FACTORY(R(ValueType&))
    FACTORY(R(R const&))
    FUNCTION(operator=, R&(R const&))

    #ifdef REW_FULLY_ENABLE
    NAMED_FUNCTION(("operator " + rew::name_of<ValueType&>()), operator rew::clean_of<ValueType>&)
    #endif // REW_FULLY_ENABLE

    FUNCTION(get)
REFLECTABLE_INIT()

#endif // REW_BUILTIN_REFERENCE_WRAPPER_HPP
