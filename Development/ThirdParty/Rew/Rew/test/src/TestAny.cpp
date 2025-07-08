#include <RewTestingBase.hpp>

#include <Rew/BuiltIn/any.hpp>

TEST(TestBuiltin, TestAny)
{
    auto type = rew::global.find("std::any");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "std::any");
    EXPECT("type-size", type->size == sizeof(std::any));
    EXPECT("type-context", type->context != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("reflection-name", reflection->name == "std::any");

    EXPECT("factory-R()", reflection->factory.find("std::any()") != nullptr);
    EXPECT("factory-R(R const&)", reflection->factory.find("std::any(std::any const&)") != nullptr);

    EXPECT("function-reset", reflection->function.find("reset") != nullptr);
    EXPECT("function-operator=", reflection->function.find("operator=") != nullptr);

    #ifdef REW_FULLY_ENABLE
    EXPECT("function-swap", reflection->function.find("swap") != nullptr);
    #endif // REW_FULLY_ENABLE

    EXPECT("function-has_value", reflection->function.find("has_value") != nullptr);
    EXPECT("function-type", reflection->function.find("type") != nullptr);
}
