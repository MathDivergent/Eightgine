#include <RewTestingBase.hpp>

#include <Rew/BuiltIn/bitset.hpp>

TEST(TestBuiltin, TestBitset)
{
    rew::reflectable<std::bitset<128>>();

    auto type = rew::global.find("std::bitset<128>");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "std::bitset<128>");
    EXPECT("type-size", type->size == sizeof(std::bitset<128>));
    EXPECT("type-context", type->context != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("reflection-name", reflection->name == "std::bitset<128>");

    EXPECT("factory-R()", reflection->factory.find("std::bitset<128>()") != nullptr);
    EXPECT("factory-R(R const&)", reflection->factory.find("std::bitset<128>(std::bitset<128> const&)") != nullptr);

    #ifdef REW_FULLY_ENABLE
    EXPECT("factory-R(unsigned long)", reflection->factory.find("std::bitset<128>(unsigned long)") != nullptr);
    #endif // REW_FULLY_ENABLE

    EXPECT("factory-R(unsigned long long)", reflection->factory.find("std::bitset<128>(unsigned long long)") != nullptr);

    #ifdef REW_FULLY_ENABLE
    EXPECT("factory-R(std::string const&, std::size_t)", reflection->factory.find("std::bitset<128>(std::string const&, std::size_t)") != nullptr);
    #endif // REW_FULLY_ENABLE

    EXPECT("factory-R(std::string const&)", reflection->factory.find("std::bitset<128>(std::string const&)") != nullptr);

    #ifdef REW_FULLY_ENABLE
    EXPECT("factory-R(char const*, std::size_t)", reflection->factory.find("std::bitset<128>(char const*, std::size_t)") != nullptr);
    EXPECT("factory-R(char const*)", reflection->factory.find("std::bitset<128>(char const*)") != nullptr);
    #endif // REW_FULLY_ENABLE

    ASSERT("function-operator=", reflection->function.find("operator=") != nullptr);
    ASSERT("function-operator==", reflection->function.find("operator==") != nullptr);

    #ifdef REW_FULLY_ENABLE
//  ASSERT("function-operator[]", reflection->function.find("operator[]") != nullptr);
    #endif // REW_FULLY_ENABLE

    EXPECT("function-test", reflection->function.find("test") != nullptr);

    #ifdef REW_FULLY_ENABLE
    EXPECT("function-all", reflection->function.find("all") != nullptr);
    EXPECT("function-any", reflection->function.find("any") != nullptr);
    EXPECT("function-none", reflection->function.find("none") != nullptr);
    EXPECT("function-count", reflection->function.find("count") != nullptr);
    EXPECT("function-size", reflection->function.find("size") != nullptr);
    EXPECT("function-operator&=", reflection->function.find("operator&=") != nullptr);
    EXPECT("function-operator|=", reflection->function.find("operator|=") != nullptr);
    EXPECT("function-operator^=", reflection->function.find("operator^=") != nullptr);
    EXPECT("function-operator~", reflection->function.find("operator~") != nullptr);
    EXPECT("function-operator<<", reflection->function.find("operator<<") != nullptr);
    EXPECT("function-operator<<=", reflection->function.find("operator<<=") != nullptr);
    EXPECT("function-operator>>", reflection->function.find("operator>>") != nullptr);
    EXPECT("function-operator>>=", reflection->function.find("operator>>=") != nullptr);
    #endif // REW_FULLY_ENABLE

    EXPECT("function-set", reflection->function.find("set") != nullptr);
    EXPECT("function-reset", reflection->function.find("reset") != nullptr);
    EXPECT("function-flip", reflection->function.find("flip") != nullptr);
    EXPECT("function-to_string", reflection->function.find("to_string") != nullptr);

    #ifdef REW_FULLY_ENABLE
    EXPECT("function-to_ulong", reflection->function.find("to_ulong") != nullptr);
    #endif // REW_FULLY_ENABLE

    EXPECT("function-to_ullong", reflection->function.find("to_ullong") != nullptr);
}
