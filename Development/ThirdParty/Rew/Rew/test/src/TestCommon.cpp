#include <RewTestingBase.hpp>

TEST(TestCommon, TestVoid)
{
    auto type = rew::global.find("void");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "void");
    EXPECT("type-size", type->size == 0);
    EXPECT("type-context", type->context == nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("reflection-name", reflection->name == "void");
}


TEST(TestCommon, TestNullptrT)
{
    auto type = rew::global.find("std::nullptr_t");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "std::nullptr_t");
    EXPECT("type-size", type->size == sizeof(std::nullptr_t));
    EXPECT("type-context", type->context != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("reflection-name", reflection->name == "std::nullptr_t");
}


TEST(TestCommon, TestSizeT)
{
    auto type = rew::global.find("std::size_t");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "std::size_t");
    EXPECT("type-size", type->size == sizeof(std::size_t));
    EXPECT("type-context", type->context != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("reflection-name", reflection->name == "std::size_t");

    EXPECT("factory-R()", reflection->factory.find("std::size_t()") != nullptr);
    EXPECT("factory-R(R)", reflection->factory.find("std::size_t(std::size_t)") != nullptr);
}

TEST(TestCommon, TestPtrDiffT)
{
    auto type = rew::global.find("std::ptrdiff_t");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "std::ptrdiff_t");
    EXPECT("type-size", type->size == sizeof(std::ptrdiff_t));
    EXPECT("type-context", type->context != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("reflection-name", reflection->name == "std::ptrdiff_t");

    EXPECT("factory-R()", reflection->factory.find("std::ptrdiff_t()") != nullptr);
    EXPECT("factory-R(R)", reflection->factory.find("std::ptrdiff_t(std::ptrdiff_t)") != nullptr);
}


TEST(TestCommon, TestBool)
{
    auto type = rew::global.find("bool");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "bool");
    EXPECT("type-size", type->size == sizeof(bool));
    EXPECT("type-context", type->context != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("reflection-name", reflection->name == "bool");

    EXPECT("factory-R()", reflection->factory.find("bool()") != nullptr);
    EXPECT("factory-R(R)", reflection->factory.find("bool(bool)") != nullptr);
}


TEST(TestCommon, TestChar)
{
    auto type = rew::global.find("char");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "char");
    EXPECT("type-size", type->size == sizeof(char));
    EXPECT("type-context", type->context != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("reflection-name", reflection->name == "char");

    EXPECT("factory-R()", reflection->factory.find("char()") != nullptr);
    EXPECT("factory-R(R)", reflection->factory.find("char(char)") != nullptr);
}

TEST(TestCommon, TestWChar)
{
    auto type = rew::global.find("wchar_t");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "wchar_t");
    EXPECT("type-size", type->size == sizeof(wchar_t));
    EXPECT("type-context", type->context != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("reflection-name", reflection->name == "wchar_t");

    EXPECT("factory-R()", reflection->factory.find("wchar_t()") != nullptr);
    EXPECT("factory-R(R)", reflection->factory.find("wchar_t(wchar_t)") != nullptr);
}

#if __cplusplus >= 202002L
TEST(TestCommon, TestChar8)
{
    auto type = rew::global.find("char8_t");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "char8_t");
    EXPECT("type-size", type->size == sizeof(char8_t));
    EXPECT("type-context", type->context != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("reflection-name", reflection->name == "char8_t");

    EXPECT("factory-R()", reflection->factory.find("char8_t()") != nullptr);
    EXPECT("factory-R(R)", reflection->factory.find("char8_t(char8_t)") != nullptr);
}
#endif // if

TEST(TestCommon, TestChar16)
{
    auto type = rew::global.find("char16_t");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "char16_t");
    EXPECT("type-size", type->size == sizeof(char16_t));
    EXPECT("type-context", type->context != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("reflection-name", reflection->name == "char16_t");

    EXPECT("factory-R()", reflection->factory.find("char16_t()") != nullptr);
    EXPECT("factory-R(R)", reflection->factory.find("char16_t(char16_t)") != nullptr);
}

TEST(TestCommon, TestChar32)
{
    auto type = rew::global.find("char32_t");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "char32_t");
    EXPECT("type-size", type->size == sizeof(char32_t));
    EXPECT("type-context", type->context != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("reflection-name", reflection->name == "char32_t");

    EXPECT("factory-R()", reflection->factory.find("char32_t()") != nullptr);
    EXPECT("factory-R(R)", reflection->factory.find("char32_t(char32_t)") != nullptr);
}


TEST(TestCommon, TestSignedChar)
{
    auto type = rew::global.find("signed char");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "signed char");
    EXPECT("type-size", type->size == sizeof(signed char));
    EXPECT("type-context", type->context != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("reflection-name", reflection->name == "signed char");

    EXPECT("factory-R()", reflection->factory.find("signed char()") != nullptr);
    EXPECT("factory-R(R)", reflection->factory.find("signed char(signed char)") != nullptr);
}

TEST(TestCommon, TestUnsignedChar)
{
    auto type = rew::global.find("unsigned char");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "unsigned char");
    EXPECT("type-size", type->size == sizeof(unsigned char));
    EXPECT("type-context", type->context != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("reflection-name", reflection->name == "unsigned char");

    EXPECT("factory-R()", reflection->factory.find("unsigned char()") != nullptr);
    EXPECT("factory-R(R)", reflection->factory.find("unsigned char(unsigned char)") != nullptr);
}

TEST(TestCommon, TestInt)
{
    auto type = rew::global.find("int");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "int");
    EXPECT("type-size", type->size == sizeof(int));
    EXPECT("type-context", type->context != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("reflection-name", reflection->name == "int");

    EXPECT("factory-R()", reflection->factory.find("int()") != nullptr);
    EXPECT("factory-R(R)", reflection->factory.find("int(int)") != nullptr);
}

TEST(TestCommon, TestUnsignedInt)
{
    auto type = rew::global.find("unsigned int");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "unsigned int");
    EXPECT("type-size", type->size == sizeof(unsigned int));
    EXPECT("type-context", type->context != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("reflection-name", reflection->name == "unsigned int");

    EXPECT("factory-R()", reflection->factory.find("unsigned int()") != nullptr);
    EXPECT("factory-R(R)", reflection->factory.find("unsigned int(unsigned int)") != nullptr);
}

TEST(TestCommon, TestLong)
{
    auto type = rew::global.find("long");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "long");
    EXPECT("type-size", type->size == sizeof(long));
    EXPECT("type-context", type->context != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("reflection-name", reflection->name == "long");

    EXPECT("factory-R()", reflection->factory.find("long()") != nullptr);
    EXPECT("factory-R(R)", reflection->factory.find("long(long)") != nullptr);
}

TEST(TestCommon, TestUnsignedLong)
{
    auto type = rew::global.find("unsigned long");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "unsigned long");
    EXPECT("type-size", type->size == sizeof(unsigned long));
    EXPECT("type-context", type->context != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("reflection-name", reflection->name == "unsigned long");

    EXPECT("factory-R()", reflection->factory.find("unsigned long()") != nullptr);
    EXPECT("factory-R(R)", reflection->factory.find("unsigned long(unsigned long)") != nullptr);
}

TEST(TestCommon, TestLongLong)
{
    auto type = rew::global.find("long long");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "long long");
    EXPECT("type-size", type->size == sizeof(long long));
    EXPECT("type-context", type->context != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("reflection-name", reflection->name == "long long");

    EXPECT("factory-R()", reflection->factory.find("long long()") != nullptr);
    EXPECT("factory-R(R)", reflection->factory.find("long long(long long)") != nullptr);
}

TEST(TestCommon, TestUnsignedLongLong)
{
    auto type = rew::global.find("unsigned long long");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "unsigned long long");
    EXPECT("type-size", type->size == sizeof(unsigned long long));
    EXPECT("type-context", type->context != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("reflection-name", reflection->name == "unsigned long long");

    EXPECT("factory-R()", reflection->factory.find("unsigned long long()") != nullptr);
    EXPECT("factory-R(R)", reflection->factory.find("unsigned long long(unsigned long long)") != nullptr);
}


TEST(TestCommon, TestFloat)
{
    auto type = rew::global.find("float");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "float");
    EXPECT("type-size", type->size == sizeof(float));
    EXPECT("type-context", type->context != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("reflection-name", reflection->name == "float");

    EXPECT("factory-R()", reflection->factory.find("float()") != nullptr);
    EXPECT("factory-R(R)", reflection->factory.find("float(float)") != nullptr);
}

TEST(TestCommon, TestDouble)
{
    auto type = rew::global.find("double");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "double");
    EXPECT("type-size", type->size == sizeof(double));
    EXPECT("type-context", type->context != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("reflection-name", reflection->name == "double");

    EXPECT("factory-R()", reflection->factory.find("double()") != nullptr);
    EXPECT("factory-R(R)", reflection->factory.find("double(double)") != nullptr);
}

TEST(TestCommon, TestLongDouble)
{
    auto type = rew::global.find("long double");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "long double");
    EXPECT("type-size", type->size == sizeof(long double));
    EXPECT("type-context", type->context != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("reflection-name", reflection->name == "long double");

    EXPECT("factory-R()", reflection->factory.find("long double()") != nullptr);
    EXPECT("factory-R(R)", reflection->factory.find("long double(long double)") != nullptr);
}
