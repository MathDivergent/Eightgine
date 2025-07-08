#include <RewTestingBase.hpp>

TEST_SPACE()
{

struct TestFieldPropertyStruct
{
    int Property = 0;
    int const Readonly = 0;
    int& Reference;
};

} // TEST_SPACE

REFLECTABLE_DECLARATION(TestFieldPropertyStruct)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(TestFieldPropertyStruct)
    PROPERTY(Property)
    PROPERTY(Readonly)
//  PROPERTY(Reference) // unsupported!
REFLECTABLE_INIT()

TEST(TestLibrary::TestRegistryProperty, TestFieldProperty)
{
    auto type = rew::global.find("TestFieldPropertyStruct");

    ASSERT("type", type != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);

    {
        auto property = reflection->property.find("Property");

        ASSERT("property", property != nullptr);
        EXPECT("property-get", property->get != nullptr);
        EXPECT("property-set", property->set != nullptr);
        EXPECT("property-context", property->context != nullptr);
    }
    {
        auto readonly = reflection->property.find("Readonly");

        ASSERT("property-readonly", readonly != nullptr);
        EXPECT("property-readonly-get", readonly->get != nullptr);
        EXPECT("property-readonly-set", readonly->set == nullptr);
        EXPECT("property-readonly-context", readonly->context != nullptr);
    }
}


TEST_SPACE()
{

struct TestStaticFieldPropertyStruct
{
    static int Property;
    static int const Readonly;

    template <typename T, typename... Args>
    static T Template;
};

int TestStaticFieldPropertyStruct::Property = 0;
int const TestStaticFieldPropertyStruct::Readonly = 0;

template <typename T, typename... Args>
T TestStaticFieldPropertyStruct::Template = T();

} // TEST_SPACE

REFLECTABLE_DECLARATION(TestStaticFieldPropertyStruct)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(TestStaticFieldPropertyStruct)
    PROPERTY(Property)
    PROPERTY(Readonly)
    PROPERTY(Template<int>)
    PROPERTY((Template<int, bool>))
REFLECTABLE_INIT()

TEST(TestLibrary::TestRegistryProperty, TestStaticFieldProperty)
{
    auto type = rew::global.find("TestStaticFieldPropertyStruct");

    ASSERT("type", type != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);

    {
        auto property = reflection->property.find("Property");

        ASSERT("property", property != nullptr);
        EXPECT("property-get", property->get != nullptr);
        EXPECT("property-set", property->set != nullptr);
        EXPECT("property-context", property->context != nullptr);
    }
    {
        auto readonly = reflection->property.find("Readonly");

        ASSERT("property-readonly", readonly != nullptr);
        EXPECT("property-readonly-get", readonly->get != nullptr);
        EXPECT("property-readonly-set", readonly->set == nullptr);
        EXPECT("property-readonly-context", readonly->context != nullptr);
    }
    {
        auto template_with_arg = reflection->property.find("Template<int>");

        ASSERT("property-template_with_arg", template_with_arg != nullptr);
        EXPECT("property-template_with_arg-get", template_with_arg->get != nullptr);
        EXPECT("property-template_with_arg-set", template_with_arg->set != nullptr);
        EXPECT("property-template_with_arg-context", template_with_arg->context != nullptr);
    }
    {
        auto template_with_args = reflection->property.find("Template<int, bool>");

        ASSERT("property-template_with_args", template_with_args != nullptr);
        EXPECT("property-template_with_args-get", template_with_args->get != nullptr);
        EXPECT("property-template_with_args-set", template_with_args->set != nullptr);
        EXPECT("property-template_with_args-context", template_with_args->context != nullptr);
    }
}


TEST_SPACE()
{

struct TestFreeFieldPropertyStruct {};

int Property = 0;
int const Readonly = 0;
int& Reference = Property;

template <typename T, typename... Args>
T Template = T();

} // TEST_SPACE

REFLECTABLE_DECLARATION(TestFreeFieldPropertyStruct)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(TestFreeFieldPropertyStruct)
    FREE_PROPERTY(Property)
    FREE_PROPERTY(Readonly)
    FREE_PROPERTY(Reference)
    FREE_PROPERTY(Template<int>)
    FREE_PROPERTY((Template<int, bool>))
REFLECTABLE_INIT()

TEST(TestLibrary::TestRegistryProperty, TestFreeFieldProperty)
{
    auto type = rew::global.find("TestFreeFieldPropertyStruct");

    ASSERT("type", type != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);

    {
        auto property = reflection->property.find("Property");

        ASSERT("property", property != nullptr);
        EXPECT("property-get", property->get != nullptr);
        EXPECT("property-set", property->set != nullptr);
        EXPECT("property-context", property->context != nullptr);
    }
    {
        auto readonly = reflection->property.find("Readonly");

        ASSERT("property-readonly", readonly != nullptr);
        EXPECT("property-readonly-get", readonly->get != nullptr);
        EXPECT("property-readonly-set", readonly->set == nullptr);
        EXPECT("property-readonly-context", readonly->context != nullptr);
    }
    {
        auto reference = reflection->property.find("Reference");

        ASSERT("property-reference", reference != nullptr);
        EXPECT("property-reference-get", reference->get != nullptr);
        EXPECT("property-reference-set", reference->set != nullptr);
        EXPECT("property-reference-context", reference->context != nullptr);
    }
    {
        auto template_with_arg = reflection->property.find("Template<int>");

        ASSERT("property-template_with_arg", template_with_arg != nullptr);
        EXPECT("property-template_with_arg-get", template_with_arg->get != nullptr);
        EXPECT("property-template_with_arg-set", template_with_arg->set != nullptr);
        EXPECT("property-template_with_arg-context", template_with_arg->context != nullptr);
    }
    {
        auto template_with_args = reflection->property.find("Template<int, bool>");

        ASSERT("property-template_with_args", template_with_args != nullptr);
        EXPECT("property-template_with_args-get", template_with_args->get != nullptr);
        EXPECT("property-template_with_args-set", template_with_args->set != nullptr);
        EXPECT("property-template_with_args-context", template_with_args->context != nullptr);
    }
}


TEST_SPACE()
{

struct TestFunctionPropertyStruct : TestFieldPropertyStruct
{
    int& WithContext() { return Property; } void WithContext(int& value) { Property = value; }
    int const& WithConstContext() { return Property; } void WithConstContext(int const& value) { Property = value; }
    int const& ConstWithConstContext() const { return Property; } void ConstWithConstContext(int const& value) { Property = value; }
    int NoContext() { return 0; } void NoContext(int) {}
    int ConstNoContext() const { return 0; } void ConstNoContext(int) {}

    int& ReadonlyWithContext() { return Property; }
    int const& ReadonlyWithConstContext() { return Property; }
    int const& ReadonlyConstWithConstContext() const { return Property; }
    int ReadonlyNoContext() { return 0; }
    int ReadonlyConstNoContext() const { return 0; }

    // u can also use function template as property
};

} // TEST_SPACE

REFLECTABLE_DECLARATION(TestFunctionPropertyStruct)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(TestFunctionPropertyStruct)
    PROPERTY(WithContext)
    PROPERTY(WithConstContext)
    PROPERTY(ConstWithConstContext)
    PROPERTY(NoContext)
    PROPERTY(ConstNoContext)

    PROPERTY(ReadonlyWithContext)
    PROPERTY(ReadonlyWithConstContext)
    PROPERTY(ReadonlyConstWithConstContext)
    PROPERTY(ReadonlyNoContext)
    PROPERTY(ReadonlyConstNoContext)
REFLECTABLE_INIT()

TEST(TestLibrary::TestRegistryProperty, TestFunctionProperty)
{
    auto type = rew::global.find("TestFunctionPropertyStruct");

    ASSERT("type", type != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);

    {
        auto with_context = reflection->property.find("WithContext");

        ASSERT("property-with_context", with_context != nullptr);
        EXPECT("property-with_context-get", with_context->get != nullptr);
        EXPECT("property-with_context-set", with_context->set != nullptr);
        EXPECT("property-with_context-context", with_context->context != nullptr);
    }
    {
        auto with_const_context = reflection->property.find("WithConstContext");

        ASSERT("property-with_const_context", with_const_context != nullptr);
        EXPECT("property-with_const_context-get", with_const_context->get != nullptr);
        EXPECT("property-with_const_context-set", with_const_context->set != nullptr);
        EXPECT("property-with_const_context-context", with_const_context->context != nullptr);
    }
    {
        auto const_with_const_context = reflection->property.find("ConstWithConstContext");

        ASSERT("property-const_with_const_context", const_with_const_context != nullptr);
        EXPECT("property-const_with_const_context-get", const_with_const_context->get != nullptr);
        EXPECT("property-const_with_const_context-set", const_with_const_context->set != nullptr);
        EXPECT("property-const_with_const_context-context", const_with_const_context->context != nullptr);
    }
    {
        auto no_context = reflection->property.find("NoContext");

        ASSERT("property-no_context", no_context != nullptr);
        EXPECT("property-no_context-get", no_context->get != nullptr);
        EXPECT("property-no_context-set", no_context->set != nullptr);
        EXPECT("property-no_context-context", no_context->context == nullptr);
    }
    {
        auto const_no_context = reflection->property.find("ConstNoContext");

        ASSERT("property-const_no_context", const_no_context != nullptr);
        EXPECT("property-const_no_context-get", const_no_context->get != nullptr);
        EXPECT("property-const_no_context-set", const_no_context->set != nullptr);
        EXPECT("property-const_no_context-context", const_no_context->context == nullptr);
    }

    {
        auto readonly_with_context = reflection->property.find("ReadonlyWithContext");

        ASSERT("property-readonly_with_context", readonly_with_context != nullptr);
        EXPECT("property-readonly_with_context-get", readonly_with_context->get != nullptr);
        EXPECT("property-readonly_with_context-set", readonly_with_context->set == nullptr);
        EXPECT("property-readonly_with_context-context", readonly_with_context->context != nullptr);
    }
    {
        auto readonly_with_const_context = reflection->property.find("ReadonlyWithConstContext");

        ASSERT("property-readonly_with_const_context", readonly_with_const_context != nullptr);
        EXPECT("property-readonly_with_const_context-get", readonly_with_const_context->get != nullptr);
        EXPECT("property-readonly_with_const_context-set", readonly_with_const_context->set == nullptr);
        EXPECT("property-readonly_with_const_context-context", readonly_with_const_context->context != nullptr);
    }
    {
        auto readonly_const_with_const_context = reflection->property.find("ReadonlyConstWithConstContext");

        ASSERT("property-readonly_const_with_const_context", readonly_const_with_const_context != nullptr);
        EXPECT("property-readonly_const_with_const_context-get", readonly_const_with_const_context->get != nullptr);
        EXPECT("property-readonly_const_with_const_context-set", readonly_const_with_const_context->set == nullptr);
        EXPECT("property-readonly_const_with_const_context-context", readonly_const_with_const_context->context != nullptr);
    }
    {
        auto readonly_no_context = reflection->property.find("ReadonlyNoContext");

        ASSERT("property-readonly_no_context", readonly_no_context != nullptr);
        EXPECT("property-readonly_no_context-get", readonly_no_context->get != nullptr);
        EXPECT("property-readonly_no_context-set", readonly_no_context->set == nullptr);
        EXPECT("property-readonly_no_context-context", readonly_no_context->context == nullptr);
    }
    {
        auto readonly_const_no_context = reflection->property.find("ReadonlyConstNoContext");

        ASSERT("property-readonly_const_no_context", readonly_const_no_context != nullptr);
        EXPECT("property-readonly_const_no_context-get", readonly_const_no_context->get != nullptr);
        EXPECT("property-readonly_const_no_context-set", readonly_const_no_context->set == nullptr);
        EXPECT("property-readonly_const_no_context-context", readonly_const_no_context->context == nullptr);
    }
}


TEST_SPACE()
{

struct TestStaticFunctionPropertyStruct : TestStaticFieldPropertyStruct
{
    static int& WithContext() { return Property; } static void WithContext(int& value) { Property = value; }
    static int const& WithConstContext() { return Property; } static void WithConstContext(int const& value) { Property = value; }
    static int NoContext() { return 0; } static void NoContext(int) {}

    static int& ReadonlyWithContext() { return Property; }
    static int const& ReadonlyWithConstContext() { return Property; }
    static int ReadonlyNoContext() { return 0; }
};

} // TEST_SPACE

REFLECTABLE_DECLARATION(TestStaticFunctionPropertyStruct)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(TestStaticFunctionPropertyStruct)
    PROPERTY(WithContext)
    PROPERTY(WithConstContext)
    PROPERTY(NoContext)

    PROPERTY(ReadonlyWithContext)
    PROPERTY(ReadonlyWithConstContext)
    PROPERTY(ReadonlyNoContext)
REFLECTABLE_INIT()

TEST(TestLibrary::TestRegistryProperty, TestStaticFunctionProperty)
{
    auto type = rew::global.find("TestStaticFunctionPropertyStruct");

    ASSERT("type", type != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);

    {
        auto with_context = reflection->property.find("WithContext");

        ASSERT("property-with_context", with_context != nullptr);
        EXPECT("property-with_context-get", with_context->get != nullptr);
        EXPECT("property-with_context-set", with_context->set != nullptr);
        EXPECT("property-with_context-context", with_context->context != nullptr);
    }
    {
        auto with_const_context = reflection->property.find("WithConstContext");

        ASSERT("property-with_const_context", with_const_context != nullptr);
        EXPECT("property-with_const_context-get", with_const_context->get != nullptr);
        EXPECT("property-with_const_context-set", with_const_context->set != nullptr);
        EXPECT("property-with_const_context-context", with_const_context->context != nullptr);
    }
    {
        auto no_context = reflection->property.find("NoContext");

        ASSERT("property-no_context", no_context != nullptr);
        EXPECT("property-no_context-get", no_context->get != nullptr);
        EXPECT("property-no_context-set", no_context->set != nullptr);
        EXPECT("property-no_context-context", no_context->context == nullptr);
    }

    {
        auto readonly_with_context = reflection->property.find("ReadonlyWithContext");

        ASSERT("property-readonly_with_context", readonly_with_context != nullptr);
        EXPECT("property-readonly_with_context-get", readonly_with_context->get != nullptr);
        EXPECT("property-readonly_with_context-set", readonly_with_context->set == nullptr);
        EXPECT("property-readonly_with_context-context", readonly_with_context->context != nullptr);
    }
    {
        auto readonly_with_const_context = reflection->property.find("ReadonlyWithConstContext");

        ASSERT("property-readonly_with_const_context", readonly_with_const_context != nullptr);
        EXPECT("property-readonly_with_const_context-get", readonly_with_const_context->get != nullptr);
        EXPECT("property-readonly_with_const_context-set", readonly_with_const_context->set == nullptr);
        EXPECT("property-readonly_with_const_context-context", readonly_with_const_context->context != nullptr);
    }
    {
        auto readonly_no_context = reflection->property.find("ReadonlyNoContext");

        ASSERT("property-readonly_no_context", readonly_no_context != nullptr);
        EXPECT("property-readonly_no_context-get", readonly_no_context->get != nullptr);
        EXPECT("property-readonly_no_context-set", readonly_no_context->set == nullptr);
        EXPECT("property-readonly_no_context-context", readonly_no_context->context == nullptr);
    }
}


TEST_SPACE()
{

struct TestFreeFunctionPropertyStruct {};

int& WithContext() { return Property; } void WithContext(int& value) { Property = value; }
int const& WithConstContext() { return Property; } void WithConstContext(int const& value) { Property = value; }
int NoContext() { return 0; } void NoContext(int) {}

int& ReadonlyWithContext() { return Property; }
int const& ReadonlyWithConstContext() { return Property; }
int ReadonlyNoContext() { return 0; }

} // TEST_SPACE

REFLECTABLE_DECLARATION(TestFreeFunctionPropertyStruct)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(TestFreeFunctionPropertyStruct)
    FREE_PROPERTY(WithContext)
    FREE_PROPERTY(WithConstContext)
    FREE_PROPERTY(NoContext)

    FREE_PROPERTY(ReadonlyWithContext)
    FREE_PROPERTY(ReadonlyWithConstContext)
    FREE_PROPERTY(ReadonlyNoContext)
REFLECTABLE_INIT()

TEST(TestLibrary::TestRegistryProperty, TestFreeFunctionProperty)
{
    auto type = rew::global.find("TestFreeFunctionPropertyStruct");

    ASSERT("type", type != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);

    {
        auto with_context = reflection->property.find("WithContext");

        ASSERT("property-with_context", with_context != nullptr);
        EXPECT("property-with_context-get", with_context->get != nullptr);
        EXPECT("property-with_context-set", with_context->set != nullptr);
        EXPECT("property-with_context-context", with_context->context != nullptr);
    }
    {
        auto with_const_context = reflection->property.find("WithConstContext");

        ASSERT("property-with_const_context", with_const_context != nullptr);
        EXPECT("property-with_const_context-get", with_const_context->get != nullptr);
        EXPECT("property-with_const_context-set", with_const_context->set != nullptr);
        EXPECT("property-with_const_context-context", with_const_context->context != nullptr);
    }
    {
        auto no_context = reflection->property.find("NoContext");

        ASSERT("property-no_context", no_context != nullptr);
        EXPECT("property-no_context-get", no_context->get != nullptr);
        EXPECT("property-no_context-set", no_context->set != nullptr);
        EXPECT("property-no_context-context", no_context->context == nullptr);
    }

    {
        auto readonly_with_context = reflection->property.find("ReadonlyWithContext");

        ASSERT("property-readonly_with_context", readonly_with_context != nullptr);
        EXPECT("property-readonly_with_context-get", readonly_with_context->get != nullptr);
        EXPECT("property-readonly_with_context-set", readonly_with_context->set == nullptr);
        EXPECT("property-readonly_with_context-context", readonly_with_context->context != nullptr);
    }
    {
        auto readonly_with_const_context = reflection->property.find("ReadonlyWithConstContext");

        ASSERT("property-readonly_with_const_context", readonly_with_const_context != nullptr);
        EXPECT("property-readonly_with_const_context-get", readonly_with_const_context->get != nullptr);
        EXPECT("property-readonly_with_const_context-set", readonly_with_const_context->set == nullptr);
        EXPECT("property-readonly_with_const_context-context", readonly_with_const_context->context != nullptr);
    }
    {
        auto readonly_no_context = reflection->property.find("ReadonlyNoContext");

        ASSERT("property-readonly_no_context", readonly_no_context != nullptr);
        EXPECT("property-readonly_no_context-get", readonly_no_context->get != nullptr);
        EXPECT("property-readonly_no_context-set", readonly_no_context->set == nullptr);
        EXPECT("property-readonly_no_context-context", readonly_no_context->context == nullptr);
    }
}
