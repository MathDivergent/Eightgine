#include <RewTestingBase.hpp>

#include <Rew/BuiltIn/initializer_list.hpp>

TEST(TestBuiltin, TestInitializerList)
{
    rew::reflectable<std::initializer_list<int>>();

    auto type = rew::global.find("std::initializer_list<int>");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "std::initializer_list<int>");
    EXPECT("type-size", type->size == sizeof(std::initializer_list<int>));
    EXPECT("type-context", type->context != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("reflection-name", reflection->name == "std::initializer_list<int>");

    EXPECT("factory-R()", reflection->factory.find("std::initializer_list<int>()") != nullptr);
    EXPECT("factory-R(R const&)", reflection->factory.find("std::initializer_list<int>(std::initializer_list<int> const&)") != nullptr);

    EXPECT("function-operator=", reflection->function.find("operator=") != nullptr);

    #ifdef REW_FULLY_ENABLE
    EXPECT("function-begin", reflection->function.find("begin") != nullptr);
    EXPECT("function-end", reflection->function.find("end") != nullptr);
    #endif // REW_FULLY_ENABLE

    EXPECT("function-size", reflection->function.find("size") != nullptr);
}
