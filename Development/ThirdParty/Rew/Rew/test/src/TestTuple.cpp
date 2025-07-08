#include <RewTestingBase.hpp>

#include <Rew/BuiltIn/tuple.hpp>

TEST(TestBuiltin, TestTuple)
{
    rew::reflectable<std::tuple<int, float, bool>>();

    auto type = rew::global.find("std::tuple<int, float, bool>");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "std::tuple<int, float, bool>");
    EXPECT("type-size", type->size == sizeof(std::tuple<int, float, bool>));
    EXPECT("type-context", type->context != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("reflection-name", reflection->name == "std::tuple<int, float, bool>");

    EXPECT("factory-R()", reflection->factory.find("std::tuple<int, float, bool>()") != nullptr);
    EXPECT("factory-R(R const&)", reflection->factory.find("std::tuple<int, float, bool>(std::tuple<int, float, bool> const&)") != nullptr);
    EXPECT("factory-R(Args...)", reflection->factory.find("std::tuple<int, float, bool>(int, float, bool)") != nullptr);

    EXPECT("function-operator=", reflection->function.find("operator=") != nullptr);

    #ifdef REW_FULLY_ENABLE
    EXPECT("function-swap", reflection->function.find("swap") != nullptr);
    #endif // REW_FULLY_ENABLE
}
