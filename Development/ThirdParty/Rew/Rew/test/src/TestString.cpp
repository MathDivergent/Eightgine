#include <RewTestingBase.hpp>

#include <Rew/BuiltIn/string.hpp>

TEST(TestBuiltin, TestString)
{
    auto type = rew::global.find("std::string");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "std::string");
    EXPECT("type-size", type->size == sizeof(std::string));
    EXPECT("type-context", type->context != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("reflection-name", reflection->name == "std::string");

    EXPECT("factory-R()", reflection->factory.find("std::string()") != nullptr);

    #ifdef REW_FULLY_ENABLE
    EXPECT("factory-R(allocator_type const&)", reflection->factory.find("std::string(std::allocator<char> const&)") != nullptr);
    EXPECT("factory-R(size_type, value_type, allocator_type const&)", reflection->factory.find("std::string(unsigned long, char, std::allocator<char> const&)") != nullptr || reflection->factory.find("std::string(unsigned long long, char, std::allocator<char> const&)") != nullptr);
    EXPECT("factory-R(size_type, value_type)", reflection->factory.find("std::string(unsigned long, char)") != nullptr || reflection->factory.find("std::string(unsigned long long, char)") != nullptr);
    EXPECT("factory-R(R const&, size_type, size_type, allocator_type const&)", reflection->factory.find("std::string(std::string const&, unsigned long, unsigned long, std::allocator<char> const&)") != nullptr || reflection->factory.find("std::string(std::string const&, unsigned long long, unsigned long long, std::allocator<char> const&)") != nullptr);
    EXPECT("factory-R(R const&, size_type, size_type)", reflection->factory.find("std::string(std::string const&, unsigned long, unsigned long)") != nullptr || reflection->factory.find("std::string(std::string const&, unsigned long long, unsigned long long)") != nullptr);
    EXPECT("factory-R(value_type const*, size_type, allocator_type const&)", reflection->factory.find("std::string(char const*, unsigned long, std::allocator<char> const&)") != nullptr || reflection->factory.find("std::string(char const*, unsigned long long, std::allocator<char> const&)") != nullptr);
    EXPECT("factory-R(value_type const*, size_type)", reflection->factory.find("std::string(char const*, unsigned long)") != nullptr || reflection->factory.find("std::string(char const*, unsigned long long)") != nullptr);
    EXPECT("factory-R(value_type const*, allocator_type const&)", reflection->factory.find("std::string(char const*, std::allocator<char> const&)") != nullptr);
    EXPECT("factory-R(value_type const*)", reflection->factory.find("std::string(char const*)") != nullptr);
    EXPECT("factory-R(const_iterator, const_iterator, allocator_type const&)", reflection->factory.find("std::string(std::string::const_iterator, std::string::const_iterator, std::allocator<char> const&)") != nullptr);
    EXPECT("factory-R(const_iterator, const_iterator)", reflection->factory.find("std::string(std::string::const_iterator, std::string::const_iterator)") != nullptr);
    EXPECT("factory-R(R const&, allocator_type const&)", reflection->factory.find("std::string(std::string const&, std::allocator<char> const&)") != nullptr);
    #endif // REW_FULLY_ENABLE

    EXPECT("factory-R(R const&)", reflection->factory.find("std::string(std::string const&)") != nullptr);

    #ifdef REW_FULLY_ENABLE
    EXPECT("factory-R(std::initializer_list<value_type>, allocator_type const&)", reflection->factory.find("std::string(std::initializer_list<char>, std::allocator<char> const&)") != nullptr);
    EXPECT("factory-R(std::initializer_list<value_type>)", reflection->factory.find("std::string(std::initializer_list<char>)") != nullptr);
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

    EXPECT("function-data", reflection->function.find("data") != nullptr);

    #ifdef REW_FULLY_ENABLE
    EXPECT("function-c_str", reflection->function.find("c_str") != nullptr);
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
    EXPECT("function-length", reflection->function.find("length") != nullptr);
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

    #ifdef REW_FULLY_ENABLE
    EXPECT("function-append", reflection->function.find("append") != nullptr);
    EXPECT("function-operator+=", reflection->function.find("operator+=") != nullptr);
    #endif // REW_FULLY_ENABLE

    EXPECT("function-replace", reflection->function.find("replace") != nullptr);
    EXPECT("function-resize", reflection->function.find("resize") != nullptr);

    #ifdef REW_FULLY_ENABLE
    EXPECT("function-swap", reflection->function.find("swap") != nullptr);
    EXPECT("function-find", reflection->function.find("find") != nullptr);
    EXPECT("function-rfind", reflection->function.find("rfind") != nullptr);
    EXPECT("function-find_first_of", reflection->function.find("find_first_of") != nullptr);
    EXPECT("function-find_first_not_of", reflection->function.find("find_first_not_of") != nullptr);
    EXPECT("function-find_last_of", reflection->function.find("find_last_of") != nullptr);
    EXPECT("function-find_last_not_of", reflection->function.find("find_last_not_of") != nullptr);
    #endif // REW_FULLY_ENABLE

    EXPECT("function-compare", reflection->function.find("compare") != nullptr);

#if __cplusplus >= 202002L
    #ifdef REW_FULLY_ENABLE
    EXPECT("function-starts_with", reflection->function.find("starts_with") != nullptr);
    EXPECT("function-ends_with", reflection->function.find("ends_with") != nullptr);
    #endif // REW_FULLY_ENABLE
#endif // if

    EXPECT("function-substr", reflection->function.find("substr") != nullptr);
}
