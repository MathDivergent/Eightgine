#include <RewTestingBase.hpp>

automation::registry_t* rew_testing_base()
{
    static automation::registry_t registry;
    return &registry;
}
