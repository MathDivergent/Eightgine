#include <cstdio>

#if EIGHTGINE_DEBUG
#include <Eightest/Core.hpp>
#endif

extern "C" EMPTYPROJECTCORE_API void RegisterModule()
{
    printf("%s\n", "Hello, DLL!");
}

#if EIGHTGINE_DEBUG
TEST(Game, Test)
{
    EXPECT("Hello, World!", true);
}
#endif
