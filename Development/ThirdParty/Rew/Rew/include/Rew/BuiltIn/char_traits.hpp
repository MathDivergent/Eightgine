#ifndef REW_BUILTIN_CHAR_TRAITS_HPP
#define REW_BUILTIN_CHAR_TRAITS_HPP

#include <string> // char_traits

#include <Rew/Reflectable.hpp>
#include <Rew/Common.hpp>

TEMPLATE_REFLECTABLE_CLEAN
(
    template <typename CharType>,
    std::char_traits<CharType>, std::char_traits<rew::clean_of<CharType>>
)

REFLECTABLE_DECLARATION(std::char_traits<char>)
    BUILTIN_REFLECTABLE()
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE_DECLARATION(std::char_traits<wchar_t>)
    BUILTIN_REFLECTABLE()
REFLECTABLE_DECLARATION_INIT()

#ifdef REW_FULLY_ENABLE
#if __cplusplus >= 202002L
REFLECTABLE_DECLARATION(std::char_traits<char8_t>)
    BUILTIN_REFLECTABLE()
REFLECTABLE_DECLARATION_INIT()
#endif // if

REFLECTABLE_DECLARATION(std::char_traits<char16_t>)
   BUILTIN_REFLECTABLE()
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE_DECLARATION(std::char_traits<char32_t>)
    BUILTIN_REFLECTABLE()
REFLECTABLE_DECLARATION_INIT()
#endif // REW_FULLY_ENABLE

TEMPLATE_REFLECTABLE_DECLARATION(template <typename CharType>, std::char_traits<CharType>)
    BUILTIN_REFLECTABLE()
    REFLECTABLE_NAME("std::char_traits<" + rew::name_of<CharType>() + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE(template <typename CharType>, std::char_traits<CharType>)
    #ifdef REW_FULLY_ENABLE
    FUNCTION(assign, void(typename R::char_type&, typename R::char_type const&))
    FUNCTION(assign, typename R::char_type*(typename R::char_type*, std::size_t, typename R::char_type))
    FUNCTION(eq)
    FUNCTION(lt)
    FUNCTION(move)
    FUNCTION(copy)
    FUNCTION(compare)
    FUNCTION(length)
    FUNCTION(find)
    FUNCTION(to_char_type)
    FUNCTION(to_int_type)
    FUNCTION(eq_int_type)
    FUNCTION(eof)
    FUNCTION(not_eof)
    #endif // REW_FULLY_ENABLE
REFLECTABLE_INIT()

#endif // REW_BUILTIN_CHAR_TRAITS_HPP
