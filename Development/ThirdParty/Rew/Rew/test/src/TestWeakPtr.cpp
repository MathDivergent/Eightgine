#include <RewTestingBase.hpp>

#include <Rew/BuiltIn/weak_ptr.hpp>

TEST(TestBuiltin, TestWseakPtr)
{
    rew::reflectable<std::weak_ptr<int>>();

    auto type = rew::global.find("std::weak_ptr<int>");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "std::weak_ptr<int>");
    EXPECT("type-size", type->size == sizeof(std::weak_ptr<int>));
    EXPECT("type-context", type->context != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("reflection-name", reflection->name == "std::weak_ptr<int>");

    EXPECT("factory-R()", reflection->factory.find("std::weak_ptr<int>()") != nullptr);
    EXPECT("factory-R(R const&)", reflection->factory.find("std::weak_ptr<int>(std::weak_ptr<int> const&)") != nullptr);
    EXPECT("factory-R(std::shared_ptr<element_type> const&)", reflection->factory.find("std::weak_ptr<int>(std::shared_ptr<int> const&)") != nullptr);

    EXPECT("function-operator=", reflection->function.find("operator=") != nullptr);
    EXPECT("function-reset", reflection->function.find("reset") != nullptr);

    #ifdef REW_FULLY_ENABLE
//  EXPECT("function-swap", reflection->function.find("swap") != nullptr);
    EXPECT("function-use_count", reflection->function.find("use_count") != nullptr);
    #endif // REW_FULLY_ENABLE

    EXPECT("function-expired", reflection->function.find("expired") != nullptr);
    EXPECT("function-lock", reflection->function.find("lock") != nullptr);

    #ifdef REW_FULLY_ENABLE
//  EXPECT("function-owner_before", reflection->function.find("owner_before") != nullptr);
    #endif // REW_FULLY_ENABLE
}
