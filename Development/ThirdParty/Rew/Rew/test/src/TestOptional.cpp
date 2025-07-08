#include <RewTestingBase.hpp>

#include <Rew/BuiltIn/optional.hpp>

TEST(TestBuiltin, TestNulloptT)
{
    auto type = rew::global.find("std::nullopt_t");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "std::nullopt_t");
    EXPECT("type-size", type->size == sizeof(std::nullopt_t));
    EXPECT("type-context", type->context != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("reflection-name", reflection->name == "std::nullopt_t");
}

TEST(TestBuiltin, TestOptional)
{
    rew::reflectable<std::optional<int>>();

    auto type = rew::global.find("std::optional<int>");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "std::optional<int>");
    EXPECT("type-size", type->size == sizeof(std::optional<int>));
    EXPECT("type-context", type->context != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("reflection-name", reflection->name == "std::optional<int>");

    EXPECT("factory-R()", reflection->factory.find("std::optional<int>()") != nullptr);
    EXPECT("factory-R(std::nullopt_t)", reflection->factory.find("std::optional<int>(std::nullopt_t)") != nullptr);
    EXPECT("factory-R(R const&)", reflection->factory.find("std::optional<int>(std::optional<int> const&)") != nullptr);
    EXPECT("factory-R(value_type const&)", reflection->factory.find("std::optional<int>(int const&)") != nullptr);

    EXPECT("function-operator=", reflection->function.find("operator=") != nullptr);

    #ifdef REW_FULLY_ENABLE
    EXPECT("function-operator->", reflection->function.find("operator->") != nullptr);
    EXPECT("function-operator*", reflection->function.find("operator*") != nullptr);
    #endif // REW_FULLY_ENABLE

    EXPECT("function-operator bool", reflection->function.find("operator bool") != nullptr);

    #ifdef REW_FULLY_ENABLE
//  EXPECT("function-has_value", reflection->function.find("has_value") != nullptr);
    #endif // REW_FULLY_ENABLE

    EXPECT("function-value", reflection->function.find("value") != nullptr);

    #ifdef REW_FULLY_ENABLE
    EXPECT("function-value_or", reflection->function.find("value_or") != nullptr);
    EXPECT("function-swap", reflection->function.find("swap") != nullptr);
    #endif // REW_FULLY_ENABLE

//  EXPECT("function-reset", reflection->function.find("reset") != nullptr);
    EXPECT("function-emplace", reflection->function.find("emplace") != nullptr);
}
