#include <gtest/gtest.h>
#include <Refureku/Refureku.h>

#include "TestStruct.h"
#include "TestClass.h"
#include "TestClass2.h"
#include "TestEnum.h"
#include "TestNamespace.h"
#include "TypeTemplateClassTemplate.h"

//=========================================================
//=========== Archetype::getAccessSpecifier ===============
//=========================================================

TEST(Rfk_Archetype_getAccessSpecifier, FundamentalArchetypes)
{
	EXPECT_EQ(rfk::getArchetype<void>()->getAccessSpecifier(), rfk::EAccessSpecifier::Undefined);
	EXPECT_EQ(rfk::getArchetype<int>()->getAccessSpecifier(), rfk::EAccessSpecifier::Undefined);
	EXPECT_EQ(rfk::getArchetype<char>()->getAccessSpecifier(), rfk::EAccessSpecifier::Undefined);
	EXPECT_EQ(rfk::getArchetype<long long>()->getAccessSpecifier(), rfk::EAccessSpecifier::Undefined);
}

TEST(Rfk_Archetype_getAccessSpecifier, NonNestedStructClass)
{
	EXPECT_EQ(rfk::getArchetype<TestClass>()->getAccessSpecifier(), rfk::EAccessSpecifier::Undefined);
	EXPECT_EQ(rfk::getArchetype<test_namespace::TestNamespaceNestedClass>()->getAccessSpecifier(), rfk::EAccessSpecifier::Undefined);
}

TEST(Rfk_Archetype_getAccessSpecifier, PublicNestedStructClass)
{
	EXPECT_EQ(rfk::getArchetype<TestStruct::NestedClass>()->getAccessSpecifier(), rfk::EAccessSpecifier::Public);
	EXPECT_EQ(rfk::getArchetype<TestStruct::NestedStruct>()->getAccessSpecifier(), rfk::EAccessSpecifier::Public);
}

TEST(Rfk_Archetype_getAccessSpecifier, ProtectedNestedStructClass)
{
	EXPECT_EQ(TestClass::staticGetArchetype().getNestedClassByName("NestedClass")->getAccessSpecifier(), rfk::EAccessSpecifier::Protected);
	EXPECT_EQ(TestClass::staticGetArchetype().getNestedClassByName("NestedClass", rfk::EAccessSpecifier::Protected)->getAccessSpecifier(), rfk::EAccessSpecifier::Protected);
}

TEST(Rfk_Archetype_getAccessSpecifier, PrivateNestedStructClass)
{
	EXPECT_EQ(TestClass::staticGetArchetype().getNestedStructByName("NestedStruct")->getAccessSpecifier(), rfk::EAccessSpecifier::Private);
	EXPECT_EQ(TestClass::staticGetArchetype().getNestedStructByName("NestedStruct", rfk::EAccessSpecifier::Private)->getAccessSpecifier(), rfk::EAccessSpecifier::Private);
}

TEST(Rfk_Archetype_getAccessSpecifier, NonNestedClassTemplate)
{
	EXPECT_EQ(rfk::getArchetype<SingleTypeTemplateClassTemplate>()->getAccessSpecifier(), rfk::EAccessSpecifier::Undefined);
}

TEST(Rfk_Archetype_getAccessSpecifier, NamespaceNestedClassTemplate)
{
	EXPECT_EQ(rfk::getArchetype<template_namespace::ClassTemplateInNamespace>()->getAccessSpecifier(), rfk::EAccessSpecifier::Undefined);
}

TEST(Rfk_Archetype_getAccessSpecifier, ClassNestedClassTemplate)
{
	EXPECT_EQ(rfk::getArchetype<ClassWithNestedClassTemplate::PublicClassTemplateInClass>()->getAccessSpecifier(), rfk::EAccessSpecifier::Public);
}

TEST(Rfk_Archetype_getAccessSpecifier, NonNestedClassTemplateInstantiation)
{
	EXPECT_EQ(rfk::getArchetype<SingleTypeTemplateClassTemplate<int>>()->getAccessSpecifier(), rfk::EAccessSpecifier::Undefined);
}

TEST(Rfk_Archetype_getAccessSpecifier, NonNestedEnum)
{
	EXPECT_EQ(rfk::getEnum<TestEnum>()->getAccessSpecifier(), rfk::EAccessSpecifier::Undefined);
	EXPECT_EQ(rfk::getEnum<test_namespace::TestNamespaceNestedEnum>()->getAccessSpecifier(), rfk::EAccessSpecifier::Undefined);
}

TEST(Rfk_Archetype_getAccessSpecifier, PublicNestedEnum)
{
	EXPECT_EQ(rfk::getEnum<TestClass::NestedEnum>()->getAccessSpecifier(), rfk::EAccessSpecifier::Public);
}

TEST(Rfk_Archetype_getAccessSpecifier, ProtectedNestedEnum)
{
	EXPECT_EQ(TestClass2::staticGetArchetype().getNestedEnumByName("ProtectedNestedEnum")->getAccessSpecifier(), rfk::EAccessSpecifier::Protected);
	EXPECT_EQ(TestClass2::staticGetArchetype().getNestedEnumByName("ProtectedNestedEnum", rfk::EAccessSpecifier::Protected)->getAccessSpecifier(), rfk::EAccessSpecifier::Protected);
}

TEST(Rfk_Archetype_getAccessSpecifier, PrivateNestedEnum)
{
	EXPECT_EQ(TestClass2::staticGetArchetype().getNestedEnumByName("PrivateNestedEnum")->getAccessSpecifier(), rfk::EAccessSpecifier::Private);
	EXPECT_EQ(TestClass2::staticGetArchetype().getNestedEnumByName("PrivateNestedEnum", rfk::EAccessSpecifier::Private)->getAccessSpecifier(), rfk::EAccessSpecifier::Private);
}

//=========================================================
//============== Archetype::getMemorySize =================
//=========================================================

TEST(Rfk_Archetype_getMemorySize, FundamentalType)
{
	EXPECT_EQ(rfk::getArchetype<void>()->getMemorySize(), 0u);
	EXPECT_EQ(rfk::getArchetype<std::nullptr_t>()->getMemorySize(), sizeof(std::nullptr_t));
	EXPECT_EQ(rfk::getArchetype<bool>()->getMemorySize(), sizeof(bool));
	EXPECT_EQ(rfk::getArchetype<char>()->getMemorySize(), sizeof(char));
	EXPECT_EQ(rfk::getArchetype<signed char>()->getMemorySize(), sizeof(signed char));
	EXPECT_EQ(rfk::getArchetype<unsigned char>()->getMemorySize(), sizeof(unsigned char));
	EXPECT_EQ(rfk::getArchetype<wchar_t>()->getMemorySize(), sizeof(wchar_t));
	EXPECT_EQ(rfk::getArchetype<char16_t>()->getMemorySize(), sizeof(char16_t));
	EXPECT_EQ(rfk::getArchetype<char32_t>()->getMemorySize(), sizeof(char32_t));
	EXPECT_EQ(rfk::getArchetype<short>()->getMemorySize(), sizeof(short));
	EXPECT_EQ(rfk::getArchetype<unsigned short>()->getMemorySize(), sizeof(unsigned short));
	EXPECT_EQ(rfk::getArchetype<int>()->getMemorySize(), sizeof(int));
	EXPECT_EQ(rfk::getArchetype<unsigned int>()->getMemorySize(), sizeof(unsigned int));
	EXPECT_EQ(rfk::getArchetype<long>()->getMemorySize(), sizeof(long));
	EXPECT_EQ(rfk::getArchetype<unsigned long>()->getMemorySize(), sizeof(unsigned long));
	EXPECT_EQ(rfk::getArchetype<long long>()->getMemorySize(), sizeof(long long));
	EXPECT_EQ(rfk::getArchetype<unsigned long long>()->getMemorySize(), sizeof(unsigned long long));
	EXPECT_EQ(rfk::getArchetype<float>()->getMemorySize(), sizeof(float));
	EXPECT_EQ(rfk::getArchetype<double>()->getMemorySize(), sizeof(double));
	EXPECT_EQ(rfk::getArchetype<long double>()->getMemorySize(), sizeof(long double));
}

TEST(Rfk_Archetype_getMemorySize, StructClass)
{
	EXPECT_EQ(rfk::getArchetype<TestClass>()->getMemorySize(), sizeof(TestClass));
}

TEST(Rfk_Archetype_getMemorySize, ClassTemplate)
{
	EXPECT_EQ(rfk::getArchetype<SingleTypeTemplateClassTemplate>()->getMemorySize(), 0u); //Dependant type
}

TEST(Rfk_Archetype_getMemorySize, ClassTemplateInstantiation)
{
	EXPECT_EQ(rfk::getArchetype<SingleTypeTemplateClassTemplate<int>>()->getMemorySize(), sizeof(SingleTypeTemplateClassTemplate<int>));
}

TEST(Rfk_Archetype_getMemorySize, Enum)
{
	EXPECT_EQ(rfk::getEnum<TestEnum>()->getMemorySize(), sizeof(TestEnum));
	EXPECT_EQ(rfk::getEnum<TestEnumClass>()->getMemorySize(), sizeof(TestEnumClass));
}

//=========================================================
//============ Archetype::setAccessSpecifier ==============
//=========================================================

TEST(Rfk_Archetype_setAccessSpecifier, setAccessSpecifier)
{
	rfk::Enum e("Test", 0u, rfk::getArchetype<int>(), nullptr);

	e.setAccessSpecifier(rfk::EAccessSpecifier::Public);
	EXPECT_EQ(e.getAccessSpecifier(), rfk::EAccessSpecifier::Public);
	
	e.setAccessSpecifier(rfk::EAccessSpecifier::Protected);
	EXPECT_EQ(e.getAccessSpecifier(), rfk::EAccessSpecifier::Protected);

	e.setAccessSpecifier(rfk::EAccessSpecifier::Private);
	EXPECT_EQ(e.getAccessSpecifier(), rfk::EAccessSpecifier::Private);
}