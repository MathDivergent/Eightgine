#ifndef REW_BUILTIN_ARRAY_HPP
#define REW_BUILTIN_ARRAY_HPP

#include <array> // array
#include <string> // to_string

#include <Rew/Reflectable.hpp>
#include <Rew/Common.hpp>

#ifdef REW_FULLY_ENABLE
// as function argument type
#include <Rew/BuiltIn/iterator.hpp>
#endif // REW_FULLY_ENABLE_DISABLE

TEMPLATE_REFLECTABLE_CLEAN
(
    (template <typename ValueType, std::size_t SizeValue>),
    (std::array<ValueType, SizeValue>), std::array<rew::clean_of<ValueType>, SizeValue>
)

TEMPLATE_REFLECTABLE_DECLARATION((template <typename ValueType, std::size_t SizeValue>), std::array<ValueType, SizeValue>)
    BUILTIN_REFLECTABLE()
    REFLECTABLE_NAME("std::array<" + rew::name_of<ValueType>() + ", " + std::to_string(SizeValue) + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE((template <typename ValueType, std::size_t SizeValue>), std::array<ValueType, SizeValue>)
    FACTORY(R())
    FACTORY(R(R const&))
    FUNCTION(operator=, R&(R const&))

    #ifdef REW_FULLY_ENABLE
    FUNCTION(at, typename R::const_reference(typename R::size_type) const)
    FUNCTION(at, typename R::reference(typename R::size_type))
    #endif // REW_FULLY_ENABLE

    FUNCTION(operator[], typename R::const_reference(typename R::size_type) const)
    FUNCTION(operator[], typename R::reference(typename R::size_type))

    #ifdef REW_FULLY_ENABLE
    FUNCTION(front, typename R::const_reference() const)
    FUNCTION(front, typename R::reference())
    FUNCTION(back, typename R::const_reference() const)
    FUNCTION(back, typename R::reference())
    #endif // REW_FULLY_ENABLE

    FUNCTION(data, typename R::const_pointer() const)
    FUNCTION(data, typename R::pointer())

    #ifdef REW_FULLY_ENABLE
    FUNCTION(begin, std_const_iterator<R>() const)
    FUNCTION(begin, std_iterator<R>())
    FUNCTION(cbegin, std_const_iterator<R>() const)
    FUNCTION(end, std_const_iterator<R>() const)
    FUNCTION(end, std_iterator<R>())
    FUNCTION(cend, std_const_iterator<R>() const)
    FUNCTION(rbegin, std_const_reverse_iterator<R>() const)
    FUNCTION(rbegin, std_reverse_iterator<R>())
    FUNCTION(crbegin, std_const_reverse_iterator<R>() const)
    FUNCTION(rend, std_const_reverse_iterator<R>() const)
    FUNCTION(rend, std_reverse_iterator<R>())
    FUNCTION(crend, std_const_reverse_iterator<R>() const)
    #endif // REW_FULLY_ENABLE

    FUNCTION(empty)
    FUNCTION(size)

    #ifdef REW_FULLY_ENABLE
    FUNCTION(max_size)
    FUNCTION(fill)
    FUNCTION(swap)
    #endif // REW_FULLY_ENABLE
REFLECTABLE_INIT()

#endif // REW_BUILTIN_ARRAY_HPP
