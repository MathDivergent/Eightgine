#include <RewTestingBase.hpp>

#include <Rew/BuiltIn/reference_wrapper.hpp>

TEST(TestBuiltin, TestReferenceWrapper)
{
    rew::reflectable<std::reference_wrapper<int>>();

    auto type = rew::global.find("std::reference_wrapper<int>");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "std::reference_wrapper<int>");
    EXPECT("type-size", type->size == sizeof(std::reference_wrapper<int>));
    EXPECT("type-context", type->context != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("reflection-name", reflection->name == "std::reference_wrapper<int>");

    EXPECT("factory-R(value_type&)", reflection->factory.find("std::reference_wrapper<int>(int&)") != nullptr);
    EXPECT("factory-R(R const&)", reflection->factory.find("std::reference_wrapper<int>(std::reference_wrapper<int> const&)") != nullptr);

    EXPECT("function-operator=", reflection->function.find("operator=") != nullptr);

    #ifdef REW_FULLY_ENABLE
    EXPECT("function-operator value_type&", reflection->function.find("operator int&") != nullptr);
    #endif // REW_FULLY_ENABLE

    EXPECT("function-get", reflection->function.find("get") != nullptr);
}
