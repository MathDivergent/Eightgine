#include <RewTestingBase.hpp>

#include <Rew/BuiltIn/allocator.hpp>

TEST(TestBuiltin, TestAllocator)
{
    rew::reflectable<std::allocator<int>>();

    auto type = rew::global.find("std::allocator<int>");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "std::allocator<int>");
    EXPECT("type-size", type->size == sizeof(std::allocator<int>));
    EXPECT("type-context", type->context != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("reflection-name", reflection->name == "std::allocator<int>");

    EXPECT("factory-R()", reflection->factory.find("std::allocator<int>()") != nullptr);
    EXPECT("factory-R(R const&)", reflection->factory.find("std::allocator<int>(std::allocator<int> const&)") != nullptr);
}
