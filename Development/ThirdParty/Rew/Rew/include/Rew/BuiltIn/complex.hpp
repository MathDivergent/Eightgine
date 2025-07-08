#ifndef REW_BUILTIN_COMPLEX_HPP
#define REW_BUILTIN_COMPLEX_HPP

#include <complex> // complex

#include <Rew/Reflectable.hpp>
#include <Rew/Common.hpp>

template <typename> struct xxrew_std_complex_pass_value;

template <typename ValueType>
struct xxrew_std_complex_pass_value<std::complex<ValueType>>
{
    using type = ValueType const&;
};

template <> struct xxrew_std_complex_pass_value<std::complex<float>> { using type = float; };
template <> struct xxrew_std_complex_pass_value<std::complex<double>> { using type = double; };
template <> struct xxrew_std_complex_pass_value<std::complex<long double>> { using type = long double; };

TEMPLATE_REFLECTABLE_CLEAN
(
    template <typename ValueType>,
    std::complex<ValueType>, std::complex<rew::clean_of<ValueType>>
)

TEMPLATE_REFLECTABLE_DECLARATION(template <typename ValueType>, std::complex<ValueType>)
    BUILTIN_REFLECTABLE()
    REFLECTABLE_NAME("std::complex<" + rew::name_of<ValueType>() + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE(template <typename ValueType>, std::complex<ValueType>)
    FACTORY(R())
    FACTORY(R(typename xxrew_std_complex_pass_value<R>::type, typename xxrew_std_complex_pass_value<R>::type))
    FACTORY(R(R const&))
    FUNCTION(operator=, R&(R const&))

    #ifdef REW_FULLY_ENABLE
    FUNCTION(operator+=, R&(typename xxrew_std_complex_pass_value<R>::type))
    #endif // REW_FULLY_ENABLE

    FUNCTION(operator+=, R&(R const&))

    #ifdef REW_FULLY_ENABLE
    FUNCTION(operator-=, R&(typename xxrew_std_complex_pass_value<R>::type))
    #endif // REW_FULLY_ENABLE

    FUNCTION(operator-=, R&(R const&))

    #ifdef REW_FULLY_ENABLE
    FUNCTION(operator*=, R&(typename xxrew_std_complex_pass_value<R>::type))
    #endif // REW_FULLY_ENABLE

    FUNCTION(operator*=, R&(R const&))

    #ifdef REW_FULLY_ENABLE
    FUNCTION(operator/=, R&(typename xxrew_std_complex_pass_value<R>::type))
    #endif // REW_FULLY_ENABLE

    FUNCTION(operator/=, R&(R const&))
    PROPERTY(real)
    PROPERTY(imag)
REFLECTABLE_INIT()

#endif // REW_BUILTIN_COMPLEX_HPP
