#ifndef REW_BUILTIN_PAIR_HPP
#define REW_BUILTIN_PAIR_HPP

#include <utility> // pair

#include <Rew/Reflectable.hpp>
#include <Rew/Common.hpp>

TEMPLATE_REFLECTABLE_CLEAN
(
    (template <typename FirstType, typename SecondType>),
    (std::pair<FirstType, SecondType>), std::pair<rew::clean_of<FirstType>, rew::clean_of<SecondType>>
)

TEMPLATE_REFLECTABLE_DECLARATION((template <typename FirstType, typename SecondType>), std::pair<FirstType, SecondType>)
    BUILTIN_REFLECTABLE()
    REFLECTABLE_NAME("std::pair<" + rew::name_of<FirstType>() + ", " + rew::name_of<SecondType>() + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE((template <typename FirstType, typename SecondType>), std::pair<FirstType, SecondType>)
    FACTORY(R())

    #ifdef REW_FULLY_ENABLE
    FACTORY(R(typename R::first_type const&, typename R::second_type const&))
    FACTORY(R(R const&))
    FUNCTION(operator=, R&(R const&))
    FUNCTION(swap, void(R&))
    #endif // REW_FULLY_ENABLE

    PROPERTY(first, typename R::first_type)
    PROPERTY(second, typename R::second_type)
REFLECTABLE_INIT()

#endif // REW_BUILTIN_PAIR_HPP
