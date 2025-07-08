#ifndef REW_BUILTIN_FORWARD_LIST_HPP
#define REW_BUILTIN_FORWARD_LIST_HPP

#include <forward_list> // forward_list

#include <Rew/Reflectable.hpp>
#include <Rew/Common.hpp>

// default allocator for forward_list
#include <Rew/BuiltIn/allocator.hpp>

#ifdef REW_FULLY_ENABLE
// as function argument type
#include <Rew/BuiltIn/initializer_list.hpp>
#include <Rew/BuiltIn/function.hpp>
#include <Rew/BuiltIn/iterator.hpp>
#endif // REW_FULLY_ENABLE

TEMPLATE_REFLECTABLE_CLEAN
(
    (template <typename ValueType, typename AllocatorType>),
    (std::forward_list<ValueType, AllocatorType>), std::forward_list<rew::clean_of<ValueType>, rew::clean_of<AllocatorType>>
)

TEMPLATE_REFLECTABLE_DECLARATION(template <typename ValueType>, std::forward_list<ValueType>)
    BUILTIN_REFLECTABLE()
    REFLECTABLE_NAME("std::forward_list<" + rew::name_of<ValueType>() + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE_DECLARATION
(
    (template <typename ValueType, typename AllocatorType>), std::forward_list<ValueType, AllocatorType>
)
    BUILTIN_REFLECTABLE()
    REFLECTABLE_NAME("std::forward_list<" + rew::name_of<ValueType>() + ", " + rew::name_of<AllocatorType>() + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE((template <typename ValueType, typename AllocatorType>), std::forward_list<ValueType, AllocatorType>)
    FACTORY(R())

    #ifdef REW_FULLY_ENABLE
    FACTORY(R(typename R::allocator_type const&))
    FACTORY(R(typename R::size_type, typename R::const_reference, typename R::allocator_type const&))
    FACTORY(R(typename R::size_type, typename R::const_reference))
    FACTORY(R(typename R::size_type, typename R::allocator_type const&))
    FACTORY(R(typename R::size_type))
    FACTORY(R(std_const_iterator<R>, std_const_iterator<R>, typename R::allocator_type const&))
    FACTORY(R(std_const_iterator<R>, std_const_iterator<R>))
    FACTORY(R(R const&, typename R::allocator_type const&))
    #endif // REW_FULLY_ENABLE

    FACTORY(R(R const&))

    #ifdef REW_FULLY_ENABLE
    FACTORY(R(std::initializer_list<typename R::value_type>, typename R::allocator_type const&))
    FACTORY(R(std::initializer_list<typename R::value_type>))
    #endif // REW_FULLY_ENABLE

    FUNCTION(operator=, R&(R const&))

    #ifdef REW_FULLY_ENABLE
    FUNCTION(operator=, R&(std::initializer_list<typename R::value_type>))
    FUNCTION(assign, void(typename R::size_type, typename R::const_reference))
    FUNCTION(assign, void(std_const_iterator<R>, std_const_iterator<R>))
    FUNCTION(assign, void(std::initializer_list<typename R::value_type>))
    FUNCTION(get_allocator)
    FUNCTION(front, typename R::const_reference() const)
    FUNCTION(front, typename R::reference())
    FUNCTION(before_begin, std_const_iterator<R>() const)
    FUNCTION(before_begin, std_iterator<R>())
    FUNCTION(cbefore_begin, std_const_iterator<R>() const)
    FUNCTION(begin, std_const_iterator<R>() const)
    FUNCTION(begin, std_iterator<R>())
    FUNCTION(cbegin, std_const_iterator<R>() const)
    FUNCTION(end, std_const_iterator<R>() const)
    FUNCTION(end, std_iterator<R>())
    FUNCTION(cend, std_const_iterator<R>() const)
    #endif // REW_FULLY_ENABLE

    FUNCTION(empty)

    #ifdef REW_FULLY_ENABLE
    FUNCTION(max_size)
    #endif // REW_FULLY_ENABLE

    FUNCTION(clear)

    #ifdef REW_FULLY_ENABLE
    FUNCTION(insert_after, std_iterator<R>(std_const_iterator<R>, typename R::const_reference))
    FUNCTION(insert_after, std_iterator<R>(std_const_iterator<R>, typename R::size_type, typename R::const_reference))
    FUNCTION(insert_after, std_iterator<R>(std_const_iterator<R>, std_const_iterator<R>, std_const_iterator<R>))
    FUNCTION(insert_after, std_iterator<R>(std_const_iterator<R>, std::initializer_list<typename R::value_type>))
    FUNCTION(erase_after, std_iterator<R>(std_const_iterator<R>))
    FUNCTION(erase_after, std_iterator<R>(std_const_iterator<R>, std_const_iterator<R>))
    #endif // REW_FULLY_ENABLE

    FUNCTION(push_front, void(typename R::const_reference))
    FUNCTION(pop_front)
    FUNCTION(resize, void(typename R::size_type))

    #ifdef REW_FULLY_ENABLE
    FUNCTION(resize, void(typename R::size_type, typename R::const_reference))
    FUNCTION(swap)
    #endif // REW_FULLY_ENABLE

    FUNCTION(merge, void(R&))

    #ifdef REW_FULLY_ENABLE
    FUNCTION(merge, void(R&, std::function<bool(typename R::const_reference, typename R::const_reference)>))
    FUNCTION(splice_after, void(std_const_iterator<R>, R&))
    FUNCTION(splice_after, void(std_const_iterator<R>, R&, std_const_iterator<R>))
    FUNCTION(splice_after, void(std_const_iterator<R>, R&, std_const_iterator<R>, std_const_iterator<R>))
    #endif // REW_FULLY_ENABLE

#if __cplusplus < 202002L
    FUNCTION(remove, void(typename R::const_reference))

    #ifdef REW_FULLY_ENABLE
    FUNCTION(remove_if, void(std::function<bool(typename R::const_reference)>))
    #endif // REW_FULLY_ENABLE

    FUNCTION(unique, void())

    #ifdef REW_FULLY_ENABLE
    FUNCTION(unique, void(std::function<bool(typename R::const_reference, typename R::const_reference)>))
    #endif // REW_FULLY_ENABLE
#else
    FUNCTION(remove, typename R::size_type(typename R::const_reference))

    #ifdef REW_FULLY_ENABLE
    FUNCTION(remove_if, typename R::size_type(std::function<bool(typename R::const_reference)>))
    #endif // REW_FULLY_ENABLE

    FUNCTION(unique, typename R::size_type())

    #ifdef REW_FULLY_ENABLE
    FUNCTION(unique, typename R::size_type(std::function<bool(typename R::const_reference, typename R::const_reference)>))
    #endif // REW_FULLY_ENABLE
#endif // if

    FUNCTION(reverse)
    FUNCTION(sort, void())

    #ifdef REW_FULLY_ENABLE
    FUNCTION(sort, void(std::function<bool(typename R::const_reference, typename R::const_reference)>))
    #endif // REW_FULLY_ENABLE
REFLECTABLE_INIT()

#endif // REW_BUILTIN_FORWARD_LIST_HPP
