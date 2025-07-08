#ifndef REW_BUILTIN_ALLOCATOR_HPP
#define REW_BUILTIN_ALLOCATOR_HPP

#include <memory> // allocator

#include <Rew/Reflectable.hpp>
#include <Rew/Common.hpp>

TEMPLATE_REFLECTABLE_CLEAN
(
    template <typename ValueType>,
    std::allocator<ValueType>, std::allocator<rew::clean_of<ValueType>>
)

TEMPLATE_REFLECTABLE_DECLARATION(template <typename ValueType>, std::allocator<ValueType>)
    BUILTIN_REFLECTABLE()
    REFLECTABLE_NAME("std::allocator<" + rew::name_of<ValueType>() + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE(template <typename ValueType>, std::allocator<ValueType>)
    FACTORY(R())
    FACTORY(R(R const&))
REFLECTABLE_INIT()

#endif // REW_BUILTIN_ALLOCATOR_HPP
