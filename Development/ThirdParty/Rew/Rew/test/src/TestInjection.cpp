#include <RewTestingBase.hpp>

TEST_SPACE()
{

struct TestInjectionStruct {};

} // TEST_SPACE

REFLECTABLE_DECLARATION(TestInjectionStruct)
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(TestInjectionStruct)
    FACTORY(R())
    FACTORY(R(R))
REFLECTABLE_INIT()


template <typename T>
struct ToString
{
    std::string Call()
    {
        return "name: " + rew::name_of<T>();
    }
};

struct TestToStringInjection : rew::injectable_t
{
    template <typename ReflectableType>
    void type(rew::type_t& type)
    {
        rew::find_or_add_meta(type.reflection->meta, "ToString", ToString<ReflectableType>());
    }
};

// will reflect injection to all types
// for correct registry u must add injection before all library includes
REFLECTABLE_INJECTION_DECLARATION(0, TestToStringInjection)
REFLECTABLE_DECLARATION_INIT()

TEST(TestLibrary, TestDefaultInjection)
{
    auto type = rew::global.find("TestInjectionStruct");

    ASSERT("type", type != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("before_injection", reflection->meta.find("ToString") == nullptr);
    
    auto injection = type->injection.find("TestToStringInjection");

    ASSERT("injection", injection != nullptr);

    // std::any to_string = TestToStringInjection(); // will destroy rvalue object after copying to any
    auto to_string = std::make_any<TestToStringInjection>(); // will emplace to any
    injection->call(injection->type->context(to_string));

    auto meta = reflection->meta.find("ToString");

    ASSERT("after_injection0", meta != nullptr);

    auto value = std::any_cast<ToString<TestInjectionStruct>>(&meta->value);
    EXPECT("after_injection1", value != nullptr && value->Call() == "name: TestInjectionStruct");
}


struct TestVirusInjection : rew::injectable_t
{
    template <typename ReflectableType, typename FunctionType>
    void factory(rew::factory_t& factory)
    {
        rew::find_or_add_meta(factory.meta, "IsDefaultConstructible", factory.arguments.size() == 0);
    }
};

REFLECTABLE_DECLARATION(TestVirusInjection)
REFLECTABLE_DECLARATION_INIT()

TEST(TestLibrary, TestDynamicInjection)
{
    auto type = rew::global.find("TestInjectionStruct");

    ASSERT("type", type != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);

    ASSERT("before_add-injection", type->injection.find("TestVirusInjection") == nullptr);
    
    rew::find_or_add_injection<TestInjectionStruct, TestVirusInjection>(type);
 
    auto injection = type->injection.find("TestVirusInjection");

    ASSERT("after_add-injection", injection != nullptr);

    {
        auto default_constructible = reflection->factory.find("TestInjectionStruct()")->meta.find("IsDefaultConstructible");
        auto no_default_constructible = reflection->factory.find("TestInjectionStruct(TestInjectionStruct)")->meta.find("IsDefaultConstructible");

        EXPECT("before_injection", default_constructible == nullptr && no_default_constructible == nullptr);
    }

    auto virus = std::make_any<TestVirusInjection>();
    injection->call(injection->type->context(virus));

    {
        auto default_constructible = reflection->factory.find("TestInjectionStruct()")->meta.find("IsDefaultConstructible");
        auto no_default_constructible = reflection->factory.find("TestInjectionStruct(TestInjectionStruct)")->meta.find("IsDefaultConstructible");

        EXPECT("after_injection0", default_constructible != nullptr && no_default_constructible != nullptr);

        auto value0 = std::any_cast<bool>(&default_constructible->value);
        auto value1 = std::any_cast<bool>(&no_default_constructible->value);

        EXPECT("after_injection1", value0 != nullptr && *value0 == true && value1 != nullptr && *value1 == false);
    }
}
