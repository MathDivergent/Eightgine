#ifndef REW_BUILTIN_UNORDERED_MAP_HPP
#define REW_BUILTIN_UNORDERED_MAP_HPP

#include <unordered_map> // unordered_map, unordered_multimap

#include <Rew/Reflectable.hpp>
#include <Rew/Common.hpp>

// default allocator for unordered_map, unordered_multimap
#include <Rew/BuiltIn/allocator.hpp>

#ifndef REW_CORE_MININAL
// as function argument type
#include <Rew/BuiltIn/initializer_list.hpp>
#include <Rew/BuiltIn/iterator.hpp>

// as value type
#include <Rew/BuiltIn/pair.hpp>
#endif // REW_CORE_MININAL

// hash - as hasher
// equal_to - as comparator
#include <Rew/BuiltIn/functional.hpp>

TEMPLATE_REFLECTABLE_CLEAN
(
    (template <typename KeyType, typename ValueType, typename HasherType, typename ComparatorType, typename AllocatorType>),
    (std::unordered_map<KeyType, ValueType, HasherType, ComparatorType, AllocatorType>),
    std::unordered_map<rew::clean_of<KeyType>, rew::clean_of<ValueType>, rew::clean_of<HasherType>, rew::clean_of<ComparatorType>, rew::clean_of<AllocatorType>>
)

TEMPLATE_REFLECTABLE_DECLARATION((template <typename KeyType, typename ValueType>), std::unordered_map<KeyType, ValueType>)
    BUILTIN_REFLECTABLE()
    REFLECTABLE_NAME("std::unordered_map<" + rew::name_of<KeyType>() + ", " + rew::name_of<ValueType>() + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE_DECLARATION
(
    (template <typename KeyType, typename ValueType, typename HasherType>),
    std::unordered_map<KeyType, ValueType, HasherType>
)
    BUILTIN_REFLECTABLE()
    REFLECTABLE_NAME("std::unordered_map<" + rew::name_of<KeyType>() + ", " + rew::name_of<ValueType>() + ", " + rew::name_of<HasherType>() + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE_DECLARATION
(
    (template <typename KeyType, typename ValueType, typename HasherType, typename ComparatorType>),
    std::unordered_map<KeyType, ValueType, HasherType, ComparatorType>
)
    BUILTIN_REFLECTABLE()
    REFLECTABLE_NAME
    (
        "std::unordered_map<" + rew::name_of<KeyType>() + ", " + rew::name_of<ValueType>() + ", "
                              + rew::name_of<ComparatorType>() + ", " + rew::name_of<HasherType>() + ">"
    )
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE_DECLARATION
(
    (template <typename KeyType, typename ValueType, typename HasherType, typename ComparatorType, typename AllocatorType>),
    std::unordered_map<KeyType, ValueType, HasherType, ComparatorType, AllocatorType>
)
    BUILTIN_REFLECTABLE()
    REFLECTABLE_NAME
    (
        "std::unordered_map<" + rew::name_of<KeyType>() + ", " + rew::name_of<ValueType>() + ", " + rew::name_of<HasherType>() + ", "
                              + rew::name_of<ComparatorType>() + ", " + rew::name_of<AllocatorType>() + ">"
    )
REFLECTABLE_DECLARATION_INIT()


TEMPLATE_REFLECTABLE_CLEAN
(
    (template <typename KeyType, typename ValueType, typename HasherType, typename ComparatorType, typename AllocatorType>),
    (std::unordered_multimap<KeyType, ValueType, HasherType, ComparatorType, AllocatorType>),
    std::unordered_multimap<rew::clean_of<KeyType>, rew::clean_of<ValueType>, rew::clean_of<HasherType>, rew::clean_of<ComparatorType>, rew::clean_of<AllocatorType>>
)

TEMPLATE_REFLECTABLE_DECLARATION((template <typename KeyType, typename ValueType>), std::unordered_multimap<KeyType, ValueType>)
    BUILTIN_REFLECTABLE()
    REFLECTABLE_NAME("std::unordered_multimap<" + rew::name_of<KeyType>() + ", " + rew::name_of<ValueType>() + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE_DECLARATION
(
    (template <typename KeyType, typename ValueType, typename HasherType>),
    std::unordered_multimap<KeyType, ValueType, HasherType>
)
    BUILTIN_REFLECTABLE()
    REFLECTABLE_NAME("std::unordered_multimap<" + rew::name_of<KeyType>() + ", " + rew::name_of<ValueType>() + ", " + rew::name_of<HasherType>() + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE_DECLARATION
(
    (template <typename KeyType, typename ValueType, typename HasherType, typename ComparatorType>),
    std::unordered_multimap<KeyType, ValueType, HasherType, ComparatorType>
)
    BUILTIN_REFLECTABLE()
    REFLECTABLE_NAME
    (
        "std::unordered_multimap<" + rew::name_of<KeyType>() + ", " + rew::name_of<ValueType>() + ", "
                                   + rew::name_of<ComparatorType>() + ", " + rew::name_of<HasherType>() + ">"
    )
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE_DECLARATION
(
    (template <typename KeyType, typename ValueType, typename HasherType, typename ComparatorType, typename AllocatorType>),
    std::unordered_multimap<KeyType, ValueType, HasherType, ComparatorType, AllocatorType>
)
    BUILTIN_REFLECTABLE()
    REFLECTABLE_NAME
    (
        "std::unordered_multimap<" + rew::name_of<KeyType>() + ", " + rew::name_of<ValueType>() + ", " + rew::name_of<HasherType>() + ", "
                                   + rew::name_of<ComparatorType>() + ", " + rew::name_of<AllocatorType>() + ">"
    )
REFLECTABLE_DECLARATION_INIT()


template <typename> struct xxrew_is_any_std_unordered_map : std::false_type {};

template <typename KeyType, typename HasherType, typename ComparatorType, typename AllocatorType>
struct xxrew_is_any_std_unordered_map<std::unordered_map<KeyType, HasherType, ComparatorType, AllocatorType>> : std::true_type {};

template <typename KeyType, typename HasherType, typename ComparatorType, typename AllocatorType>
struct xxrew_is_any_std_unordered_map<std::unordered_multimap<KeyType, HasherType, ComparatorType, AllocatorType>> : std::true_type {};

CONDITIONAL_REFLECTABLE(xxrew_is_any_std_unordered_map<R>::value)
    FACTORY(R())

    #ifdef REW_FULLY_ENABLE
    FACTORY(R(typename R::size_type, typename R::hasher const&, typename R::key_equal const&, typename R::allocator_type const&))
    FACTORY(R(typename R::size_type, typename R::hasher const&, typename R::key_equal const&))
    FACTORY(R(typename R::size_type, typename R::hasher const&))
    FACTORY(R(typename R::size_type))
    FACTORY(R(typename R::size_type, typename R::allocator_type const&))
    FACTORY(R(typename R::size_type, typename R::hasher const&, typename R::allocator_type const&))
    FACTORY(R(std_const_iterator<R>, std_const_iterator<R>, typename R::size_type, typename R::hasher const&, typename R::key_equal const&, typename R::allocator_type const&))
    FACTORY(R(std_const_iterator<R>, std_const_iterator<R>, typename R::size_type, typename R::hasher const&, typename R::key_equal const&))
    FACTORY(R(std_const_iterator<R>, std_const_iterator<R>, typename R::size_type, typename R::hasher const&))
    FACTORY(R(std_const_iterator<R>, std_const_iterator<R>, typename R::size_type))
    FACTORY(R(std_const_iterator<R>, std_const_iterator<R>, typename R::size_type, typename R::allocator_type const&))
    FACTORY(R(std_const_iterator<R>, std_const_iterator<R>, typename R::size_type, typename R::hasher const&, typename R::allocator_type const&))
    FACTORY(R(std::initializer_list<typename R::value_type>, typename R::size_type, typename R::hasher const&, typename R::key_equal const&, typename R::allocator_type const&))
    FACTORY(R(std::initializer_list<typename R::value_type>, typename R::size_type, typename R::hasher const&, typename R::key_equal const&))
    FACTORY(R(std::initializer_list<typename R::value_type>, typename R::size_type, typename R::hasher const&))
    FACTORY(R(std::initializer_list<typename R::value_type>, typename R::size_type))
    FACTORY(R(std::initializer_list<typename R::value_type>, typename R::size_type, typename R::hasher const&, typename R::allocator_type const&))
    #endif // REW_FULLY_ENABLE

    FACTORY(R(R const&))
    FUNCTION(operator=, R&(R const&))

    #ifdef REW_FULLY_ENABLE
    FUNCTION(get_allocator)
    FUNCTION(begin, std_const_iterator<R>() const)
    FUNCTION(begin, std_iterator<R>())
    FUNCTION(cbegin, std_const_iterator<R>() const)
    FUNCTION(end, std_const_iterator<R>() const)
    FUNCTION(end, std_iterator<R>())
    FUNCTION(cend, std_const_iterator<R>() const)
    #endif // REW_FULLY_ENABLE

    FUNCTION(empty)
    FUNCTION(size)

    #ifdef REW_FULLY_ENABLE
    FUNCTION(max_size)
    #endif // REW_CORE_MININAL

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

    #ifdef REW_FULLY_ENABLE
    FUNCTION(at, typename R::mapped_type&(typename R::key_type const&))
    #endif // REW_FULLY_ENABLE

    FUNCTION(at, typename R::mapped_type const&(typename R::key_type const&) const)
    FUNCTION(operator[], typename R::mapped_type&(typename R::key_type const&))
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
    FUNCTION(begin, std_const_local_iterator<R>(typename R::size_type) const)
    FUNCTION(begin, std_local_iterator<R>(typename R::size_type))
    FUNCTION(cbegin, std_const_local_iterator<R>(typename R::size_type) const)
    FUNCTION(end, std_const_local_iterator<R>(typename R::size_type) const)
    FUNCTION(end, std_local_iterator<R>(typename R::size_type))
    FUNCTION(cend, std_const_local_iterator<R>(typename R::size_type) const)
    FUNCTION(bucket_count)
    FUNCTION(max_bucket_count)
    FUNCTION(bucket_size)
    FUNCTION(bucket, typename R::size_type(typename R::key_type const&) const)
    FUNCTION(load_factor)
    FUNCTION(max_load_factor, float() const)
    FUNCTION(max_load_factor, void(float))
    #endif // REW_FULLY_ENABLE

    FUNCTION(rehash)
    FUNCTION(reserve)

    #ifdef REW_FULLY_ENABLE
    FUNCTION(hash_function)
    FUNCTION(key_eq)
    #endif // REW_FULLY_ENABLE
REFLECTABLE_INIT()

#endif // REW_BUILTIN_UNORDERED_MAP_HPP
