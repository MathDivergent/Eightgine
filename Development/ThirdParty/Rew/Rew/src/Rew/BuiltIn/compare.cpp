#include <Rew/BuiltIn/compare.hpp>

#if __cplusplus > 201703L
REFLECTABLE(std::partial_ordering)
REFLECTABLE_INIT()

REFLECTABLE(std::weak_ordering)
REFLECTABLE_INIT()

REFLECTABLE(std::strong_ordering)
REFLECTABLE_INIT()
#endif // if
