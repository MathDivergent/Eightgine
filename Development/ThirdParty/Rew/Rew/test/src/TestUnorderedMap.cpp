#include <RewTestingBase.hpp>

#include <Rew/BuiltIn/unordered_map.hpp>

TEST(TestBuiltin, TestUnorderedMap)
{
    rew::reflectable<std::unordered_map<int, float>>();

    auto type = rew::global.find("std::unordered_map<int, float>");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "std::unordered_map<int, float>");
    EXPECT("type-size", type->size == sizeof(std::unordered_map<int, float>));
    EXPECT("type-context", type->context != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("reflection-name", reflection->name == "std::unordered_map<int, float>");

    EXPECT("factory-R()", reflection->factory.find("std::unordered_map<int, float>()") != nullptr);

    #ifdef REW_FULLY_ENABLE
    EXPECT("R(size_type, hasher const&, key_equal const&, allocator_type const&)", reflection->factory.find("std::unordered_map<int, float>(unsigned long, std::hash<int> const&, std::equal_to<int> const&, std::allocator<std::pair<int const, float>> const&)") != nullptr || reflection->factory.find("std::unordered_map<int, float>(unsigned long long, std::hash<int> const&, std::equal_to<int> const&, std::allocator<std::pair<int const, float>> const&)") != nullptr);
    EXPECT("R(size_type, hasher const&, key_equal const&)", reflection->factory.find("std::unordered_map<int, float>(unsigned long, std::hash<int> const&, std::equal_to<int> const&)") != nullptr || reflection->factory.find("std::unordered_map<int, float>(unsigned long long, std::hash<int> const&, std::equal_to<int> const&)") != nullptr);
    EXPECT("R(size_type, hasher const&)", reflection->factory.find("std::unordered_map<int, float>(unsigned long, std::hash<int> const&)") != nullptr || reflection->factory.find("std::unordered_map<int, float>(unsigned long long, std::hash<int> const&)") != nullptr);
    EXPECT("R(size_type)", reflection->factory.find("std::unordered_map<int, float>(unsigned long)") != nullptr || reflection->factory.find("std::unordered_map<int, float>(unsigned long long)") != nullptr);
    EXPECT("R(size_type, allocator_type const&)", reflection->factory.find("std::unordered_map<int, float>(unsigned long, std::allocator<std::pair<int const, float>> const&)") != nullptr || reflection->factory.find("std::unordered_map<int, float>(unsigned long long, std::allocator<std::pair<int const, float>> const&)") != nullptr);
    EXPECT("R(size_type, hasher const&, typename R::allocator_type const&)", reflection->factory.find("std::unordered_map<int, float>(unsigned long, std::hash<int> const&, std::allocator<std::pair<int const, float>> const&)") != nullptr || reflection->factory.find("std::unordered_map<int, float>(unsigned long long, std::hash<int> const&, std::allocator<std::pair<int const, float>> const&)") != nullptr);
    EXPECT("R(const_iterator, const_iterator, size_type, hasher const&, key_equal const&, allocator_type const&)", reflection->factory.find("std::unordered_map<int, float>(std::unordered_map<int, float>::const_iterator, std::unordered_map<int, float>::const_iterator, unsigned long, std::hash<int> const&, std::equal_to<int> const&, std::allocator<std::pair<int const, float>> const&)") != nullptr || reflection->factory.find("std::unordered_map<int, float>(std::unordered_map<int, float>::const_iterator, std::unordered_map<int, float>::const_iterator, unsigned long long, std::hash<int> const&, std::equal_to<int> const&, std::allocator<std::pair<int const, float>> const&)") != nullptr);
    EXPECT("R(const_iterator, const_iterator, size_type, hasher const&, key_equal const&)", reflection->factory.find("std::unordered_map<int, float>(std::unordered_map<int, float>::const_iterator, std::unordered_map<int, float>::const_iterator, unsigned long, std::hash<int> const&, std::equal_to<int> const&)") != nullptr || reflection->factory.find("std::unordered_map<int, float>(std::unordered_map<int, float>::const_iterator, std::unordered_map<int, float>::const_iterator, unsigned long long, std::hash<int> const&, std::equal_to<int> const&)") != nullptr);
    EXPECT("R(const_iterator, const_iterator, size_type, hasher const&)", reflection->factory.find("std::unordered_map<int, float>(std::unordered_map<int, float>::const_iterator, std::unordered_map<int, float>::const_iterator, unsigned long, std::hash<int> const&)") != nullptr || reflection->factory.find("std::unordered_map<int, float>(std::unordered_map<int, float>::const_iterator, std::unordered_map<int, float>::const_iterator, unsigned long long, std::hash<int> const&)") != nullptr);
    EXPECT("R(const_iterator, const_iterator, size_type)", reflection->factory.find("std::unordered_map<int, float>(std::unordered_map<int, float>::const_iterator, std::unordered_map<int, float>::const_iterator, unsigned long)") != nullptr || reflection->factory.find("std::unordered_map<int, float>(std::unordered_map<int, float>::const_iterator, std::unordered_map<int, float>::const_iterator, unsigned long long)") != nullptr);
    EXPECT("R(const_iterator, const_iterator, size_type, allocator_type const&)", reflection->factory.find("std::unordered_map<int, float>(std::unordered_map<int, float>::const_iterator, std::unordered_map<int, float>::const_iterator, unsigned long, std::allocator<std::pair<int const, float>> const&)") != nullptr || reflection->factory.find("std::unordered_map<int, float>(std::unordered_map<int, float>::const_iterator, std::unordered_map<int, float>::const_iterator, unsigned long long, std::allocator<std::pair<int const, float>> const&)") != nullptr);
    EXPECT("R(const_iterator, const_iterator, size_type, hasher const&, allocator_type const&)", reflection->factory.find("std::unordered_map<int, float>(std::unordered_map<int, float>::const_iterator, std::unordered_map<int, float>::const_iterator, unsigned long, std::hash<int> const&, std::allocator<std::pair<int const, float>> const&)") != nullptr || reflection->factory.find("std::unordered_map<int, float>(std::unordered_map<int, float>::const_iterator, std::unordered_map<int, float>::const_iterator, unsigned long long, std::hash<int> const&, std::allocator<std::pair<int const, float>> const&)") != nullptr);
    EXPECT("R(std::initializer_list<value_type>, size_type, hasher const&, key_equal const&, allocator_type const&)", reflection->factory.find("std::unordered_map<int, float>(std::initializer_list<std::pair<int const, float>>, unsigned long, std::hash<int> const&, std::equal_to<int> const&, std::allocator<std::pair<int const, float>> const&)") != nullptr || reflection->factory.find("std::unordered_map<int, float>(std::initializer_list<std::pair<int const, float>>, unsigned long long, std::hash<int> const&, std::equal_to<int> const&, std::allocator<std::pair<int const, float>> const&)") != nullptr);
    EXPECT("R(std::initializer_list<value_type>, size_type, hasher const&, key_equal const&)", reflection->factory.find("std::unordered_map<int, float>(std::initializer_list<std::pair<int const, float>>, unsigned long, std::hash<int> const&, std::equal_to<int> const&)") != nullptr || reflection->factory.find("std::unordered_map<int, float>(std::initializer_list<std::pair<int const, float>>, unsigned long long, std::hash<int> const&, std::equal_to<int> const&)") != nullptr);
    EXPECT("R(std::initializer_list<value_type>, size_type, hasher const&)", reflection->factory.find("std::unordered_map<int, float>(std::initializer_list<std::pair<int const, float>>, unsigned long, std::hash<int> const&)") != nullptr || reflection->factory.find("std::unordered_map<int, float>(std::initializer_list<std::pair<int const, float>>, unsigned long long, std::hash<int> const&)") != nullptr);
    EXPECT("R(std::initializer_list<value_type>, size_type)", reflection->factory.find("std::unordered_map<int, float>(std::initializer_list<std::pair<int const, float>>, unsigned long)") != nullptr || reflection->factory.find("std::unordered_map<int, float>(std::initializer_list<std::pair<int const, float>>, unsigned long long)") != nullptr);
    EXPECT("R(std::initializer_list<value_type>, size_type, hasher const&, allocator_type const&)", reflection->factory.find("std::unordered_map<int, float>(std::initializer_list<std::pair<int const, float>>, unsigned long, std::hash<int> const&, std::allocator<std::pair<int const, float>> const&)") != nullptr || reflection->factory.find("std::unordered_map<int, float>(std::initializer_list<std::pair<int const, float>>, unsigned long long, std::hash<int> const&, std::allocator<std::pair<int const, float>> const&)") != nullptr);
    #endif // REW_FULLY_ENABLE

    EXPECT("factory-R(R const&)", reflection->factory.find("std::unordered_map<int, float>(std::unordered_map<int, float> const&)") != nullptr);
    EXPECT("function-operator=", reflection->function.find("operator=") != nullptr);

    #ifdef REW_FULLY_ENABLE
    EXPECT("function-get_allocator", reflection->function.find("get_allocator") != nullptr);
    EXPECT("function-begin", reflection->function.find("begin") != nullptr);
    EXPECT("function-cbegin", reflection->function.find("cbegin") != nullptr);
    EXPECT("function-end", reflection->function.find("end") != nullptr);
    EXPECT("function-cend", reflection->function.find("cend") != nullptr);
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
    EXPECT("function-at", reflection->function.find("at") != nullptr);
    EXPECT("function-operator[]", reflection->function.find("operator[]") != nullptr);
    EXPECT("function-count", reflection->function.find("count") != nullptr);

    #ifdef REW_FULLY_ENABLE
    EXPECT("function-find", reflection->function.find("find") != nullptr);
    #endif // REW_FULLY_ENABLE

#if __cplusplus >= 202002L
    EXPECT("function-contains", reflection->function.find("contains") != nullptr);
#endif // if

    #ifdef REW_FULLY_ENABLE
    EXPECT("function-equal_range", reflection->function.find("equal_range") != nullptr);
    EXPECT("function-bucket_count", reflection->function.find("bucket_count") != nullptr);
    EXPECT("function-max_bucket_count", reflection->function.find("max_bucket_count") != nullptr);
    EXPECT("function-bucket_size", reflection->function.find("bucket_size") != nullptr);
    EXPECT("function-bucket", reflection->function.find("bucket") != nullptr);
    EXPECT("function-load_factor", reflection->function.find("load_factor") != nullptr);
    EXPECT("function-max_load_factor", reflection->function.find("max_load_factor") != nullptr);
    #endif // REW_FULLY_ENABLE

    EXPECT("function-rehash", reflection->function.find("rehash") != nullptr);
    EXPECT("function-reserve", reflection->function.find("reserve") != nullptr);

    #ifdef REW_FULLY_ENABLE
    EXPECT("function-hash_function", reflection->function.find("hash_function") != nullptr);
    EXPECT("function-key_eq", reflection->function.find("key_eq") != nullptr);
    #endif // REW_FULLY_ENABLE
}
