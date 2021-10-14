#include <cstring>	//std::strcmp

#include <gtest/gtest.h>
#include <Refureku/Refureku.h>

#include "TestClass.h"
#include "TestEnum.h"
#include "SingleTypeTemplateClassTemplate.h"
#include "MultipleTypeTemplateClassTemplate.h"

//=========================================================
//================== Entity::getName ======================
//=========================================================

TEST(Rfk_Entity_getName, Class_getName)
{
	EXPECT_TRUE(std::strcmp(rfk::getArchetype<TestClass>()->getName(), "TestClass") == 0);	//struct/class
	EXPECT_TRUE(std::strcmp(TestClass::staticGetArchetype().getNestedClassByName("NestedClass")->getName(), "NestedClass") == 0);	//Nested struct/class
}

TEST(Rfk_Entity_getName, Method_getName)
{
	EXPECT_TRUE(std::strcmp(TestClass::staticGetArchetype().getMethodByName("getIntField")->getName(), "getIntField") == 0);
	EXPECT_TRUE(std::strcmp(TestClass::staticGetArchetype().getStaticMethodByName("getIntStaticField")->getName(), "getIntStaticField") == 0);
}

TEST(Rfk_Entity_getName, Field_getName)
{
	EXPECT_TRUE(std::strcmp(TestClass::staticGetArchetype().getFieldByName("_intField")->getName(), "_intField") == 0);
	EXPECT_TRUE(std::strcmp(TestClass::staticGetArchetype().getStaticFieldByName("_intStaticField")->getName(), "_intStaticField") == 0);
}

TEST(Rfk_Entity_getName, Variable_getName)
{
	EXPECT_TRUE(std::strcmp(rfk::getDatabase().getVariableByName("var_global_extern")->getName(), "var_global_extern") == 0);
	EXPECT_TRUE(std::strcmp(rfk::getDatabase().getNamespaceByName("test_namespace")->getVariableByName("var_nested_extern")->getName(), "var_nested_extern") == 0);
}

TEST(Rfk_Entity_getName, Function_getName)
{
	EXPECT_TRUE(std::strcmp(rfk::getDatabase().getFunctionByName("func_return_noParam")->getName(), "func_return_noParam") == 0);	//Without parameters
	EXPECT_TRUE(std::strcmp(rfk::getDatabase().getFunctionByName("func_return_singleParam")->getName(), "func_return_singleParam") == 0); //With parameters
	EXPECT_TRUE(std::strcmp(rfk::getDatabase().getNamespaceByName("test_namespace")->getFunctionByName("func_nested_return_noParam")->getName(), "func_nested_return_noParam") == 0); //With parameters
}

TEST(Rfk_Entity_getName, Namespace_getName)
{
	EXPECT_TRUE(std::strcmp(rfk::getDatabase().getNamespaceByName("test_namespace")->getName(), "test_namespace") == 0);	//Global namespace
	EXPECT_TRUE(std::strcmp(rfk::getDatabase().getNamespaceByName("test_namespace")->getNamespaceByName("nested_namespace")->getName(), "nested_namespace") == 0);	//Nested namespace
}

TEST(Rfk_Entity_getName, Enum_getName)
{
	EXPECT_TRUE(std::strcmp(rfk::getEnum<TestEnum>()->getName(), "TestEnum") == 0);				//Enum
	EXPECT_TRUE(std::strcmp(rfk::getEnum<TestEnumClass>()->getName(), "TestEnumClass") == 0);	//Enum class
	EXPECT_TRUE(std::strcmp(rfk::getDatabase().getNamespaceByName("test_namespace")->getEnumByName("TestNamespaceNestedEnum")->getName(), "TestNamespaceNestedEnum") == 0);	//Namespace nested enum class
}

TEST(Rfk_Entity_getName, EnumValue_getName)
{
	EXPECT_TRUE(std::strcmp(rfk::getEnum<TestEnum>()->getEnumValueByName("TestEnumValue1")->getName(), "TestEnumValue1") == 0);
	EXPECT_TRUE(std::strcmp(rfk::getEnum<TestEnum>()->getEnumValueByName("TestEnumValue3")->getName(), "TestEnumValue3") == 0);
	EXPECT_TRUE(std::strcmp(rfk::getEnum<TestEnumClass>()->getEnumValueByName("Value1")->getName(), "Value1") == 0);
	EXPECT_TRUE(std::strcmp(rfk::getEnum<TestEnumClass>()->getEnumValueByName("Value3")->getName(), "Value3") == 0);
}

TEST(Rfk_Entity_getName, ClassTemplate_getName)
{
	EXPECT_TRUE(std::strcmp(rfk::getArchetype<SingleTypeTemplateClassTemplate>()->getName(), "SingleTypeTemplateClassTemplate") == 0);
	EXPECT_TRUE(std::strcmp(rfk::getArchetype<MultipleTypeTemplateClassTemplate>()->getName(), "MultipleTypeTemplateClassTemplate") == 0);
}

TEST(Rfk_Entity_getName, ClassTemplateInstantiation_getName)
{
	EXPECT_TRUE(std::strcmp(rfk::entityCast<rfk::Class>(rfk::getArchetype<SingleTypeTemplateClassTemplate<int>>())->asTemplateInstantiation()->getName(), "SingleTypeTemplateClassTemplate") == 0);
	EXPECT_TRUE(std::strcmp(rfk::entityCast<rfk::Class>(rfk::getArchetype<MultipleTypeTemplateClassTemplate<int, TestEnum, TestClass>>())->asTemplateInstantiation()->getName(), "MultipleTypeTemplateClassTemplate") == 0);
}

