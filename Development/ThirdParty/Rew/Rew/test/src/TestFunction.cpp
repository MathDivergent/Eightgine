#include <RewTestingBase.hpp>

#include <Rew/BuiltIn/function.hpp>

TEST(TestBuiltin, TestFunction)
{
    rew::reflectable<std::function<void(int, float)>>();

    auto type = rew::global.find("std::function<void(int, float)>");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "std::function<void(int, float)>");
    EXPECT("type-size", type->size == sizeof(std::function<void(int, float)>));
    EXPECT("type-context", type->context != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("reflection-name", reflection->name == "std::function<void(int, float)>");

    EXPECT("factory-R()", reflection->factory.find("std::function<void(int, float)>()") != nullptr);
    EXPECT("factory-R(std::nullptr_t)", reflection->factory.find("std::function<void(int, float)>(std::nullptr_t)") != nullptr);
    EXPECT("factory-R(R const&)", reflection->factory.find("std::function<void(int, float)>(std::function<void(int, float)> const&)") != nullptr);

    EXPECT("function-operator=", reflection->function.find("operator=") != nullptr);

    #ifdef REW_FULLY_ENABLE
    EXPECT("function-swap", reflection->function.find("swap") != nullptr);
    #endif // REW_FULLY_ENABLE

    EXPECT("function-operator bool", reflection->function.find("operator bool") != nullptr);
    EXPECT("function-operator()", reflection->function.find("operator()") != nullptr);

    #ifdef REW_FULLY_ENABLE
    EXPECT("function-target_type", reflection->function.find("target_type") != nullptr);
    #endif // REW_FULLY_ENABLE
}
