#include <RewTestingBase.hpp>

#include <Rew/BuiltIn/complex.hpp>

TEST(TestBuiltin, TestComplex)
{
    rew::reflectable<std::complex<float>>();

    auto type = rew::global.find("std::complex<float>");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "std::complex<float>");
    EXPECT("type-size", type->size == sizeof(std::complex<float>));
    EXPECT("type-context", type->context != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("reflection-name", reflection->name == "std::complex<float>");

    EXPECT("factory-R()", reflection->factory.find("std::complex<float>()") != nullptr);
    EXPECT("factory-R(value_type, value_type)", reflection->factory.find("std::complex<float>(float, float)") != nullptr);
    EXPECT("factory-R(R const&)", reflection->factory.find("std::complex<float>(std::complex<float> const&)") != nullptr);

    EXPECT("function-operator=", reflection->function.find("operator=") != nullptr);
    EXPECT("function-operator+=", reflection->function.find("operator+=") != nullptr);
    EXPECT("function-operator-=", reflection->function.find("operator-=") != nullptr);
    EXPECT("function-operator*=", reflection->function.find("operator*=") != nullptr);
    EXPECT("function-operator/=", reflection->function.find("operator/=") != nullptr);

    EXPECT("property-real", reflection->property.find("real") != nullptr);
    EXPECT("property-imag", reflection->property.find("imag") != nullptr);
}
