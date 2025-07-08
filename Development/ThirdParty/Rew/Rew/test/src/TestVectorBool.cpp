#include <RewTestingBase.hpp>

#include <Rew/BuiltIn/vector.hpp>

TEST(TestBuiltin, TestVectorBool)
{
    rew::reflectable<std::vector<bool>>();

    auto type = rew::global.find("std::vector<bool>");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "std::vector<bool>");
    EXPECT("type-size", type->size == sizeof(std::vector<bool>));
    EXPECT("type-context", type->context != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("reflection-name", reflection->name == "std::vector<bool>");

    EXPECT("factory-R()", reflection->factory.find("std::vector<bool>()") != nullptr);

    #ifdef REW_FULLY_ENABLE
    EXPECT("factory-R(allocator_type const&)", reflection->factory.find("std::vector<bool>(std::allocator<bool> const&)") != nullptr);
    EXPECT("factory-R(size_type, const_reference, allocator_type const&)", reflection->factory.find("std::vector<bool>(unsigned long, std::vector<bool>::const_reference, std::allocator<bool> const&)") != nullptr || reflection->factory.find("std::vector<bool>(unsigned long long, std::vector<bool>::const_reference, std::allocator<bool> const&)") != nullptr);
    EXPECT("factory-R(size_type, const_reference)", reflection->factory.find("std::vector<bool>(unsigned long, std::vector<bool>::const_reference)") != nullptr || reflection->factory.find("std::vector<bool>(unsigned long long, std::vector<bool>::const_reference)") != nullptr);
    EXPECT("factory-R(size_type, allocator_type const&)", reflection->factory.find("std::vector<bool>(unsigned long, std::allocator<bool> const&)") != nullptr || reflection->factory.find("std::vector<bool>(unsigned long long, std::allocator<bool> const&)") != nullptr);
    EXPECT("factory-R(size_type)", reflection->factory.find("std::vector<bool>(unsigned long)") != nullptr || reflection->factory.find("std::vector<bool>(unsigned long long)") != nullptr);
    EXPECT("factory-R(const_iterator, const_iterator, allocator_type const&)", reflection->factory.find("std::vector<bool>(std::vector<bool>::const_iterator, std::vector<bool>::const_iterator, std::allocator<bool> const&)") != nullptr);
    EXPECT("factory-R(const_iterator, const_iterator)", reflection->factory.find("std::vector<bool>(std::vector<bool>::const_iterator, std::vector<bool>::const_iterator)") != nullptr);
    EXPECT("factory-R(R const&, allocator_type const&)", reflection->factory.find("std::vector<bool>(std::vector<bool> const&, std::allocator<bool> const&)") != nullptr);
    #endif // REW_FULLY_ENABLE

    EXPECT("factory-R(R const&)", reflection->factory.find("std::vector<bool>(std::vector<bool> const&)") != nullptr);

    #ifdef REW_FULLY_ENABLE
    EXPECT("factory-R(std::initializer_list<value_type>, allocator_type const&)", reflection->factory.find("std::vector<bool>(std::initializer_list<bool>, std::allocator<bool> const&)") != nullptr);
    EXPECT("factory-R(std::initializer_list<value_type>)", reflection->factory.find("std::vector<bool>(std::initializer_list<bool>)") != nullptr);
    #endif // REW_FULLY_ENABLE

    EXPECT("function-operator=", reflection->function.find("operator=") != nullptr);

    #ifdef REW_FULLY_ENABLE
    EXPECT("function-assign", reflection->function.find("assign") != nullptr);
    EXPECT("function-get_allocator", reflection->function.find("get_allocator") != nullptr);
    EXPECT("function-at", reflection->function.find("at") != nullptr);
    #endif // REW_FULLY_ENABLE

    EXPECT("function-operator[]", reflection->function.find("operator[]") != nullptr);

    #ifdef REW_FULLY_ENABLE
    EXPECT("function-front", reflection->function.find("front") != nullptr);
    EXPECT("function-back", reflection->function.find("back") != nullptr);
    #endif // REW_FULLY_ENABLE

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
    #endif // REW_FULLY_ENABLE

    EXPECT("function-capacity", reflection->function.find("capacity") != nullptr);
    EXPECT("function-reserve", reflection->function.find("reserve") != nullptr);

    #ifdef REW_FULLY_ENABLE
    EXPECT("function-shrink_to_fit", reflection->function.find("shrink_to_fit") != nullptr);
    #endif // REW_FULLY_ENABLE

    EXPECT("function-clear", reflection->function.find("clear") != nullptr);

    #ifdef REW_FULLY_ENABLE
    EXPECT("function-insert", reflection->function.find("insert") != nullptr);
    EXPECT("function-erase", reflection->function.find("erase") != nullptr);
    #endif // REW_FULLY_ENABLE

    EXPECT("function-push_back", reflection->function.find("push_back") != nullptr);
    EXPECT("function-pop_back", reflection->function.find("pop_back") != nullptr);
//  EXPECT("function-resize", reflection->function.find("resize") != nullptr);

    #ifdef REW_FULLY_ENABLE
    EXPECT("function-swap", reflection->function.find("swap") != nullptr);
    EXPECT("function-flip", reflection->function.find("flip") != nullptr);
    #endif // REW_FULLY_ENABLE
}
