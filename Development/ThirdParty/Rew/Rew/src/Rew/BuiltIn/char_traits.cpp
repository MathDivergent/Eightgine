#include <Rew/BuiltIn/char_traits.hpp>

template struct ::xxrew<std::char_traits<char>>;

template struct ::xxrew<std::char_traits<wchar_t>>;

#ifdef REW_FULLY_ENABLE
#if __cplusplus >= 202002L
template struct ::xxrew<std::char_traits<char8_t>>;
#endif // if

template struct ::xxrew<std::char_traits<char16_t>>;

template struct ::xxrew<std::char_traits<char32_t>>;
#endif // REW_FULLY_ENABLE
