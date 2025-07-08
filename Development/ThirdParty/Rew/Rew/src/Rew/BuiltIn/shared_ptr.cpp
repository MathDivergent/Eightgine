#include <Rew/BuiltIn/shared_ptr.hpp>

REFLECTABLE(std::shared_ptr<void>)
    FACTORY(R())

    #ifdef REW_FULLY_ENABLE
    FACTORY(R(std::nullptr_t))
    #endif // REW_FULLY_ENABLE

    FACTORY(R(R const&))
    FUNCTION(operator=, R&(R const&))
    FUNCTION(reset, void())
    FUNCTION(get)

    #ifdef REW_FULLY_ENABLE
    FUNCTION(use_count)
    #endif // REW_FULLY_ENABLE

    FUNCTION(operator bool)
REFLECTABLE_INIT()
