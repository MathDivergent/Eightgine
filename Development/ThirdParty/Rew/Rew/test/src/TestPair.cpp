#include <RewTestingBase.hpp>

#include <Rew/BuiltIn/pair.hpp>

TEST(TestBuiltin, TestPair)
{
    rew::reflectable<std::pair<int, float>>();

    auto type = rew::global.find("std::pair<int, float>");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "std::pair<int, float>");
    EXPECT("type-size", type->size == sizeof(std::pair<int, float>));
    EXPECT("type-context", type->context != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("reflection-name", reflection->name == "std::pair<int, float>");

    EXPECT("factory-R()", reflection->factory.find("std::pair<int, float>()") != nullptr);

    #ifdef REW_FULLY_ENABLE
    EXPECT("factory-R(first_type const&, second_type const&)", reflection->factory.find("std::pair<int, float>(int const&, float const&)") != nullptr);
    EXPECT("factory-R(R const&)", reflection->factory.find("std::pair<int, float>(std::pair<int, float> const&)") != nullptr);
    EXPECT("function-operator=", reflection->function.find("operator=") != nullptr);
    EXPECT("function-swap", reflection->function.find("swap") != nullptr);
    #endif // REW_FULLY_ENABLE

    EXPECT("property-first", reflection->property.find("first") != nullptr);
    EXPECT("property-second", reflection->property.find("second") != nullptr);
}
