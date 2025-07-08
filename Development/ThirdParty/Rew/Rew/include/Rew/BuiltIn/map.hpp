#ifndef REW_BUILTIN_MAP_HPP
#define REW_BUILTIN_MAP_HPP

#include <map> // map, multimap

#include <Rew/Reflectable.hpp>
#include <Rew/Common.hpp>

// default allocator for map, multimap
#include <Rew/BuiltIn/allocator.hpp>

#ifdef REW_FULLY_ENABLE
// as function argument type
#include <Rew/BuiltIn/initializer_list.hpp>
#include <Rew/BuiltIn/iterator.hpp>
#endif // REW_FULLY_ENABLE

// as value type
#include <Rew/BuiltIn/pair.hpp>

//less - as comparator
#include <Rew/BuiltIn/functional.hpp>

TEMPLATE_REFLECTABLE_CLEAN
(
    (template <typename KeyType, typename ValueType, typename ComparatorType, typename AllocatorType>),
    (std::map<KeyType, ValueType, ComparatorType, AllocatorType>),
    std::map<rew::clean_of<KeyType>, rew::clean_of<ValueType>, rew::clean_of<ComparatorType>, rew::clean_of<AllocatorType>>
)

TEMPLATE_REFLECTABLE_DECLARATION((template <typename KeyType, typename ValueType>), std::map<KeyType, ValueType>)
    BUILTIN_REFLECTABLE()
    REFLECTABLE_NAME( "std::map<" + rew::name_of<KeyType>() + ", " + rew::name_of<ValueType>() + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE_DECLARATION
(
    (template <typename KeyType, typename ValueType, typename ComparatorType>),
    std::map<KeyType, ValueType, ComparatorType>
)
    BUILTIN_REFLECTABLE()
    REFLECTABLE_NAME
    (
        "std::map<" + rew::name_of<KeyType>() + ", " + rew::name_of<ValueType>() + ", " + rew::name_of<ComparatorType>() + ">"
    )
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE_DECLARATION
(
    (template <typename KeyType, typename ValueType, typename ComparatorType, typename AllocatorType>),
    std::map<KeyType, ValueType, ComparatorType, AllocatorType>
)
    BUILTIN_REFLECTABLE()
    REFLECTABLE_NAME
    (
        "std::map<" + rew::name_of<KeyType>() + ", " + rew::name_of<ValueType>() + ", "
                    + rew::name_of<ComparatorType>() + ", " + rew::name_of<AllocatorType>() + ">"
    )
REFLECTABLE_DECLARATION_INIT()


TEMPLATE_REFLECTABLE_CLEAN
(
    (template <typename KeyType, typename ValueType, typename ComparatorType, typename AllocatorType>),
    (std::multimap<KeyType, ValueType, ComparatorType, AllocatorType>),
    std::multimap<rew::clean_of<KeyType>, rew::clean_of<ValueType>, rew::clean_of<ComparatorType>, rew::clean_of<AllocatorType>>
)

TEMPLATE_REFLECTABLE_DECLARATION((template <typename KeyType, typename ValueType>), std::multimap<KeyType, ValueType>)
    BUILTIN_REFLECTABLE()
    REFLECTABLE_NAME( "std::multimap<" + rew::name_of<KeyType>() + ", " + rew::name_of<ValueType>() + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE_DECLARATION
(
    (template <typename KeyType, typename ValueType, typename ComparatorType>),
    std::multimap<KeyType, ValueType, ComparatorType>
)
    BUILTIN_REFLECTABLE()
    REFLECTABLE_NAME
    (
        "std::multimap<" + rew::name_of<KeyType>() + ", " + rew::name_of<ValueType>() + ", " + rew::name_of<ComparatorType>() + ">"
    )
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE_DECLARATION
(
    (template <typename KeyType, typename ValueType, typename ComparatorType, typename AllocatorType>),
    std::multimap<KeyType, ValueType, ComparatorType, AllocatorType>
)
    BUILTIN_REFLECTABLE()
    REFLECTABLE_NAME
    (
        "std::multimap<" + rew::name_of<KeyType>() + ", " + rew::name_of<ValueType>() + ", "
                         + rew::name_of<ComparatorType>() + ", " + rew::name_of<AllocatorType>() + ">"
    )
REFLECTABLE_DECLARATION_INIT()


template <typename> struct xxrew_is_any_std_ordered_map : std::false_type {};

template <typename KeyType, typename ValueType, typename ComparatorType, typename AllocatorType>
struct xxrew_is_any_std_ordered_map<std::map<KeyType, ValueType, ComparatorType, AllocatorType>> : std::true_type {};

template <typename KeyType, typename ValueType, typename ComparatorType, typename AllocatorType>
struct xxrew_is_any_std_ordered_map<std::multimap<KeyType, ValueType, ComparatorType, AllocatorType>> : std::true_type {};

CONDITIONAL_REFLECTABLE(xxrew_is_any_std_ordered_map<R>::value)
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
    FUNCTION(at, typename R::mapped_type&(typename R::key_type const&))
    #endif // REW_FULLY_ENABLE

    FUNCTION(at, typename R::mapped_type const&(typename R::key_type const&) const)
    FUNCTION(operator[], typename R::mapped_type&(typename R::key_type const&))

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
    #endif // REW_FULLY_ENABLE

    FUNCTION(clear)

    #ifdef REW_FULLY_ENABLE
    FUNCTION(insert, std::pair<std_iterator<R>, bool>(typename R::const_reference))
    FUNCTION(insert, std_iterator<R>(std_const_iterator<R>, typename R::const_reference))
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

#endif // REW_BUILTIN_MAP_HPP
