#include <RewTestingBase.hpp>

#include <Rew/BuiltIn/array.hpp>

TEST(TestBuiltin, TestArray)
{
    rew::reflectable<std::array<int, 8>>();

    auto type = rew::global.find("std::array<int, 8>");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "std::array<int, 8>");
    EXPECT("type-size", type->size == sizeof(std::array<int, 8>));
    EXPECT("type-context", type->context != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("reflection-name", reflection->name == "std::array<int, 8>");

    EXPECT("factory-R()", reflection->factory.find("std::array<int, 8>()") != nullptr);
    EXPECT("factory-R(R const&)", reflection->factory.find("std::array<int, 8>(std::array<int, 8> const&)") != nullptr);

    #ifdef REW_FULLY_ENABLE
    ASSERT("function-at", reflection->function.find("at") != nullptr);
    #endif // REW_FULLY_ENABLE

    EXPECT("function-operator[]", reflection->function.find("operator[]") != nullptr);

    #ifdef REW_FULLY_ENABLE
    EXPECT("function-front", reflection->function.find("front") != nullptr);
    EXPECT("function-back", reflection->function.find("back") != nullptr);
    #endif // REW_FULLY_ENABLE

    EXPECT("function-data", reflection->function.find("data") != nullptr);

    #ifdef REW_FULLY_ENABLE
    EXPECT("function-begin", reflection->function.find("begin") != nullptr);
    EXPECT("function-cbegin", reflection->function.find("cbegin") != nullptr);
    EXPECT("function-end", reflection->function.find("end") != nullptr);
    EXPECT("function-cend", reflection->function.find("cend") != nullptr);
    EXPECT("function-rbegin", reflection->function.find("rbegin") != nullptr);
    EXPECT("function-crbegin", reflection->function.find("crbegin") != nullptr);
    EXPECT("function-rend", reflection->function.find("rend") != nullptr);
    EXPECT("function-crend", reflection->function.find("crend") != nullptr);
    #endif // REW_FULLY_ENABLE

    EXPECT("function-empty", reflection->function.find("empty") != nullptr);
    EXPECT("function-size", reflection->function.find("size") != nullptr);

    #ifdef REW_FULLY_ENABLE
    EXPECT("function-max_size", reflection->function.find("max_size") != nullptr);
    EXPECT("function-fill", reflection->function.find("fill") != nullptr);
    EXPECT("function-swap", reflection->function.find("swap") != nullptr);
    #endif // REW_FULLY_ENABLE
}
