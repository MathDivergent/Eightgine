#include <Rew/BuiltIn/any.hpp>

#include <Rew/Common.hpp>

// as function return type
#include <Rew/BuiltIn/typeinfo.hpp>

REFLECTABLE(std::any)
    FACTORY(R())
    FACTORY(R(R const&))
    FUNCTION(operator=, R&(R const&))
    FUNCTION(reset)

    #ifdef REW_FULLY_ENABLE
    FUNCTION(swap)
    #endif // REW_FULLY_ENABLE

    FUNCTION(has_value)
    FUNCTION(type)
REFLECTABLE_INIT()
