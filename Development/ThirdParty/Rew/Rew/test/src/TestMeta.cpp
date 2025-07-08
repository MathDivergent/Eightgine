#include <RewTestingBase.hpp>

#include <vector> // vector
#include <string> // string

TEST_SPACE()
{

struct TestParentMetaStruct {};

struct TestMetaStruct : TestParentMetaStruct
{
    TestMetaStruct() {}
    static int Function() { return 0; }
    void Function(double value) {}
    float Property = 0.f;
    int Constant = 0;

    inline static char* TestDescriptor = nullptr;
};

int TestMetaStructPropertyCast(float) { return 0; }

namespace TestMetaStructFlags
{

enum Type : long { Abstract, Internal, Serializable };

} // TestMetaStructFlags

struct TestMetaStructConfigs
{
    bool const IsVisible = false;
    float LifeTime = -1,f;
    char const* Name = "UNKNOWN";
};

std::string sMetaName = "Descriptors";
void* TestDescriptorReadOnly = nullptr;
char const* sToolTip = "Don't use manually.";

struct FunctionHandlerStruct
{
    void operator()(double) {}

    bool IsAsync = true;
};

FunctionHandlerStruct FunctionHandler{ false };

} // TEST_SPACE

REFLECTABLE_DECLARATION(TestParentMetaStruct)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(TestParentMetaStruct)
REFLECTABLE_INIT()

REFLECTABLE_DECLARATION(TestMetaStruct)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(TestMetaStruct)
    META("DisplayName", "Meta Struct")
    // you can add SUBMETA(...) after any META(...) or SUBMETA(...), but for test - we will ommit all cases
    META("Configs", TestMetaStructConfigs{ true, 100.f }) SUBMETA("Hash", int(0x0101))
    META(sMetaName, std::vector<void*>{ &R::TestDescriptor, &TestDescriptorReadOnly }) SUBMETA("ToolTip", sToolTip)

    PARENT(TestParentMetaStruct) META("Hidden", true)

    FACTORY(R()) META("ConstructionType", std::string("PostLoad"))

    FUNCTION(Function, int()) META("MinValue", -1) META("MaxValue", 10) META("static", true)
    FUNCTION(Function, void(double)) META("Handler", FunctionHandler)

    PROPERTY(Property) META("Cast", &TestMetaStructPropertyCast)
    META("Serializable") // meta without value
    META("Flags", TestMetaStructFlags::Serializable | TestMetaStructFlags::Internal)

    PROPERTY(Constant) META("Mutable", true) SUBMETA("Status", -1) SUBMETA("Info", nullptr)
    SUBMETA("Readonly") // submeta without value
REFLECTABLE_INIT()

TEST(TestLibrary, TestMeta)
{
    auto type = rew::global.find("TestMetaStruct");

    ASSERT("type", type != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);

    {
        auto meta0 = reflection->meta.find("DisplayName");

        ASSERT("reflection-meta0", meta0 != nullptr);

        auto value = std::any_cast<char const*>(&meta0->value);

        EXPECT("reflection-meta0-value", value != nullptr && std::string(*value) == "Meta Struct");
    }
    {
        auto meta1 = reflection->meta.find("Configs");

        ASSERT("reflection-meta1", meta1 != nullptr);

        auto value = std::any_cast<TestMetaStructConfigs>(&meta1->value);

        EXPECT("reflection-meta1-value", value != nullptr && value->IsVisible == true && value->LifeTime == 100.f);

        {
            auto submeta0 = meta1->meta.find("Hash");

            ASSERT("reflection-meta1-submenta0", submeta0 != nullptr);

            auto value = std::any_cast<int>(&submeta0->value);

            EXPECT("reflection-meta1-submenta0", value != nullptr && *value == int(0x0101));
        }
    }
    {
        auto meta2 = reflection->meta.find(sMetaName);

        ASSERT("reflection-meta2", meta2 != nullptr);

        auto value = std::any_cast<std::vector<void*>>(&meta2->value);

        EXPECT("reflection-meta2-value", value != nullptr && value->size() == 2 && (*value)[0] == &TestMetaStruct::TestDescriptor && (*value)[1] == &TestDescriptorReadOnly);

        {
            auto submeta0 = meta2->meta.find("ToolTip");

            ASSERT("reflection-meta2-submenta0", submeta0 != nullptr);

            auto value = std::any_cast<char const*>(&submeta0->value);

            EXPECT("reflection-meta2-submenta0", value != nullptr && std::string(*value) == sToolTip);
        }
    }

    auto parent = reflection->parent.find("TestParentMetaStruct");

    ASSERT("parent", parent != nullptr);

    {
        auto meta0 = parent->meta.find("Hidden");

        ASSERT("parent-meta0", meta0 != nullptr);

        auto value = std::any_cast<bool>(&meta0->value);

        EXPECT("parent-meta0-value-init", value != nullptr && *value == true);
    }

    auto factory = reflection->factory.find("TestMetaStruct()");

    ASSERT("factory", factory != nullptr);

    {
        auto meta0 = factory->meta.find("ConstructionType");

        ASSERT("factory-meta0", meta0 != nullptr);

        auto value = std::any_cast<std::string>(&meta0->value);

        EXPECT("factory-meta0-value", value != nullptr && *value == "PostLoad");
    }

    auto overloads = reflection->function.find("Function");

    ASSERT("overloads", overloads != nullptr);

    auto function0 = overloads->find("int()");

    ASSERT("function0", function0 != nullptr);

    {
        auto meta0 = function0->meta.find("MinValue");

        ASSERT("function0-meta0", meta0 != nullptr);

        auto value = std::any_cast<int>(&meta0->value);

        EXPECT("function0-meta0-value", value != nullptr && *value == -1);
    }
    {
        auto meta1 = function0->meta.find("MaxValue");

        ASSERT("function0-meta1", meta1 != nullptr);

        auto value = std::any_cast<int>(&meta1->value);

        EXPECT("function0-meta1-value", value != nullptr && *value == 10);
    }
    {
        auto meta2 = function0->meta.find("static");

        ASSERT("function0-meta2", meta2 != nullptr);

        auto value = std::any_cast<bool>(&meta2->value);

        EXPECT("function0-meta2-value", value != nullptr && *value == true);
    }

    auto function1 = overloads->find("void(double)");

    ASSERT("function1", function1 != nullptr);

    {
        auto meta0 = function1->meta.find("Handler");

        ASSERT("function1-meta0", meta0 != nullptr);

        auto value = std::any_cast<FunctionHandlerStruct>(&meta0->value);

        EXPECT("function1-meta0-value", value != nullptr && value->IsAsync == FunctionHandler.IsAsync);
    }

    auto property0 = reflection->property.find("Property");

    ASSERT("property0", property0 != nullptr);

    {
        using meta0_type = decltype(&TestMetaStructPropertyCast);

        auto meta0 = property0->meta.find("Cast");

        ASSERT("property0-meta0", meta0 != nullptr);

        auto value = std::any_cast<meta0_type>(&meta0->value);

        EXPECT("property0-meta0-value", value != nullptr && *value == &TestMetaStructPropertyCast);
    }
    {
        auto meta1 = property0->meta.find("Serializable");

        ASSERT("property0-meta1", meta1 != nullptr);
        EXPECT("property0-meta1-value", !meta1->value.has_value());
    }
    {
        auto meta2 = property0->meta.find("Flags");

        ASSERT("property0-meta2", meta2 != nullptr);

        auto value = std::any_cast<long>(&meta2->value);

        EXPECT("property0-meta2-value", value != nullptr && *value == (TestMetaStructFlags::Serializable | TestMetaStructFlags::Internal));
    }

    auto property1 = reflection->property.find("Constant");

    ASSERT("property1", property1 != nullptr);

    {
        auto meta0 = property1->meta.find("Mutable");

        ASSERT("meta0", meta0 != nullptr);

        auto value = std::any_cast<bool>(&meta0->value);

        EXPECT("Mutable", value != nullptr && *value == true);

        {
            auto submeta0 = meta0->meta.find("Status");

            ASSERT("property1-meta0-submenta0", submeta0 != nullptr);

            auto value = std::any_cast<int>(&submeta0->value);

            EXPECT("property1-meta0-submenta0", value != nullptr && *value == -1);
        }
        {
            auto submeta1 = meta0->meta.find("Info");

            ASSERT("property1-meta0-submenta1", submeta1 != nullptr);

            auto value = std::any_cast<std::nullptr_t>(&submeta1->value);

            EXPECT("property1-meta0-submenta1", value != nullptr && *value == nullptr);
        }
        {
            auto submeta2 = meta0->meta.find("Readonly");

            ASSERT("property1-meta0-submeta2", submeta2 != nullptr);
            EXPECT("property1-meta0-submeta2", !submeta2->value.has_value());
        }
    }
}
