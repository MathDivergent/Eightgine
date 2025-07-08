#ifndef REW_BUILTIN_VECTOR_HPP
#define REW_BUILTIN_VECTOR_HPP

#include <vector> // vector

#include <Rew/Reflectable.hpp>
#include <Rew/Common.hpp>

// default allocator for vector
#include <Rew/BuiltIn/allocator.hpp>

#ifdef REW_FULLY_ENABLE
// as function argument type
#include <Rew/BuiltIn/initializer_list.hpp>

// as function argument type
#include <Rew/BuiltIn/iterator.hpp>
#endif // REW_FULLY_ENABLE

TEMPLATE_REFLECTABLE_CLEAN
(
    (template <typename ValueType, typename AllocatorType>),
    (std::vector<ValueType, AllocatorType>), std::vector<rew::clean_of<ValueType>, rew::clean_of<AllocatorType>>
)

TEMPLATE_REFLECTABLE_DECLARATION(template <typename ValueType>, std::vector<ValueType>)
    BUILTIN_REFLECTABLE()
    REFLECTABLE_NAME("std::vector<" + rew::name_of<ValueType>() + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE_DECLARATION
(
    (template <typename ValueType, typename AllocatorType>), std::vector<ValueType, AllocatorType>
)
    BUILTIN_REFLECTABLE()
    REFLECTABLE_NAME("std::vector<" + rew::name_of<ValueType>() + ", " + rew::name_of<AllocatorType>() + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE
(
    (template <typename ValueType, typename AllocatorType>), std::vector<ValueType, AllocatorType>
)
    FACTORY(R())

    #ifdef REW_FULLY_ENABLE
    FACTORY(R(typename R::allocator_type const&))
    FACTORY(R(typename R::size_type, typename R::const_reference, typename R::allocator_type const&))
    FACTORY(R(typename R::size_type, typename R::const_reference))
    FACTORY(R(typename R::size_type, typename R::allocator_type const&))
    FACTORY(R(typename R::size_type))
    FACTORY(R(std_const_iterator<R>, std_const_iterator<R>, typename R::allocator_type const&))
    FACTORY(R(std_const_iterator<R>, std_const_iterator<R>))
    FACTORY(R(R const&,  typename R::allocator_type const&))
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
    #endif // REW_FULLY_ENABLE

    FUNCTION(capacity)
    FUNCTION(reserve)

    #ifdef REW_FULLY_ENABLE
    FUNCTION(shrink_to_fit)
    #endif // REW_FULLY_ENABLE

    FUNCTION(clear)

    #ifdef REW_FULLY_ENABLE
    FUNCTION(insert, std_iterator<R>(std_const_iterator<R>, typename R::const_reference))
    FUNCTION(insert, std_iterator<R>(std_const_iterator<R>, typename R::size_type, typename R::const_reference))
    FUNCTION(insert, std_iterator<R>(std_const_iterator<R>, std_const_iterator<R>, std_const_iterator<R>))
    FUNCTION(insert, std_iterator<R>(std_const_iterator<R>, std::initializer_list<typename R::value_type>))
    FUNCTION(erase, std_iterator<R>(std_const_iterator<R>))
    FUNCTION(erase, std_iterator<R>(std_const_iterator<R>, std_const_iterator<R>))
    #endif // REW_FULLY_ENABLE

    FUNCTION(push_back, void(typename R::const_reference))
    FUNCTION(pop_back)
    FUNCTION(resize, void(typename R::size_type))

    #ifdef REW_FULLY_ENABLE
    FUNCTION(resize, void(typename R::size_type, typename R::const_reference))
    FUNCTION(swap)
    #endif // REW_FULLY_ENABLE
REFLECTABLE_INIT()


TEMPLATE_REFLECTABLE_USING
(
    template <class StdContainer>, std_vectorbool_reference,
    std_vectorbool_reference<StdContainer>, typename rew::clean_of<StdContainer>::reference
)

TEMPLATE_REFLECTABLE_DECLARATION(template <class StdContainer>, std_vectorbool_reference<StdContainer>)
    BUILTIN_REFLECTABLE()
    REFLECTABLE_NAME(rew::name_of<StdContainer>() + "::reference")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE(template <class StdContainer>, std_vectorbool_reference<StdContainer>)
    FUNCTION(operator=, R&(bool))

    #ifdef REW_FULLY_ENABLE
    FUNCTION(operator=, R&(R const&))
    #endif // REW_FULLY_ENABLE

    FUNCTION(operator bool)
    FUNCTION(flip)
REFLECTABLE_INIT()


TEMPLATE_REFLECTABLE_USING
(
    template <class StdContainer>, std_vectorbool_const_reference,
    std_vectorbool_const_reference<StdContainer>, typename rew::clean_of<StdContainer>::const_reference
)

TEMPLATE_REFLECTABLE_DECLARATION(template <class StdContainer>, std_vectorbool_const_reference<StdContainer>)
    BUILTIN_REFLECTABLE()
    REFLECTABLE_NAME(rew::name_of<StdContainer>() + "::const_reference")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE(template <class StdContainer>, std_vectorbool_const_reference<StdContainer>)
    FUNCTION(operator bool)
REFLECTABLE_INIT()


TEMPLATE_REFLECTABLE(template <typename AllocatorType>, std::vector<bool, AllocatorType>)
    FACTORY(R())

    #ifdef REW_FULLY_ENABLE
    FACTORY(R(typename R::allocator_type const&))
    FACTORY(R(typename R::size_type, std_vectorbool_const_reference<R>, typename R::allocator_type const&))
    FACTORY(R(typename R::size_type, std_vectorbool_const_reference<R>))
    FACTORY(R(typename R::size_type, typename R::allocator_type const&))
    FACTORY(R(typename R::size_type))
    FACTORY(R(std_const_iterator<R>, std_const_iterator<R>, typename R::allocator_type const&))
    FACTORY(R(std_const_iterator<R>, std_const_iterator<R>))
    FACTORY(R(R const&,  typename R::allocator_type const&))
    #endif // REW_FULLY_ENABLE

    FACTORY(R(R const&))

    #ifdef REW_FULLY_ENABLE
    FACTORY(R(std::initializer_list<typename R::value_type>, typename R::allocator_type const&))
    FACTORY(R(std::initializer_list<typename R::value_type>))
    #endif // REW_FULLY_ENABLE

    FUNCTION(operator=, R&(R const&))

    #ifdef REW_FULLY_ENABLE
    FUNCTION(operator=, R&(std::initializer_list<typename R::value_type>))
    FUNCTION(assign, void(typename R::size_type, typename R::value_type const&))
    FUNCTION(assign, void(std_const_iterator<R>, std_const_iterator<R>))
    FUNCTION(assign, void(std::initializer_list<typename R::value_type>))
    FUNCTION(get_allocator)
    FUNCTION(at, std_vectorbool_const_reference<R>(typename R::size_type) const)
    FUNCTION(at, std_vectorbool_reference<R>(typename R::size_type))
    #endif // REW_FULLY_ENABLE

    FUNCTION(operator[], std_vectorbool_const_reference<R>(typename R::size_type) const)
    FUNCTION(operator[], std_vectorbool_reference<R>(typename R::size_type))

    #ifdef REW_FULLY_ENABLE
    FUNCTION(front, std_vectorbool_const_reference<R>() const)
    FUNCTION(front, std_vectorbool_reference<R>())
    FUNCTION(back, std_vectorbool_const_reference<R>() const)
    FUNCTION(back, std_vectorbool_reference<R>())
    #endif // REW_FULLY_ENABLE

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

    FUNCTION(capacity)
    FUNCTION(reserve)

    #ifdef REW_FULLY_ENABLE
    FUNCTION(shrink_to_fit)
    #endif // REW_FULLY_ENABLE

    FUNCTION(clear)

    #ifdef REW_FULLY_ENABLE
    FUNCTION(insert, std_iterator<R>(std_const_iterator<R>, typename R::value_type const&))
    FUNCTION(insert, std_iterator<R>(std_const_iterator<R>, typename R::size_type, typename R::value_type const&))
    FUNCTION(insert, std_iterator<R>(std_const_iterator<R>, std_const_iterator<R>, std_const_iterator<R>))
    FUNCTION(insert, std_iterator<R>(std_const_iterator<R>, std::initializer_list<typename R::value_type>))
    FUNCTION(erase, std_iterator<R>(std_const_iterator<R>))
    FUNCTION(erase, std_iterator<R>(std_const_iterator<R>, std_const_iterator<R>))
    #endif // REW_FULLY_ENABLE

    FUNCTION(push_back, void(typename R::value_type const&))
    FUNCTION(pop_back)
//  FUNCTION(resize, void(typename R::size_type))

    #ifdef REW_FULLY_ENABLE
    FUNCTION(resize, void(typename R::size_type, typename R::value_type))
    FUNCTION(swap, void(R&))
    FUNCTION(swap, void(std_vectorbool_reference<R>, std_vectorbool_reference<R>))
    FUNCTION(flip)
    #endif // REW_FULLY_ENABLE
REFLECTABLE_INIT()

#endif // REW_BUILTIN_VECTOR_HPP
