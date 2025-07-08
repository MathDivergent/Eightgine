#include <Rew/BuiltIn/string.hpp>

template struct ::xxrew<std::string>;

template struct ::xxrew<std::wstring>;

#ifdef REW_FULLY_ENABLE
#if __cplusplus >= 202002L
template struct ::xxrew<std::u8string>;
#endif // if

template struct ::xxrew<std::u16string>;

template struct ::xxrew<std::u32string>;
#endif // REW_FULLY_ENABLE
