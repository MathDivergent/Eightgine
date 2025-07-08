#include <RewTestingBase.hpp>

#include <cstdint>

TEST_SPACE()
{

template <typename T>
struct TestContainerWithIteratorUsing
{
    struct Iterator {};

    TestContainerWithIteratorUsing(Iterator, Iterator) {}
    void Insert(Iterator, T) {}
    std::int32_t Size() const { return 0; }

    Iterator* Head = nullptr;
};

} // TEST_SPACE

REFLECTABLE_USING(Test_std_int32_t, std::int32_t)

REFLECTABLE_DECLARATION(Test_std_int32_t)
    REFLECTABLE_NAME("std::int32_t")
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(Test_std_int32_t)
    FACTORY(Test_std_int32_t())
    FACTORY(R(R)) // same as Test_std_int32_t(Test_std_int32_t)
REFLECTABLE_INIT()

// will not compile!
// TEMPLATE_REFLECTABLE_DECLARATION(template <typename T>, TestContainerWithIteratorUsing<T>::Iterator)
//     REFLECTABLE_NAME(rew::name_of<TestContainerWithIteratorUsing<T>>() + "::Iterator")
// REFLECTABLE_DECLARATION_INIT()

// TEMPLATE_REFLECTABLE(template <typename T>, TestContainerWithIteratorUsing<T>::Iterator)
// REFLECTABLE_INIT()

TEMPLATE_REFLECTABLE_USING
(
    template <typename T>, TestContainerWithIteratorUsing_Iterator,
    TestContainerWithIteratorUsing_Iterator<T>, typename TestContainerWithIteratorUsing<T>::Iterator
)

TEMPLATE_REFLECTABLE_DECLARATION(template <typename T>, TestContainerWithIteratorUsing_Iterator<T>)
    REFLECTABLE_NAME(rew::name_of<TestContainerWithIteratorUsing<T>>() + "::Iterator")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE(template <typename T>, TestContainerWithIteratorUsing_Iterator<T>)
REFLECTABLE_INIT()

TEMPLATE_REFLECTABLE_DECLARATION(template <typename T>, TestContainerWithIteratorUsing<T>)
    REFLECTABLE_NAME("TestContainerWithIteratorUsing<" + rew::name_of<T>() + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE(template <typename T>, TestContainerWithIteratorUsing<T>)
    FUNCTION(Insert, void(TestContainerWithIteratorUsing_Iterator<T>, T))
    PROPERTY(Head, TestContainerWithIteratorUsing_Iterator<T>*)
    FACTORY(R(TestContainerWithIteratorUsing_Iterator<T>, TestContainerWithIteratorUsing_Iterator<T>))
    FUNCTION(Size, Test_std_int32_t() const)
REFLECTABLE_INIT()

TEST(TestLibrary, TestUsing)
{
    rew::reflectable<TestContainerWithIteratorUsing<int>>();

    auto type = rew::global.find("TestContainerWithIteratorUsing<int>");

    ASSERT("type", type != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);

    auto function0 = reflection->function.find("Insert");

    EXPECT("function0",
        function0 != nullptr &&
        function0->find("void(TestContainerWithIteratorUsing<int>::Iterator, int)") != nullptr);

    auto function1 = reflection->function.find("Size");

    EXPECT("function1",
        function1 != nullptr &&
        function1->find("std::int32_t() const") != nullptr);

    auto property = reflection->property.find("Head");

    EXPECT("property",
        property != nullptr &&
        property->type != nullptr &&
        property->type->name == "TestContainerWithIteratorUsing<int>::Iterator*");

    auto factory = reflection->factory.find("TestContainerWithIteratorUsing<int>(TestContainerWithIteratorUsing<int>::Iterator, TestContainerWithIteratorUsing<int>::Iterator)");

    EXPECT("factory", factory != nullptr);
}
