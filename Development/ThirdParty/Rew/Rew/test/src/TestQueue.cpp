#include <RewTestingBase.hpp>

#include <Rew/BuiltIn/queue.hpp>

TEST(TestBuiltin, TestQueue)
{
    rew::reflectable<std::queue<int>>();

    auto type = rew::global.find("std::queue<int>");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "std::queue<int>");
    EXPECT("type-size", type->size == sizeof(std::queue<int>));
    EXPECT("type-context", type->context != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("reflection-name", reflection->name == "std::queue<int>");

    EXPECT("factory-R()", reflection->factory.find("std::queue<int>()") != nullptr);

    #ifdef REW_FULLY_ENABLE
    EXPECT("factory-R(container_type const&)", reflection->factory.find("std::queue<int>(std::deque<int> const&)") != nullptr);
    #endif // REW_FULLY_ENABLE

    EXPECT("factory-R(R const&)", reflection->factory.find("std::queue<int>(std::queue<int> const&)") != nullptr);

    EXPECT("function-operator=", reflection->function.find("operator=") != nullptr);
    EXPECT("function-front", reflection->function.find("front") != nullptr);
    EXPECT("function-back", reflection->function.find("back") != nullptr);
    EXPECT("function-empty", reflection->function.find("empty") != nullptr);
    EXPECT("function-size", reflection->function.find("size") != nullptr);
    EXPECT("function-push", reflection->function.find("push") != nullptr);
    EXPECT("function-pop", reflection->function.find("pop") != nullptr);

    #ifdef REW_FULLY_ENABLE
    EXPECT("function-swap", reflection->function.find("swap") != nullptr);
    #endif // REW_FULLY_ENABLE
}
