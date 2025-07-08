#ifndef REW_BUILTIN_BITSET_HPP
#define REW_BUILTIN_BITSET_HPP

#include <string> // to_string

#include <bitset> // bitest

#include <Rew/Reflectable.hpp>
#include <Rew/Common.hpp>

// as function argument tye
#include <Rew/BuiltIn/string.hpp>

#ifdef REW_FULLY_ENABLE
TEMPLATE_REFLECTABLE_USING
(
    template <class StdBitsetType>, std_bitset_reference,
    std_bitset_reference<StdBitsetType>, typename rew::clean_of<StdBitsetType>::reference
)

TEMPLATE_REFLECTABLE_DECLARATION(template <class StdBitsetType>, std_bitset_reference<StdBitsetType>)
    BUILTIN_REFLECTABLE()
    REFLECTABLE_NAME(rew::name_of<StdBitsetType>() + "::reference")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE(template <class StdBitsetType>, std_bitset_reference<StdBitsetType>)
    FUNCTION(operator=, R&(bool))

    #ifdef REW_FULLY_ENABLE
    FUNCTION(operator=, R&(R const&))
    #endif // REW_FULLY_ENABLE

    FUNCTION(operator bool)

    #ifdef REW_FULLY_ENABLE
    FUNCTION(operator~)
    #endif // REW_FULLY_ENABLE

    FUNCTION(flip, R&())
REFLECTABLE_INIT()
#endif // REW_FULLY_ENABLE

TEMPLATE_REFLECTABLE_DECLARATION(template <std::size_t SizeValue>, std::bitset<SizeValue>)
    BUILTIN_REFLECTABLE()
    REFLECTABLE_NAME("std::bitset<" + std::to_string(SizeValue) + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE(template <std::size_t SizeValue>, std::bitset<SizeValue>)
    FACTORY(R())
    FACTORY(R(R const&))

    #ifdef REW_FULLY_ENABLE
    FACTORY(R(unsigned long))
    #endif // REW_FULLY_ENABLE

    FACTORY(R(unsigned long long))

    #ifdef REW_FULLY_ENABLE
    FACTORY(R(std::string const&, std_size_t))
    #endif // REW_FULLY_ENABLE

    FACTORY(R(std::string const&))

    #ifdef REW_FULLY_ENABLE
    FACTORY(R(char const*, std_size_t))
    FACTORY(R(char const*))
    #endif // REW_FULLY_ENABLE

    FUNCTION(operator=, R&(R const&))
    FUNCTION(operator==)

    #ifdef REW_FULLY_ENABLE
//  FUNCTION(operator[], bool(std_size_t) const)
//  FUNCTION(operator[], std_bitset_reference<R>(std_size_t))
    #endif // REW_FULLY_ENABLE

    FUNCTION(test)

    #ifdef REW_FULLY_ENABLE
    FUNCTION(all)
    FUNCTION(any)
    FUNCTION(none)
    FUNCTION(count)
    FUNCTION(size)
    FUNCTION(operator&=)
    FUNCTION(operator|=)
    FUNCTION(operator^=)
    FUNCTION(operator~)
    FUNCTION(operator<<)
    FUNCTION(operator<<=)
    FUNCTION(operator>>)
    FUNCTION(operator>>=)
    FUNCTION(set, R&())
    #endif // REW_FULLY_ENABLE

    FUNCTION(set, R&(std_size_t, bool))

    #ifdef REW_FULLY_ENABLE
    FUNCTION(reset, R&())
    #endif // REW_FULLY_ENABLE

    FUNCTION(reset, R&(std_size_t))

    #ifdef REW_FULLY_ENABLE
    FUNCTION(flip, R&())
    #endif // REW_FULLY_ENABLE

    FUNCTION(flip, R&(std_size_t))
    FUNCTION(to_string, std::string(char, char) const)

    #ifdef REW_FULLY_ENABLE
    FUNCTION(to_ulong)
    #endif // REW_FULLY_ENABLE

    FUNCTION(to_ullong)
REFLECTABLE_INIT()

#endif // REW_BUILTIN_BITSET_HPP
