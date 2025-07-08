#ifndef REW_BUILTIN_SET_HPP
#define REW_BUILTIN_SET_HPP

#include <set> // set, multiset

#include <Rew/Reflectable.hpp>
#include <Rew/Common.hpp>

// default allocator for set, multiset
#include <Rew/BuiltIn/allocator.hpp>

#ifdef REW_FULLY_ENABLE
// as function argument/result type
#include <Rew/BuiltIn/initializer_list.hpp>
#include <Rew/BuiltIn/iterator.hpp>
#include <Rew/BuiltIn/pair.hpp>
#endif // REW_FULLY_ENABLE

//less - as comparator
#include <Rew/BuiltIn/functional.hpp>

TEMPLATE_REFLECTABLE_CLEAN
(
    (template <typename KeyType, typename ComparatorType, typename AllocatorType>),
    (std::set<KeyType, ComparatorType, AllocatorType>),
    std::set<rew::clean_of<KeyType>, rew::clean_of<ComparatorType>, rew::clean_of<AllocatorType>>
)

TEMPLATE_REFLECTABLE_DECLARATION(template <typename KeyType>, std::set<KeyType>)
    BUILTIN_REFLECTABLE()
    REFLECTABLE_NAME("std::set<" + rew::name_of<KeyType>() + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE_DECLARATION
(
    (template <typename KeyType, typename ComparatorType>),
    std::set<KeyType, ComparatorType>
)
    BUILTIN_REFLECTABLE()
    REFLECTABLE_NAME("std::set<" + rew::name_of<KeyType>() + ", " + rew::name_of<ComparatorType>() + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE_DECLARATION
(
    (template <typename KeyType, typename ComparatorType, typename AllocatorType>),
    std::set<KeyType, ComparatorType, AllocatorType>
)
    BUILTIN_REFLECTABLE()
    REFLECTABLE_NAME
    (
        "std::set<" + rew::name_of<KeyType>() + ", " + rew::name_of<ComparatorType>() + ", " + rew::name_of<AllocatorType>() + ">"
    )
REFLECTABLE_DECLARATION_INIT()


TEMPLATE_REFLECTABLE_CLEAN
(
    (template <typename KeyType, typename ComparatorType, typename AllocatorType>),
    (std::multiset<KeyType, ComparatorType, AllocatorType>),
    std::multiset<rew::clean_of<KeyType>, rew::clean_of<ComparatorType>, rew::clean_of<AllocatorType>>
)

TEMPLATE_REFLECTABLE_DECLARATION(template <typename KeyType>, std::multiset<KeyType>)
    BUILTIN_REFLECTABLE()
    REFLECTABLE_NAME("std::multiset<" + rew::name_of<KeyType>() + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE_DECLARATION
(
    (template <typename KeyType, typename ComparatorType>),
    std::multiset<KeyType, ComparatorType>
)
    BUILTIN_REFLECTABLE()
    REFLECTABLE_NAME("std::multiset<" + rew::name_of<KeyType>() + ", " + rew::name_of<ComparatorType>() + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE_DECLARATION
(
    (template <typename KeyType, typename ComparatorType, typename AllocatorType>),
    std::multiset<KeyType, ComparatorType, AllocatorType>
)
    BUILTIN_REFLECTABLE()
    REFLECTABLE_NAME
    (
        "std::multiset<" + rew::name_of<KeyType>() + ", " + rew::name_of<ComparatorType>() + ", " + rew::name_of<AllocatorType>() + ">"
    )
REFLECTABLE_DECLARATION_INIT()


template <typename> struct xxrew_is_any_std_ordered_set : std::false_type {};

template <typename KeyType, typename ComparatorType, typename AllocatorType>
struct xxrew_is_any_std_ordered_set<std::set<KeyType, ComparatorType, AllocatorType>> : std::true_type {};

template <typename KeyType, typename ComparatorType, typename AllocatorType>
struct xxrew_is_any_std_ordered_set<std::multiset<KeyType, ComparatorType, AllocatorType>> : std::true_type {};

CONDITIONAL_REFLECTABLE(xxrew_is_any_std_ordered_set<R>::value)
    FACTORY(R())

    #ifdef REW_FULLY_ENABLE
    FACTORY(R(typename R::key_compare const&, typename R::allocator_type const&))
    FACTORY(R(typename R::key_compare const&))
    FACTORY(R(typename R::allocator_type const&))
    FACTORY(R(std_const_iterator<R>, std_const_iterator<R>, typename R::key_compare const&, typename R::allocator_type const&))
    FACTORY(R(std_const_iterator<R>, std_const_iterator<R>, typename R::allocator_type const&))
    #endif // REW_FULLY_ENABLE

    FACTORY(R(R const&))

    #ifdef REW_FULLY_ENABLE
    FACTORY(R(R const&, typename R::allocator_type const&))
    FACTORY(R(std::initializer_list<typename R::value_type>, typename R::key_compare const&, typename R::allocator_type const&))
    FACTORY(R(std::initializer_list<typename R::value_type>))
    #endif // REW_FULLY_ENABLE

    FUNCTION(operator=, R&(R const&))

    #ifdef REW_FULLY_ENABLE
    FUNCTION(operator=, R&(std::initializer_list<typename R::value_type>))
    FUNCTION(get_allocator)
    FUNCTION(begin, std_const_iterator<R>() const)
    FUNCTION(cbegin, std_const_iterator<R>() const)
    FUNCTION(end, std_const_iterator<R>() const)
    FUNCTION(cend, std_const_iterator<R>() const)
    FUNCTION(rbegin, std_const_reverse_iterator<R>() const)
    FUNCTION(crbegin, std_const_reverse_iterator<R>() const)
    FUNCTION(rend, std_const_reverse_iterator<R>() const)
    FUNCTION(crend, std_const_reverse_iterator<R>() const)
    #endif // REW_FULLY_ENABLE

    FUNCTION(empty)
    FUNCTION(size)

    #ifdef REW_FULLY_ENABLE
    FUNCTION(max_size)
    #endif // REW_FULLY_ENABLE

    FUNCTION(clear)

    #ifdef REW_FULLY_ENABLE
    FUNCTION(insert, std::pair<std_iterator<R>, bool>(typename R::const_reference))
    FUNCTION(insert, std_iterator<R>(std_iterator<R>, typename R::const_reference))
    FUNCTION(insert, void(std_const_iterator<R>, std_const_iterator<R>))
    FUNCTION(insert, void(std::initializer_list<typename R::value_type>))
    FUNCTION(erase, std_iterator<R>(std_iterator<R>))
    FUNCTION(erase, std_iterator<R>(std_const_iterator<R>))
    FUNCTION(erase, std_iterator<R>(std_const_iterator<R>, std_const_iterator<R>))
    FUNCTION(swap)
//  FUNCTION(extract, typename R::node_type(std_const_iterator<R>))
//  FUNCTION(extract, typename R::node_type(typename R::key_type const&))
    #endif // REW_FULLY_ENABLE

    FUNCTION(merge, void(R&))
    FUNCTION(count, typename R::size_type(typename R::key_type const&) const)

    #ifdef REW_FULLY_ENABLE
    FUNCTION(find, std_iterator<R>(typename R::key_type const&))
    FUNCTION(find, std_const_iterator<R>(typename R::key_type const&) const)
    #endif // REW_FULLY_ENABLE

#if __cplusplus >= 202002L
    FUNCTION(contains, bool(typename R::key_type const&) const)
#endif // if

    #ifdef REW_FULLY_ENABLE
    FUNCTION(equal_range, std::pair<std_iterator<R>, std_iterator<R>>(typename R::key_type const&))
    FUNCTION(equal_range, std::pair<std_const_iterator<R>, std_const_iterator<R>>(typename R::key_type const&) const)
    FUNCTION(lower_bound, std_iterator<R>(typename R::key_type const&))
    FUNCTION(lower_bound, std_const_iterator<R>(typename R::key_type const&) const)
    FUNCTION(upper_bound, std_iterator<R>(typename R::key_type const&))
    FUNCTION(upper_bound, std_const_iterator<R>(typename R::key_type const&) const)
    FUNCTION(key_comp)
//  FUNCTION(value_comp)
    #endif // REW_FULLY_ENABLE
REFLECTABLE_INIT()

#endif // REW_BUILTIN_SET_HPP
