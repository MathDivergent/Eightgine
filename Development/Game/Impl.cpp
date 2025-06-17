#include <cstdio>

#include <Automation/Core.hpp>

extern "C" void RegisterModule()
{
    printf("%s\n", "Hello, DLL!");
}

TEST(Game, Test)
{
    EXPECT("Hello, World!", true);
}
