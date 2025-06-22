#include <cstdio>

#include <Automation/Core.hpp>

extern "C" EMPTYPROJECT_API void RegisterModule()
{
    printf("%s\n", "Hello, DLL!");
}

TEST(Game, Test)
{
    EXPECT("Hello, World!", true);
}
