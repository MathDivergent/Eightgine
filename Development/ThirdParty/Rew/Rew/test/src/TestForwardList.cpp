#include <RewTestingBase.hpp>

#include <Rew/BuiltIn/forward_list.hpp>

TEST(TestBuiltin, TestForwardList)
{
    rew::reflectable<std::forward_list<int>>();

    auto type = rew::global.find("std::forward_list<int>");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "std::forward_list<int>");
    EXPECT("type-size", type->size == sizeof(std::forward_list<int>));
    EXPECT("type-context", type->context != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("reflection-name", reflection->name == "std::forward_list<int>");

    EXPECT("factory-R()", reflection->factory.find("std::forward_list<int>()") != nullptr);

    #ifdef REW_FULLY_ENABLE
    EXPECT("factory-R(allocator_type const&)", reflection->factory.find("std::forward_list<int>(std::allocator<int> const&)") != nullptr);
    EXPECT("factory-R(size_type, const_reference, allocator_type const&)", reflection->factory.find("std::forward_list<int>(unsigned long, int const&, std::allocator<int> const&)") != nullptr || reflection->factory.find("std::forward_list<int>(unsigned long long, int const&, std::allocator<int> const&)") != nullptr);
    EXPECT("factory-R(size_type, const_reference)", reflection->factory.find("std::forward_list<int>(unsigned long, int const&)") != nullptr || reflection->factory.find("std::forward_list<int>(unsigned long long, int const&)") != nullptr);
    EXPECT("factory-R(size_type, allocator_type const&)", reflection->factory.find("std::forward_list<int>(unsigned long, std::allocator<int> const&)") != nullptr || reflection->factory.find("std::forward_list<int>(unsigned long long, std::allocator<int> const&)") != nullptr);
    EXPECT("factory-R(size_type)", reflection->factory.find("std::forward_list<int>(unsigned long)") != nullptr || reflection->factory.find("std::forward_list<int>(unsigned long long)") != nullptr);
    EXPECT("factory-R(const_iterator, const_iterator, allocator_type const&)", reflection->factory.find("std::forward_list<int>(std::forward_list<int>::const_iterator, std::forward_list<int>::const_iterator, std::allocator<int> const&)") != nullptr);
    EXPECT("factory-R(const_iterator, const_iterator)", reflection->factory.find("std::forward_list<int>(std::forward_list<int>::const_iterator, std::forward_list<int>::const_iterator)") != nullptr);
    EXPECT("factory-R(R const&, allocator_type const&)", reflection->factory.find("std::forward_list<int>(std::forward_list<int> const&, std::allocator<int> const&)") != nullptr);
    #endif // REW_FULLY_ENABLE

    EXPECT("factory-R(R const&)", reflection->factory.find("std::forward_list<int>(std::forward_list<int> const&)") != nullptr);

    #ifdef REW_FULLY_ENABLE
    EXPECT("factory-R(std::initializer_list<value_type>, allocator_type const&)", reflection->factory.find("std::forward_list<int>(std::initializer_list<int>, std::allocator<int> const&)") != nullptr);
    EXPECT("factory-R(std::initializer_list<value_type>)", reflection->factory.find("std::forward_list<int>(std::initializer_list<int>)") != nullptr);
    #endif // REW_FULLY_ENABLE

    EXPECT("function-operator=", reflection->function.find("operator=") != nullptr);

    #ifdef REW_FULLY_ENABLE
    EXPECT("function-assign", reflection->function.find("assign") != nullptr);
    EXPECT("function-get_allocator", reflection->function.find("get_allocator") != nullptr);
    #endif // REW_FULLY_ENABLE

    #ifdef REW_FULLY_ENABLE
    EXPECT("function-front", reflection->function.find("front") != nullptr);
    EXPECT("function-before_begin", reflection->function.find("before_begin") != nullptr);
    EXPECT("function-cbefore_begin", reflection->function.find("cbefore_begin") != nullptr);
    EXPECT("function-begin", reflection->function.find("begin") != nullptr);
    EXPECT("function-cbegin", reflection->function.find("cbegin") != nullptr);
    EXPECT("function-end", reflection->function.find("end") != nullptr);
    EXPECT("function-cend", reflection->function.find("cend") != nullptr);
    #endif // REW_FULLY_ENABLE

    EXPECT("function-empty", reflection->function.find("empty") != nullptr);

    #ifdef REW_FULLY_ENABLE
    EXPECT("function-max_size", reflection->function.find("max_size") != nullptr);
    #endif // REW_FULLY_ENABLE

    EXPECT("function-clear", reflection->function.find("clear") != nullptr);

    #ifdef REW_FULLY_ENABLE
    EXPECT("function-insert_after", reflection->function.find("insert_after") != nullptr);
    EXPECT("function-erase_after", reflection->function.find("erase_after") != nullptr);
    #endif // REW_FULLY_ENABLE

    EXPECT("function-push_front", reflection->function.find("push_front") != nullptr);
    EXPECT("function-pop_front", reflection->function.find("pop_front") != nullptr);
    EXPECT("function-resize", reflection->function.find("resize") != nullptr);

    #ifdef REW_FULLY_ENABLE
    EXPECT("function-swap", reflection->function.find("swap") != nullptr);
    #endif // REW_FULLY_ENABLE

    EXPECT("function-merge", reflection->function.find("merge") != nullptr);

    #ifdef REW_FULLY_ENABLE
    EXPECT("function-splice_after", reflection->function.find("splice_after") != nullptr);
    #endif // REW_FULLY_ENABLE

    EXPECT("function-remove", reflection->function.find("remove") != nullptr);

    #ifdef REW_FULLY_ENABLE
    EXPECT("function-remove_if", reflection->function.find("remove_if") != nullptr);
    #endif // REW_FULLY_ENABLE

    EXPECT("function-reverse", reflection->function.find("reverse") != nullptr);
    EXPECT("function-sort", reflection->function.find("sort") != nullptr);
}
