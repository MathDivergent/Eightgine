#include <Rew/BuiltIn/typeinfo.hpp>

#include <Rew/Common.hpp>

REFLECTABLE(std::type_info)
    FUNCTION(operator==)

    #ifdef REW_FULLY_ENABLE
    FUNCTION(before)
    #endif // REW_CRE_MINIMAL

    FUNCTION(hash_code)
    FUNCTION(name)
REFLECTABLE_INIT()
