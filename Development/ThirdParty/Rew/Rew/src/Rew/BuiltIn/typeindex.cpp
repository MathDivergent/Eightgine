#include <Rew/BuiltIn/typeindex.hpp>

#include <Rew/Common.hpp>

// as function argument type
#include <Rew/BuiltIn/typeinfo.hpp>

#if __cplusplus > 201703L
#include <Rew/BuiltIn/compare.hpp>
#endif // if

REFLECTABLE(std::type_index)
    FACTORY(R(std::type_info const&))

#if __cplusplus > 201703L
    FUNCTION(operator<=>)
#else
    FUNCTION(operator==)
    FUNCTION(operator!=)

    #ifdef REW_FULLY_ENABLE
    FUNCTION(operator<)
    FUNCTION(operator<=)
    FUNCTION(operator>)
    FUNCTION(operator>=)
    #endif // REW_FULLY_ENABLE
#endif // if
    FUNCTION(hash_code)
    FUNCTION(name)
REFLECTABLE_INIT()
