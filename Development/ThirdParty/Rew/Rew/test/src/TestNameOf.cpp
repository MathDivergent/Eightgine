#include <RewTestingBase.hpp>

TEST(TestLibrary, TestNameOf)
{
    EXPECT("const-type", rew::name_of<const int>() == "int const");
    EXPECT("pointer-type", rew::name_of<int*>() == "int*");
    EXPECT("const_pointer-type", rew::name_of<int* const>() == "int* const");
    EXPECT("reference-type", rew::name_of<int&>() == "int&");
    EXPECT("function-type", rew::name_of<void(int, float)>() == "void(int, float)");
    EXPECT("function-pointer-type", rew::name_of<void(*)(int, float)>() == "std::type_identity_t<void(int, float)>*");
    EXPECT("function-reference-type", rew::name_of<void(&)(int, float)>() == "std::type_identity_t<void(int, float)>&");
    EXPECT("const-qualified_function-type", rew::name_of<void(int, float) const>() == "void(int, float) const");
    EXPECT("reference-qualified_function-type", rew::name_of<void(int, float)&>() == "void(int, float)&");
    EXPECT("const-reference_qualified_function-type", rew::name_of<void(int, float) const&>() == "void(int, float) const&");
    EXPECT("array-type", rew::name_of<int[8]>() == "int[8]");
    EXPECT("array-pointer-type", rew::name_of<int(*)[8]>() == "std::type_identity_t<int[8]>*");
    EXPECT("array-reference-type", rew::name_of<int(&)[8]>() == "std::type_identity_t<int[8]>&");
    EXPECT("mixed-type0", rew::name_of<char(*(* const*&)[8])(void)>() == "std::type_identity_t<std::type_identity_t<char()>*[8]>* const*&");
    EXPECT("mixed-type1", rew::name_of<bool*(** const* (* const&)(void*, long))[3]>() == "std::type_identity_t<std::type_identity_t<bool*[3]>** const*(void*, long)>* const&");
}

// Patterns:
// array<T, N> ~ T[N]
// array<T, N>& ~ T(&)[N]
// array<T, N> const& ~ T( const&)[N]
// array<T, N>* ~ T(*)[N]
// array<T, N> const* ~ T( const*)[N]
// array<T, N>* const ~ T(* const)[N]
// array<T, N> const* const ~ T( const* const)[N]

// function<R(Args...)>& ~ R(&)(Args...)
// function<R(Args...)> const& ~ R( const&)(Args...)
// function<R(Args...) ~ R(Args...)
// function<R(Args...)>* ~ R(*)(Args...)
// function<R(Args...)> const* ~ R( const*)(Args...)
// function<R(Args...)>* const ~ R(* const)(Args...)
// function<R(Args...)> const* const ~ R( const* const)(Args...)

// Pointers/References as T/R:
// if T is type pointer/reference of function or array,
// we should wrapp Pattern to '(' and ')' braces, examples:
// array<array<T, InnerN>*, N>* ~ T(*(*)[N])[InnerN]
// array<function<R(Args...)>*, N>* ~ R(*(*)[N])(Args...)

// if R is type pointer/reference of function or array,
// we should wrapp Pattern to '(' and ')' braces, examples:
// function<function<R(InnerArgs...)>*(Args...)>* ~ InnerR(*(*)(Args...))(InnerArgs...)
// function<array<T, N>*(Args...)>* ~ T(*(*)(Args...))[N]
