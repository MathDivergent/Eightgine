#include <cstdio>

#include <Eightest/Eightest.hpp>

extern "C" EMPTYPROJECT_API void RegisterModule()
{
    printf("%s\n", "Hello, DLL!");
}

#if EIGHTGINE_DEBUG
TEST(Game, Test)
{
    EXPECT("Hello, World!", true);
}
#endif
