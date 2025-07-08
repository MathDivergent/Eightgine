#include <RewTestingBase.hpp>

TEST_SPACE()
{

struct TestFunctionStruct
{
    void Function() {}
    void Reference()& {}
    void Const() const {}
    void ConstReference() const& {}

    void Overload()& {}
    void Overload() const& {}
    void Overload(int) {}
    void Overload(int) const {}

    template <typename... Args>
    void Template() {}

    template <typename... Args, typename T>
    void Template(T) {}
};

} // TEST_SPACE

REFLECTABLE_DECLARATION(TestFunctionStruct)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(TestFunctionStruct)
    FUNCTION(Function)
    FUNCTION(Reference)
    FUNCTION(Const)
    FUNCTION(ConstReference)
    FUNCTION(Overload, void()&)
    FUNCTION(Overload, void() const&)
    FUNCTION(Overload, void(int))
    FUNCTION(Overload, void(int) const)
    FUNCTION(Template, void(float))
    FUNCTION(Template<int>, void())
    FUNCTION(Template<int>, void(float))
    FUNCTION((Template<int, bool>), void(float))
REFLECTABLE_INIT()

TEST(TestLibrary::TestRegistryFunction, TestFunction)
{
    auto type = rew::global.find("TestFunctionStruct");

    ASSERT("type", type != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);

    {
        EXPECT("function", reflection->function.find("Function") != nullptr);
        EXPECT("function-reference", reflection->function.find("Reference") != nullptr);
        EXPECT("function-const", reflection->function.find("Const") != nullptr);
        EXPECT("function-const_reference", reflection->function.find("ConstReference") != nullptr);
    }
    {
        auto overload = reflection->function.find("Overload");

        ASSERT("function-overload", overload != nullptr);
        EXPECT("function-overload-1", overload->find("void()&") != nullptr);
        EXPECT("function-overload-2", overload->find("void() const&") != nullptr);
        EXPECT("function-overload-3", overload->find("void(int)") != nullptr);
        EXPECT("function-overload-4", overload->find("void(int) const") != nullptr);
    }
    {
        EXPECT("function-template", reflection->function.find("Template") != nullptr);
    }
    {
        auto template_with_arg = reflection->function.find("Template<int>");

        ASSERT("function-template_with_arg",template_with_arg != nullptr);
        EXPECT("function-template_with_arg-overload-1", template_with_arg->find("void()") != nullptr);
        EXPECT("function-template_with_arg-overload-2", template_with_arg->find("void(float)") != nullptr);
    }
    {
        EXPECT("function-template_with_args", reflection->function.find("Template<int, bool>") != nullptr);
    }
}


TEST_SPACE()
{

struct TestStaticFunctionStruct
{
    static void Function() {}
    static void Overload() {}
    static void Overload(int) {}

    template <typename... Args>
    static void Template() {}

    template <typename... Args, typename T>
    static void Template(T) {}
};

} // TEST_SPACE

REFLECTABLE_DECLARATION(TestStaticFunctionStruct)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(TestStaticFunctionStruct)
    FUNCTION(Function)
    FUNCTION(Overload, void())
    FUNCTION(Overload, void(int))
    FUNCTION(Template, void(float))
    FUNCTION(Template<int>, void())
    FUNCTION(Template<int>, void(float))
    FUNCTION((Template<int, bool>), void(float))
REFLECTABLE_INIT()

TEST(TestLibrary::TestRegistryFunction, TestStaticFunction)
{
    auto type = rew::global.find("TestStaticFunctionStruct");

    ASSERT("type", type != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);

    {
        EXPECT("function", reflection->function.find("Function") != nullptr);
    }
    {
        auto overload = reflection->function.find("Overload");

        ASSERT("function-overload", overload != nullptr);
        EXPECT("function-overload-1", overload->find("void()") != nullptr);
        EXPECT("function-overload-2", overload->find("void(int)") != nullptr);
    }
    {
        EXPECT("function-template", reflection->function.find("Template") != nullptr);
    }
    {
        auto template_with_arg = reflection->function.find("Template<int>");

        ASSERT("function-template_with_arg",template_with_arg != nullptr);
        EXPECT("function-template_with_arg-overload-1", template_with_arg->find("void()") != nullptr);
        EXPECT("function-template_with_arg-overload-2", template_with_arg->find("void(float)") != nullptr);
    }
    {
        EXPECT("function-template_with_args", reflection->function.find("Template<int, bool>") != nullptr);
    }
}


TEST_SPACE()
{

struct TestFreeFunctionStruct {};

void Function() {}
void Overload() {}
void Overload(int) {}

template <typename... Args>
void Template() {}

template <typename... Args, typename T>
void Template(T) {}

} // TEST_SPACE

REFLECTABLE_DECLARATION(TestFreeFunctionStruct)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(TestFreeFunctionStruct)
    FREE_FUNCTION(Function)
    FREE_FUNCTION(Overload, void())
    FREE_FUNCTION(Overload, void(int))
    FREE_FUNCTION(Template, void(float))
    FREE_FUNCTION(Template<int>, void())
    FREE_FUNCTION(Template<int>, void(float))
    FREE_FUNCTION((Template<int, bool>), void(float))
REFLECTABLE_INIT()

TEST(TestLibrary::TestRegistryFunction, TestFreeFunction)
{
    auto type = rew::global.find("TestFreeFunctionStruct");

    ASSERT("type", type != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);

    EXPECT("function", reflection->function.find("Function") != nullptr);

    {
        auto overload = reflection->function.find("Overload");

        ASSERT("function-overload", overload != nullptr);
        EXPECT("function-overload-1", overload->find("void()") != nullptr);
        EXPECT("function-overload-2", overload->find("void(int)") != nullptr);
    {
    }
        EXPECT("function-template", reflection->function.find("Template") != nullptr);
    }
    {
        auto template_with_arg = reflection->function.find("Template<int>");

        ASSERT("function-template_with_arg",template_with_arg != nullptr);
        EXPECT("function-template_with_arg-overload-1", template_with_arg->find("void()") != nullptr);
        EXPECT("function-template_with_arg-overload-2", template_with_arg->find("void(float)") != nullptr);
    }
    {
        EXPECT("function-template_with_args", reflection->function.find("Template<int, bool>") != nullptr);
    }
}
