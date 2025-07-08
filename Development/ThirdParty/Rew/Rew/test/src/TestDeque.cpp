#include <RewTestingBase.hpp>

#include <Rew/BuiltIn/deque.hpp>

TEST(TestBuiltin, TestDeque)
{
    rew::reflectable<std::deque<int>>();

    auto type = rew::global.find("std::deque<int>");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "std::deque<int>");
    EXPECT("type-size", type->size == sizeof(std::deque<int>));
    EXPECT("type-context", type->context != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("reflection-name", reflection->name == "std::deque<int>");

    EXPECT("factory-R()", reflection->factory.find("std::deque<int>()") != nullptr);

    #ifdef REW_FULLY_ENABLE
    EXPECT("factory-R(allocator_type const&)", reflection->factory.find("std::deque<int>(std::allocator<int> const&)") != nullptr);
    EXPECT("factory-R(size_type, const_reference, allocator_type const&)", reflection->factory.find("std::deque<int>(unsigned long, int const&, std::allocator<int> const&)") != nullptr || reflection->factory.find("std::deque<int>(unsigned long long, int const&, std::allocator<int> const&)") != nullptr);
    EXPECT("factory-R(size_type, const_reference)", reflection->factory.find("std::deque<int>(unsigned long, int const&)") != nullptr || reflection->factory.find("std::deque<int>(unsigned long long, int const&)") != nullptr);
    EXPECT("factory-R(size_type, allocator_type const&)", reflection->factory.find("std::deque<int>(unsigned long, std::allocator<int> const&)") != nullptr || reflection->factory.find("std::deque<int>(unsigned long long, std::allocator<int> const&)") != nullptr);
    EXPECT("factory-R(size_type)", reflection->factory.find("std::deque<int>(unsigned long)") != nullptr || reflection->factory.find("std::deque<int>(unsigned long long)") != nullptr);
    EXPECT("factory-R(const_iterator, const_iterator, allocator_type const&)", reflection->factory.find("std::deque<int>(std::deque<int>::const_iterator, std::deque<int>::const_iterator, std::allocator<int> const&)") != nullptr);
    EXPECT("factory-R(const_iterator, const_iterator)", reflection->factory.find("std::deque<int>(std::deque<int>::const_iterator, std::deque<int>::const_iterator)") != nullptr);
    EXPECT("factory-R(R const&, allocator_type const&)", reflection->factory.find("std::deque<int>(std::deque<int> const&, std::allocator<int> const&)") != nullptr);
    #endif // REW_FULLY_ENABLE

    EXPECT("factory-R(R const&)", reflection->factory.find("std::deque<int>(std::deque<int> const&)") != nullptr);

    #ifdef REW_FULLY_ENABLE
    EXPECT("factory-R(std::initializer_list<value_type>, allocator_type const&)", reflection->factory.find("std::deque<int>(std::initializer_list<int>, std::allocator<int> const&)") != nullptr);
    EXPECT("factory-R(std::initializer_list<value_type>)", reflection->factory.find("std::deque<int>(std::initializer_list<int>)") != nullptr);
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
    EXPECT("function-shrink_to_fit", reflection->function.find("shrink_to_fit") != nullptr);
    #endif // REW_FULLY_ENABLE

    EXPECT("function-clear", reflection->function.find("clear") != nullptr);

    #ifdef REW_FULLY_ENABLE
    EXPECT("function-insert", reflection->function.find("insert") != nullptr);
    EXPECT("function-erase", reflection->function.find("erase") != nullptr);
    #endif // REW_FULLY_ENABLE

    EXPECT("function-push_back", reflection->function.find("push_back") != nullptr);
    EXPECT("function-push_front", reflection->function.find("push_front") != nullptr);
    EXPECT("function-pop_back", reflection->function.find("pop_back") != nullptr);
    EXPECT("function-pop_front", reflection->function.find("pop_front") != nullptr);
    EXPECT("function-resize", reflection->function.find("resize") != nullptr);

    #ifdef REW_FULLY_ENABLE
    EXPECT("function-swap", reflection->function.find("swap") != nullptr);
    #endif // REW_FULLY_ENABLE
}
