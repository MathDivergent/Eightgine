#include <RewTestingBase.hpp>

#include <Rew/BuiltIn/set.hpp>

TEST(TestBuiltin, TestSet)
{
    rew::reflectable<std::set<int>>();

    auto type = rew::global.find("std::set<int>");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "std::set<int>");
    EXPECT("type-size", type->size == sizeof(std::set<int>));
    EXPECT("type-context", type->context != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("reflection-name", reflection->name == "std::set<int>");

    EXPECT("factory-R()", reflection->factory.find("std::set<int>()") != nullptr);

    #ifdef REW_FULLY_ENABLE
    EXPECT("factory-R(key_compare const&, allocator_type const&)", reflection->factory.find("std::set<int>(std::less<int> const&, std::allocator<int> const&)") != nullptr);
    EXPECT("factory-R(key_compare const&)", reflection->factory.find("std::set<int>(std::less<int> const&)") != nullptr);
    EXPECT("factory-R(allocator_type const&)", reflection->factory.find("std::set<int>(std::allocator<int> const&)") != nullptr);
    EXPECT("factory-R(const_iterator, const_iterator, key_compare const&, allocator_type const&)", reflection->factory.find("std::set<int>(std::set<int>::const_iterator, std::set<int>::const_iterator, std::less<int> const&, std::allocator<int> const&)") != nullptr);
    EXPECT("factory-R(const_iterator, const_iterator, allocator_type const&)", reflection->factory.find("std::set<int>(std::set<int>::const_iterator, std::set<int>::const_iterator, std::allocator<int> const&)") != nullptr);
    #endif // REW_FULLY_ENABLE

    EXPECT("factory-R(R const&)", reflection->factory.find("std::set<int>(std::set<int> const&)") != nullptr);

    #ifdef REW_FULLY_ENABLE
    EXPECT("factory-R(R const&, allocator_type const&)", reflection->factory.find("std::set<int>(std::set<int> const&, std::allocator<int> const&)") != nullptr);
    EXPECT("factory-R(std::initializer_list<value_type>, key_compare const&, allocator_type const&)", reflection->factory.find("std::set<int>(std::initializer_list<int>, std::less<int> const&, std::allocator<int> const&)") != nullptr);
    EXPECT("factory-R(std::initializer_list<value_type>)", reflection->factory.find("std::set<int>(std::initializer_list<int>)") != nullptr);
    #endif // REW_FULLY_ENABLE

    EXPECT("function-operator=", reflection->function.find("operator=") != nullptr);

    #ifdef REW_FULLY_ENABLE
    EXPECT("function-get_allocator", reflection->function.find("get_allocator") != nullptr);
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

    EXPECT("function-clear", reflection->function.find("clear") != nullptr);

    #ifdef REW_FULLY_ENABLE
    EXPECT("function-insert", reflection->function.find("insert") != nullptr);
    EXPECT("function-erase", reflection->function.find("erase") != nullptr);
    EXPECT("function-swap", reflection->function.find("swap") != nullptr);
//  EXPECT("function-extract", reflection->function.find("extract") != nullptr);
    #endif // REW_FULLY_ENABLE

    EXPECT("function-merge", reflection->function.find("merge") != nullptr);
    EXPECT("function-count", reflection->function.find("count") != nullptr);

    #ifdef REW_FULLY_ENABLE
    EXPECT("function-find", reflection->function.find("find") != nullptr);
    #endif // REW_FULLY_ENABLE

#if __cplusplus >= 202002L
    EXPECT("function-contains", reflection->function.find("contains") != nullptr);
#endif // if

    #ifdef REW_FULLY_ENABLE
    EXPECT("function-equal_range", reflection->function.find("equal_range") != nullptr);
    EXPECT("function-lower_bound", reflection->function.find("lower_bound") != nullptr);
    EXPECT("function-upper_bound", reflection->function.find("upper_bound") != nullptr);
    EXPECT("function-key_comp", reflection->function.find("key_comp") != nullptr);
//  EXPECT("function-value_comp", reflection->function.find("value_comp") != nullptr);
    #endif // REW_FULLY_ENABLE
}
