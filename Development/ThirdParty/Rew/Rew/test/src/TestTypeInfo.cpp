#include <RewTestingBase.hpp>

#include <Rew/BuiltIn/typeinfo.hpp>

TEST(TestBuiltin, TestTypeInfo)
{
    auto type = rew::global.find("std::type_info");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "std::type_info");
    EXPECT("type-size", type->size == sizeof(std::type_info));
    EXPECT("type-context", type->context != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("reflection-name", reflection->name == "std::type_info");

    EXPECT("function-operator==", reflection->function.find("operator==") != nullptr);

    #ifdef REW_FULLY_ENABLE
    EXPECT("function-before", reflection->function.find("before") != nullptr);
    #endif // REW_FULLY_ENABLE

    EXPECT("function-hash_code", reflection->function.find("hash_code") != nullptr);
    EXPECT("function-name", reflection->function.find("name") != nullptr);
}
