#include <Rew/Common.hpp>

// incomplete type
REFLECTABLE(void)
REFLECTABLE_INIT()

// nullptr type
REFLECTABLE(std::nullptr_t)
REFLECTABLE_INIT()

// aliasing
REFLECTABLE(std_size_t)
    FACTORY(R())
    FACTORY(R(R))
REFLECTABLE_INIT()

REFLECTABLE(std_ptrdiff_t)
    FACTORY(R())
    FACTORY(R(R))
REFLECTABLE_INIT()
// ~ aliasing

// boolean type
REFLECTABLE(bool)
    FACTORY(R())
    FACTORY(R(R))
REFLECTABLE_INIT()
// ~ boolean type

// char types
REFLECTABLE(char)
    FACTORY(R())
    FACTORY(R(R))
REFLECTABLE_INIT()

REFLECTABLE(wchar_t)
    FACTORY(R())
    FACTORY(R(R))
REFLECTABLE_INIT()

#if __cplusplus >= 202002L
REFLECTABLE(char8_t)
    FACTORY(R())
    FACTORY(R(R))
REFLECTABLE_INIT()
#endif // if

REFLECTABLE(char16_t)
    FACTORY(R())
    FACTORY(R(R))
REFLECTABLE_INIT()

REFLECTABLE(char32_t)
    FACTORY(R())
    FACTORY(R(R))
REFLECTABLE_INIT()
// ~ char types

// integral types
REFLECTABLE(signed char)
    FACTORY(R())
    FACTORY(R(R))
REFLECTABLE_INIT()

REFLECTABLE(unsigned char)
    FACTORY(R())
    FACTORY(R(R))
REFLECTABLE_INIT()

REFLECTABLE(short)
    FACTORY(R())
    FACTORY(R(R))
REFLECTABLE_INIT()

REFLECTABLE(unsigned short)
    FACTORY(R())
    FACTORY(R(R))
REFLECTABLE_INIT()

REFLECTABLE(int)
    FACTORY(R())
    FACTORY(R(R))
REFLECTABLE_INIT()

REFLECTABLE(unsigned int)
    FACTORY(R())
    FACTORY(R(R))
REFLECTABLE_INIT()

REFLECTABLE(long)
    FACTORY(R())
    FACTORY(R(R))
REFLECTABLE_INIT()

REFLECTABLE(unsigned long)
    FACTORY(R())
    FACTORY(R(R))
REFLECTABLE_INIT()

REFLECTABLE(long long)
    FACTORY(R())
    FACTORY(R(R))
REFLECTABLE_INIT()

REFLECTABLE(unsigned long long)
    FACTORY(R())
    FACTORY(R(R))
REFLECTABLE_INIT()
// ~ integral types

// floating point types
REFLECTABLE(float)
    FACTORY(R())
    FACTORY(R(R))
REFLECTABLE_INIT()

REFLECTABLE(double)
    FACTORY(R())
    FACTORY(R(R))
REFLECTABLE_INIT()

REFLECTABLE(long double)
    FACTORY(R())
    FACTORY(R(R))
REFLECTABLE_INIT()
// ~ floating point types
