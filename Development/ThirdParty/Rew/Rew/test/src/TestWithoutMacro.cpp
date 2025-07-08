#include <RewTestingBase.hpp>

TEST_SPACE()
{

struct TestWithoutMacroBaseStruct {};

struct TestWithoutMacroStruct : TestWithoutMacroBaseStruct
{
    void Function() {}

    int Property = 0;
};

struct TestWithoutMacroInjection : rew::injectable_t {};

} // TEST_SPACE

// need only for default injections
// template <>
// struct xxrew_traits<1>
// {
//     using R = TestWithoutMacroInjection;
// };

template <>
struct xxrew_traits<TestWithoutMacroInjection>
{
    using R = TestWithoutMacroInjection; // not required by library
    static auto name() { return "TestWithoutMacroInjection"; }
};

template <>
struct xxrew_traits<TestWithoutMacroBaseStruct>
{
    static auto registry() { return &rew::global; }
    static auto name() { return "TestWithoutMacroBaseStruct"; }
};

template <>
struct xxrew<TestWithoutMacroBaseStruct>
{
    template <typename InjectionType>
    void evaluate(InjectionType& injection)
    {
        rew::find_or_add_type<TestWithoutMacroBaseStruct>();
    }
};

template <>
struct xxrew_traits<TestWithoutMacroStruct>
{
    static auto registry() { return &rew::global; }
    static auto name() { return "TestWithoutMacroStruct"; }
};

template <>
struct xxrew<TestWithoutMacroStruct>
{
    using R = TestWithoutMacroStruct; // not required by library

    template <typename InjectionType>
    static void evaluate(InjectionType&& injection)
    {
        auto type = rew::find_or_add_type<R>();
        rew::find_or_add_parent<R, TestWithoutMacroBaseStruct>(type->reflection);
        rew::find_or_add_factory<R()>(type->reflection);
        rew::find_or_add_function(type->reflection, "Function", &R::Function);
        rew::find_or_add_property(type->reflection, "Property", &R::Property, &R::Property);
        rew::find_or_add_deleter<void(R*)>(type->reflection);
        rew::find_or_add_meta(type->reflection->meta, "Meta", 123);
        rew::find_or_add_injection<R, TestWithoutMacroInjection>(type);
    }
};

// need only for reflectable using
// struct TestWithoutMacroStructAlias : TestWithoutMacroStruct {};

// template <>
// struct xxrew_alias<TestWithoutMacroStructAlias>
// {
//     using R = TestWithoutMacroStruct;
// };

TEST(TestLibrary, TestWithoutMacro)
{
    rew::reflectable<TestWithoutMacroStruct>();

    auto type = rew::global.find("TestWithoutMacroStruct");

    ASSERT("type", type != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("reflection-name", reflection->name == "TestWithoutMacroStruct");

    EXPECT("parent", reflection->parent.find("TestWithoutMacroBaseStruct") != nullptr);
    EXPECT("factory", reflection->factory.find("TestWithoutMacroStruct()") != nullptr);
    EXPECT("function", reflection->function.find("Function") != nullptr);
    EXPECT("property", reflection->property.find("Property") != nullptr);
    EXPECT("deleter", reflection->deleter.find("void(TestWithoutMacroStruct*)") != nullptr);
    EXPECT("meta", reflection->meta.find("Meta") != nullptr);
    EXPECT("injection", type->injection.find("TestWithoutMacroInjection") != nullptr);
}
