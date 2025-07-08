#ifndef REW_BUILTIN_STRING_HPP
#define REW_BUILTIN_STRING_HPP

#define REW_CORE_MINIMAL

#include <string> // basic_string

#include <Rew/Reflectable.hpp>
#include <Rew/Common.hpp>

// default allocator for basic_string
#include <Rew/BuiltIn/allocator.hpp>

#ifdef REW_FULLY_ENABLE
// as function argument type
#include <Rew/BuiltIn/initializer_list.hpp>
#include <Rew/BuiltIn/iterator.hpp>
#endif // REW_FULLY_ENABLE

// as traits type
#include <Rew/BuiltIn/char_traits.hpp>

TEMPLATE_REFLECTABLE_CLEAN
(
    (template <typename CharType, typename TraitsType, typename AllocatorType>),
    (std::basic_string<CharType, TraitsType, AllocatorType>),
    std::basic_string<rew::clean_of<CharType>, rew::clean_of<TraitsType>, rew::clean_of<AllocatorType>>
)

REFLECTABLE_DECLARATION(std::string)
    BUILTIN_REFLECTABLE()
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE_DECLARATION(std::wstring)
    BUILTIN_REFLECTABLE()
REFLECTABLE_DECLARATION_INIT()

#ifdef REW_FULLY_ENABLE
#if __cplusplus >= 202002L
REFLECTABLE_DECLARATION(std::u8string)
    BUILTIN_REFLECTABLE()
REFLECTABLE_DECLARATION_INIT()
#endif // if

REFLECTABLE_DECLARATION(std::u16string)
    BUILTIN_REFLECTABLE()
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE_DECLARATION(std::u32string)
    BUILTIN_REFLECTABLE()
REFLECTABLE_DECLARATION_INIT()
#endif // REW_FULLY_ENABLE

TEMPLATE_REFLECTABLE_DECLARATION(template <typename CharType>, std::basic_string<CharType>)
    BUILTIN_REFLECTABLE()
    REFLECTABLE_NAME("std::basic_string<" + rew::name_of<CharType>() + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE_DECLARATION((template <typename CharType, typename TraitsType>), std::basic_string<CharType, TraitsType>)
    BUILTIN_REFLECTABLE()
    REFLECTABLE_NAME("std::basic_string<" + rew::name_of<CharType>() + ", " + rew::name_of<TraitsType>() + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE_DECLARATION
(
    (template <typename CharType, typename TraitsType, typename AllocatorType>),
    std::basic_string<CharType, TraitsType, AllocatorType>
)
    BUILTIN_REFLECTABLE()
    REFLECTABLE_NAME("std::basic_string<" + rew::name_of<CharType>() + ", " + rew::name_of<TraitsType>() + ", " + rew::name_of<AllocatorType>() + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE
(
    (template <typename CharType, typename TraitsType, typename AllocatorType>),
    std::basic_string<CharType, TraitsType, AllocatorType>
)
    FACTORY(R())

    #ifdef REW_FULLY_ENABLE
    FACTORY(R(typename R::allocator_type const&))
    FACTORY(R(typename R::size_type, typename R::value_type, typename R::allocator_type const&))
    FACTORY(R(typename R::size_type, typename R::value_type))
    FACTORY(R(R const&, typename R::size_type, typename R::size_type, typename R::allocator_type const&))
    FACTORY(R(R const&, typename R::size_type, typename R::size_type))
    FACTORY(R(typename R::value_type const*, typename R::size_type, typename R::allocator_type const&))
    FACTORY(R(typename R::value_type const*, typename R::size_type))
    FACTORY(R(typename R::value_type const*, typename R::allocator_type const&))
    FACTORY(R(typename R::value_type const*))
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
    FUNCTION(operator=, R&(typename R::value_type const*))
    FUNCTION(operator=, R&(typename R::value_type))
    FUNCTION(operator=, R&(std::initializer_list<typename R::value_type>))
    FUNCTION(assign, R&(typename R::size_type, typename R::value_type))
    FUNCTION(assign, R&(R const&))
    FUNCTION(assign, R&(R const&, typename R::size_type, typename R::size_type))
    FUNCTION(assign, R&(typename R::value_type const*, typename R::size_type))
    FUNCTION(assign, R&(typename R::value_type const*))
    FUNCTION(assign, R&(std_const_iterator<R>, std_const_iterator<R>))
    FUNCTION(assign, R&(std::initializer_list<typename R::value_type>))
    FUNCTION(get_allocator)
    FUNCTION(at, typename R::reference(typename R::size_type))
    FUNCTION(at, typename R::const_reference(typename R::size_type) const)
    #endif // REW_FULLY_ENABLE

    FUNCTION(operator[], typename R::reference(typename R::size_type))
    FUNCTION(operator[], typename R::const_reference(typename R::size_type) const)

    #ifdef REW_FULLY_ENABLE
    FUNCTION(front, typename R::reference())
    FUNCTION(front, typename R::const_reference() const)
    FUNCTION(back, typename R::reference())
    FUNCTION(back, typename R::const_reference() const)
    #endif // REW_FULLY_ENABLE

    FUNCTION(data, typename R::value_type const*() const)

#if __cplusplus >= 201703L
    FUNCTION(data, typename R::value_type*())
#endif // if

    #ifdef REW_FULLY_ENABLE
    FUNCTION(c_str)
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
    FUNCTION(length)
    FUNCTION(max_size)
    #endif // REW_FULLY_ENABLE

    FUNCTION(reserve, void(typename R::size_type))
    FUNCTION(capacity)

    #ifdef REW_FULLY_ENABLE
    FUNCTION(shrink_to_fit)
    #endif // REW_FULLY_ENABLE

    FUNCTION(clear)

    #ifdef REW_FULLY_ENABLE
    FUNCTION(insert, R&(typename R::size_type, typename R::size_type, typename R::value_type))
    FUNCTION(insert, R&(typename R::size_type, typename R::value_type const*))
    FUNCTION(insert, R&(typename R::size_type, typename R::value_type const*, typename R::size_type))
    FUNCTION(insert, R&(typename R::size_type, R const&))
    FUNCTION(insert, R&(typename R::size_type, R const&, typename R::size_type, typename R::size_type))
    FUNCTION(insert, std_iterator<R>(std_const_iterator<R>, typename R::value_type))
    FUNCTION(insert, std_iterator<R>(std_const_iterator<R>, typename R::size_type, typename R::value_type))
    FUNCTION(insert, std_iterator<R>(std_const_iterator<R>, std::initializer_list<typename R::value_type>))
    FUNCTION(erase, R&(typename R::size_type, typename R::size_type))
    FUNCTION(erase, std_iterator<R>(std_const_iterator<R>))
    FUNCTION(erase, std_iterator<R>(std_const_iterator<R>, std_const_iterator<R>))
    #endif // REW_FULLY_ENABLE

    FUNCTION(push_back)
    FUNCTION(pop_back)

    #ifdef REW_FULLY_ENABLE
    FUNCTION(append, R&(typename R::size_type, typename R::value_type))
    FUNCTION(append, R&(R const&))
    FUNCTION(append, R&(R const&, typename R::size_type, typename R::size_type))
    FUNCTION(append, R&(typename R::value_type const*, typename R::size_type))
    FUNCTION(append, R&(typename R::value_type const*))
    FUNCTION(append, R&(std_const_iterator<R>, std_const_iterator<R>))
    FUNCTION(append, R&(std::initializer_list<typename R::value_type>))
    FUNCTION(operator+=, R&(R const&))
    FUNCTION(operator+=, R&(typename R::value_type))
    FUNCTION(operator+=, R&(typename R::value_type const*))
    FUNCTION(operator+=, R&(std::initializer_list<typename R::value_type>))
    #endif // REW_FULLY_ENABLE

    FUNCTION(replace, R&(typename R::size_type, typename R::size_type, R const&))

    #ifdef REW_FULLY_ENABLE
    FUNCTION(replace, R&(std_const_iterator<R>, std_const_iterator<R>, R const&))
    FUNCTION(replace, R&(typename R::size_type, typename R::size_type, R const&, typename R::size_type, typename R::size_type))
    FUNCTION(replace, R&(typename R::size_type, typename R::size_type, typename R::value_type const*, typename R::size_type))
    FUNCTION(replace, R&(std_const_iterator<R>, std_const_iterator<R>, typename R::value_type const*, typename R::size_type))
    FUNCTION(replace, R&(typename R::size_type, typename R::size_type, typename R::value_type const*))
    FUNCTION(replace, R&(std_const_iterator<R>, std_const_iterator<R>, typename R::value_type const*))
    FUNCTION(replace, R&(typename R::size_type, typename R::size_type, typename R::size_type, typename R::value_type))
    FUNCTION(replace, R&(std_const_iterator<R>, std_const_iterator<R>, typename R::size_type, typename R::value_type))
    FUNCTION(replace, R&(std_const_iterator<R>, std_const_iterator<R>, std_const_iterator<R>, std_const_iterator<R>))
    FUNCTION(replace, R&(std_const_iterator<R>, std_const_iterator<R>, std::initializer_list<typename R::value_type>))
    FUNCTION(copy)
    #endif // REW_FULLY_ENABLE

    FUNCTION(resize, void(typename R::size_type))

    #ifdef REW_FULLY_ENABLE
    FUNCTION(resize, void(typename R::size_type, typename R::value_type))
    FUNCTION(swap)
    #endif // REW_FULLY_ENABLE
    
    FUNCTION(find, typename R::size_type(R const&, typename R::size_type) const)

    #ifdef REW_FULLY_ENABLE
    FUNCTION(find, typename R::size_type(typename R::value_type const*, typename R::size_type, typename R::size_type) const)
    FUNCTION(find, typename R::size_type(typename R::value_type const*, typename R::size_type) const)
    FUNCTION(find, typename R::size_type(typename R::value_type, typename R::size_type) const)
    FUNCTION(rfind, typename R::size_type(R const&, typename R::size_type) const)
    FUNCTION(rfind, typename R::size_type(typename R::value_type const*, typename R::size_type, typename R::size_type) const)
    FUNCTION(rfind, typename R::size_type(typename R::value_type const*, typename R::size_type) const)
    FUNCTION(rfind, typename R::size_type(typename R::value_type, typename R::size_type) const)
    FUNCTION(find_first_of, typename R::size_type(R const&, typename R::size_type) const)
    FUNCTION(find_first_of, typename R::size_type(typename R::value_type const*, typename R::size_type, typename R::size_type) const)
    FUNCTION(find_first_of, typename R::size_type(typename R::value_type const*, typename R::size_type) const)
    FUNCTION(find_first_of, typename R::size_type(typename R::value_type, typename R::size_type) const)
    FUNCTION(find_first_not_of, typename R::size_type(R const&, typename R::size_type) const)
    FUNCTION(find_first_not_of, typename R::size_type(typename R::value_type const*, typename R::size_type, typename R::size_type) const)
    FUNCTION(find_first_not_of, typename R::size_type(typename R::value_type const*, typename R::size_type) const)
    FUNCTION(find_first_not_of, typename R::size_type(typename R::value_type, typename R::size_type) const)
    FUNCTION(find_last_of, typename R::size_type(R const&, typename R::size_type) const)
    FUNCTION(find_last_of, typename R::size_type(typename R::value_type const*, typename R::size_type, typename R::size_type) const)
    FUNCTION(find_last_of, typename R::size_type(typename R::value_type const*, typename R::size_type) const)
    FUNCTION(find_last_of, typename R::size_type(typename R::value_type, typename R::size_type) const)
    FUNCTION(find_last_not_of, typename R::size_type(R const&, typename R::size_type) const)
    FUNCTION(find_last_not_of, typename R::size_type(typename R::value_type const*, typename R::size_type, typename R::size_type) const)
    FUNCTION(find_last_not_of, typename R::size_type(typename R::value_type const*, typename R::size_type) const)
    FUNCTION(find_last_not_of, typename R::size_type(typename R::value_type, typename R::size_type) const)
    #endif // REW_FULLY_ENABLE

    FUNCTION(compare, int(R const&) const)

    #ifdef REW_FULLY_ENABLE
    FUNCTION(compare, int(typename R::size_type, typename R::size_type, R const&) const)
    FUNCTION(compare, int(typename R::size_type, typename R::size_type, R const&, typename R::size_type, typename R::size_type) const)
    FUNCTION(compare, int(typename R::value_type const*) const)
    FUNCTION(compare, int(typename R::size_type, typename R::size_type, typename R::value_type const*) const)
    FUNCTION(compare, int(typename R::size_type, typename R::size_type, typename R::value_type const*, typename R::size_type) const)
    #endif // REW_FULLY_ENABLE

#if __cplusplus >= 202002L
    #ifdef REW_FULLY_ENABLE
    FUNCTION(starts_with, bool(typename R::value_type) const)
    FUNCTION(starts_with, bool(typename R::value_type const*) const)
    FUNCTION(ends_with, bool(typename R::value_type) const)
    FUNCTION(ends_with, bool(typename R::value_type const*) const)
    #endif // REW_FULLY_ENABLE
#endif // if

    FUNCTION(substr, R(typename R::size_type, typename R::size_type) const)
REFLECTABLE_INIT()

#endif // REW_BUILTIN_STRING_HPP
