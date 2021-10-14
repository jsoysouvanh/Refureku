#include <string_view>

#include <gtest/gtest.h>
#include <Refureku/Refureku.h>

#include "TestStruct.h"
#include "TestClass.h"
#include "TestClass2.h"
#include "TestEnum.h"
#include "TestNamespace.h"
#include "SingleTypeTemplateClassTemplate.h"
#include "MultipleTypeTemplateClassTemplate.h"

//=========================================================
//================== Entity::getName ======================
//=========================================================

TEST(Rfk_Entity_getName, Class_getName)
{
	EXPECT_STREQ(rfk::getArchetype<TestClass>()->getName(), "TestClass"); //struct/class
	EXPECT_STREQ(TestClass::staticGetArchetype().getNestedClassByName("NestedClass")->getName(), "NestedClass");	//Nested struct/class
}

TEST(Rfk_Entity_getName, ClassTemplate_getName)
{
	EXPECT_STREQ(rfk::getArchetype<SingleTypeTemplateClassTemplate>()->getName(), "SingleTypeTemplateClassTemplate");
	EXPECT_STREQ(rfk::getArchetype<MultipleTypeTemplateClassTemplate>()->getName(), "MultipleTypeTemplateClassTemplate");
}

TEST(Rfk_Entity_getName, ClassTemplateInstantiation_getName)
{
	EXPECT_STREQ(rfk::entityCast<rfk::Class>(rfk::getArchetype<SingleTypeTemplateClassTemplate<int>>())->asTemplateInstantiation()->getName(), "SingleTypeTemplateClassTemplate");
	EXPECT_STREQ(rfk::entityCast<rfk::Class>(rfk::getArchetype<MultipleTypeTemplateClassTemplate<int, TestEnum, TestClass>>())->asTemplateInstantiation()->getName(), "MultipleTypeTemplateClassTemplate");
}

TEST(Rfk_Entity_getName, Method_getName)
{
	EXPECT_STREQ(TestClass::staticGetArchetype().getMethodByName("getIntField")->getName(), "getIntField");
	EXPECT_STREQ(TestClass::staticGetArchetype().getStaticMethodByName("getIntStaticField")->getName(), "getIntStaticField");
}

TEST(Rfk_Entity_getName, Field_getName)
{
	EXPECT_STREQ(TestClass::staticGetArchetype().getFieldByName("_intField")->getName(), "_intField");
	EXPECT_STREQ(TestClass::staticGetArchetype().getStaticFieldByName("_intStaticField")->getName(), "_intStaticField");
}

TEST(Rfk_Entity_getName, Variable_getName)
{
	EXPECT_STREQ(rfk::getDatabase().getVariableByName("var_global_extern")->getName(), "var_global_extern");
	EXPECT_STREQ(rfk::getDatabase().getNamespaceByName("test_namespace")->getVariableByName("var_nested_extern")->getName(), "var_nested_extern");
}

TEST(Rfk_Entity_getName, Function_getName)
{
	EXPECT_STREQ(rfk::getDatabase().getFunctionByName("func_return_noParam")->getName(), "func_return_noParam");	//Without parameters
	EXPECT_STREQ(rfk::getDatabase().getFunctionByName("func_return_singleParam")->getName(), "func_return_singleParam"); //With parameters
	EXPECT_STREQ(rfk::getDatabase().getNamespaceByName("test_namespace")->getFunctionByName("func_nested_return_noParam")->getName(), "func_nested_return_noParam"); //With parameters
}

TEST(Rfk_Entity_getName, Namespace_getName)
{
	EXPECT_STREQ(rfk::getDatabase().getNamespaceByName("test_namespace")->getName(), "test_namespace");	//Global namespace
	EXPECT_STREQ(rfk::getDatabase().getNamespaceByName("test_namespace")->getNamespaceByName("nested_namespace")->getName(), "nested_namespace");	//Nested namespace
}

TEST(Rfk_Entity_getName, Enum_getName)
{
	EXPECT_STREQ(rfk::getEnum<TestEnum>()->getName(), "TestEnum");				//Enum
	EXPECT_STREQ(rfk::getEnum<TestEnumClass>()->getName(), "TestEnumClass");	//Enum class
	EXPECT_STREQ(rfk::getDatabase().getNamespaceByName("test_namespace")->getEnumByName("TestNamespaceNestedEnum")->getName(), "TestNamespaceNestedEnum");	//Namespace nested enum class
}

TEST(Rfk_Entity_getName, EnumValue_getName)
{
	EXPECT_STREQ(rfk::getEnum<TestEnum>()->getEnumValueByName("TestEnumValue1")->getName(), "TestEnumValue1");
	EXPECT_STREQ(rfk::getEnum<TestEnum>()->getEnumValueByName("TestEnumValue3")->getName(), "TestEnumValue3");
	EXPECT_STREQ(rfk::getEnum<TestEnumClass>()->getEnumValueByName("Value1")->getName(), "Value1");
	EXPECT_STREQ(rfk::getEnum<TestEnumClass>()->getEnumValueByName("Value3")->getName(), "Value3");
}

//=========================================================
//================== Entity::getId ========================
//=========================================================

TEST(Rfk_Entity_getId, getId)
{
	EXPECT_EQ(rfk::getArchetype<void>()->getId(), std::hash<std::string_view>()("void"));
}

//=========================================================
//================== Entity::getKind ======================
//=========================================================

TEST(Rfk_Entity_getKind, Struct_getKind)
{
	EXPECT_EQ(rfk::getArchetype<TestStruct>()->getKind(), rfk::EEntityKind::Struct);
}

TEST(Rfk_Entity_getKind, Class_getKind)
{
	EXPECT_EQ(rfk::getArchetype<TestClass>()->getKind(), rfk::EEntityKind::Class);
}

TEST(Rfk_Entity_getKind, ClassTemplate_getKind)
{
	EXPECT_EQ(rfk::getArchetype<SingleTypeTemplateClassTemplate>()->getKind(), rfk::EEntityKind::Class);
}

TEST(Rfk_Entity_getKind, ClassTemplateInstantiation_getKind)
{
	EXPECT_EQ(rfk::entityCast<rfk::Class>(rfk::getArchetype<SingleTypeTemplateClassTemplate<int>>())->asTemplateInstantiation()->getKind(), rfk::EEntityKind::Class);
}

TEST(Rfk_Entity_getKind, Method_getKind)
{
	EXPECT_EQ(TestClass::staticGetArchetype().getMethodByName("getIntField")->getKind(), rfk::EEntityKind::Method);	//non-static method
	EXPECT_EQ(TestClass::staticGetArchetype().getStaticMethodByName("getIntStaticField")->getKind(), rfk::EEntityKind::Method);	//static method
}

TEST(Rfk_Entity_getKind, Field_getKind)
{
	EXPECT_EQ(TestClass::staticGetArchetype().getFieldByName("_intField")->getKind(), rfk::EEntityKind::Field); //non-static field
	EXPECT_EQ(TestClass::staticGetArchetype().getStaticFieldByName("_intStaticField")->getKind(), rfk::EEntityKind::Field); //static field
}

TEST(Rfk_Entity_getKind, Variable_getKind)
{
	EXPECT_EQ(rfk::getDatabase().getVariableByName("var_global_extern")->getKind(), rfk::EEntityKind::Variable);
}

TEST(Rfk_Entity_getKind, Function_getKind)
{
	EXPECT_EQ(rfk::getDatabase().getFunctionByName("func_return_noParam")->getKind(), rfk::EEntityKind::Function);
}

TEST(Rfk_Entity_getKind, Namespace_getKind)
{
	EXPECT_EQ(rfk::getDatabase().getNamespaceByName("test_namespace")->getKind(), rfk::EEntityKind::Namespace);
}

TEST(Rfk_Entity_getKind, Enum_getKind)
{
	EXPECT_EQ(rfk::getEnum<TestEnum>()->getKind(), rfk::EEntityKind::Enum);			//Enum
	EXPECT_EQ(rfk::getEnum<TestEnumClass>()->getKind(), rfk::EEntityKind::Enum);	//Enum class
}

TEST(Rfk_Entity_getKind, EnumValue_getKind)
{
	EXPECT_EQ(rfk::getEnum<TestEnum>()->getEnumValueByName("TestEnumValue1")->getKind(), rfk::EEntityKind::EnumValue);	//Enum value
	EXPECT_EQ(rfk::getEnum<TestEnumClass>()->getEnumValueByName("Value3")->getKind(), rfk::EEntityKind::EnumValue);		//Enum class value
}

//=========================================================
//================ Entity::getOuterEntity =================
//=========================================================

TEST(Rfk_Entity_getOuterEntity, Struct_getOuterEntity)
{
	EXPECT_EQ(rfk::getArchetype<TestStruct>()->getOuterEntity(), nullptr);	//global struct
	EXPECT_EQ(rfk::getArchetype<test_namespace::TestNamespaceNestedStruct>()->getOuterEntity(), rfk::getDatabase().getNamespaceByName("test_namespace"));	//namespace nested struct
	EXPECT_EQ(rfk::getArchetype<TestStruct::NestedStruct>()->getOuterEntity(), rfk::getArchetype<TestStruct>());	//struct nested struct
	EXPECT_EQ(TestClass::staticGetArchetype().getNestedStructByName("NestedStruct")->getOuterEntity(), rfk::getArchetype<TestClass>());	//class nested struct
}

TEST(Rfk_Entity_getOuterEntity, Class_getOuterEntity)
{
	EXPECT_EQ(rfk::getArchetype<TestClass>()->getOuterEntity(), nullptr);	//global class
	EXPECT_EQ(rfk::getArchetype<test_namespace::TestNamespaceNestedClass>()->getOuterEntity(), rfk::getDatabase().getNamespaceByName("test_namespace"));	//namespace nested class
	EXPECT_EQ(rfk::getArchetype<TestStruct::NestedClass>()->getOuterEntity(), rfk::getArchetype<TestStruct>());	//struct nested class
	EXPECT_EQ(TestClass::staticGetArchetype().getNestedClassByName("NestedClass")->getOuterEntity(), rfk::getArchetype<TestClass>());	//class nested class
}

TEST(Rfk_Entity_getOuterEntity, ClassTemplate_getOuterEntity)
{
	EXPECT_EQ(rfk::getArchetype<SingleTypeTemplateClassTemplate>()->getOuterEntity(), nullptr);
	//TODO: Template classes can't be nested in other entities for now, they will always return nullptr for the outer entity. Need to fix that.
}

TEST(Rfk_Entity_getOuterEntity, ClassTemplateInstantiation_getOuterEntity)
{
	EXPECT_EQ(rfk::entityCast<rfk::Class>(rfk::getArchetype<SingleTypeTemplateClassTemplate<int>>())->asTemplateInstantiation()->getOuterEntity(), nullptr);
}

TEST(Rfk_Entity_getOuterEntity, Method_getOuterEntity)
{
	EXPECT_EQ(TestClass::staticGetArchetype().getMethodByName("getIntField")->getOuterEntity(), rfk::getArchetype<TestClass>());	//non-static method
	EXPECT_EQ(TestClass::staticGetArchetype().getStaticMethodByName("getIntStaticField")->getOuterEntity(), rfk::getArchetype<TestClass>());	//static method
	EXPECT_EQ(TestClass2::staticGetArchetype().getMethodByName("getIntField", rfk::EMethodFlags::Default, true)->getOuterEntity(), rfk::getArchetype<TestClass>()); //Inherited method
	EXPECT_EQ(TestClass2::staticGetArchetype().getStaticMethodByName("getIntStaticField", rfk::EMethodFlags::Default, true)->getOuterEntity(), rfk::getArchetype<TestClass>()); //Inherited static method
	
	EXPECT_EQ(SingleTypeTemplateClassTemplate<int>::staticGetArchetype().getMethodByName("testMethod")->getOuterEntity(), rfk::getArchetype<SingleTypeTemplateClassTemplate<int>>());
	EXPECT_NE(SingleTypeTemplateClassTemplate<int>::staticGetArchetype().getMethodByName("testMethod")->getOuterEntity(), rfk::getArchetype<SingleTypeTemplateClassTemplate<double>>());	//Other instantiation field
}

TEST(Rfk_Entity_getOuterEntity, Field_getOuterEntity)
{
	EXPECT_EQ(TestClass::staticGetArchetype().getFieldByName("_intField")->getOuterEntity(), rfk::getArchetype<TestClass>()); //non-static field
	EXPECT_EQ(TestClass::staticGetArchetype().getStaticFieldByName("_intStaticField")->getOuterEntity(), rfk::getArchetype<TestClass>()); //static field
	EXPECT_EQ(TestClass2::staticGetArchetype().getFieldByName("_intField", rfk::EFieldFlags::Default, true)->getOuterEntity(), rfk::getArchetype<TestClass>()); //Inherited non-static field
	EXPECT_EQ(TestClass2::staticGetArchetype().getStaticFieldByName("_intStaticField", rfk::EFieldFlags::Default, true)->getOuterEntity(), rfk::getArchetype<TestClass>()); //Inherited static field

	EXPECT_EQ(SingleTypeTemplateClassTemplate<int>::staticGetArchetype().getFieldByName("testField")->getOuterEntity(), rfk::getArchetype<SingleTypeTemplateClassTemplate<int>>());
	EXPECT_NE(SingleTypeTemplateClassTemplate<int>::staticGetArchetype().getFieldByName("testField")->getOuterEntity(), rfk::getArchetype<SingleTypeTemplateClassTemplate<double>>());	//Other instantiation field
}

TEST(Rfk_Entity_getOuterEntity, Variable_getOuterEntity)
{
	EXPECT_EQ(rfk::getDatabase().getVariableByName("var_global_extern")->getOuterEntity(), nullptr);	//global
	EXPECT_EQ(rfk::getDatabase().getNamespaceByName("test_namespace")->getVariableByName("var_nested_extern")->getOuterEntity(), rfk::getDatabase().getNamespaceByName("test_namespace"));	//nested
}

TEST(Rfk_Entity_getOuterEntity, Function_getOuterEntity)
{
	EXPECT_EQ(rfk::getDatabase().getFunctionByName("func_return_noParam")->getOuterEntity(), nullptr);
	EXPECT_EQ(rfk::getDatabase().getNamespaceByName("test_namespace")->getFunctionByName("func_nested_return_noParam")->getOuterEntity(), rfk::getDatabase().getNamespaceByName("test_namespace"));	//nested
}

TEST(Rfk_Entity_getOuterEntity, Namespace_getOuterEntity)
{
	EXPECT_EQ(rfk::getDatabase().getNamespaceByName("test_namespace")->getOuterEntity(), nullptr);
	EXPECT_EQ(rfk::getDatabase().getNamespaceByName("test_namespace::nested_namespace")->getOuterEntity(), rfk::getDatabase().getNamespaceByName("test_namespace"));
}

TEST(Rfk_Entity_getOuterEntity, Enum_getOuterEntity)
{
	EXPECT_EQ(rfk::getEnum<TestEnum>()->getOuterEntity(), nullptr);			//Enum
	EXPECT_EQ(rfk::getEnum<TestEnumClass>()->getOuterEntity(), nullptr);	//Enum class
	EXPECT_EQ(rfk::getEnum<test_namespace::TestNamespaceNestedEnum>()->getOuterEntity(), rfk::getDatabase().getNamespaceByName("test_namespace"));	//Namespace nested
	EXPECT_EQ(rfk::getEnum<TestClass::NestedEnum>()->getOuterEntity(), rfk::getArchetype<TestClass>());	//Class nested
}

TEST(Rfk_Entity_getOuterEntity, EnumValue_getOuterEntity)
{
	EXPECT_EQ(rfk::getEnum<TestEnum>()->getEnumValueByName("TestEnumValue1")->getOuterEntity(), rfk::getEnum<TestEnum>());		//Enum value
	EXPECT_EQ(rfk::getEnum<TestEnumClass>()->getEnumValueByName("Value3")->getOuterEntity(), rfk::getEnum<TestEnumClass>());	//Enum class value
}

//=========================================================
//================ Entity::getPropertyAt ==================
//=========================================================

TEST(Rfk_Entity_getPropertyAt, Entity_getPropertyAt)
{
	EXPECT_NE(TestClass::staticGetArchetype().getPropertyAt(0), nullptr);
	EXPECT_STREQ(TestClass::staticGetArchetype().getPropertyAt(0)->getArchetype().getName(), "UniqueInheritedProperty");
	EXPECT_NE(TestClass::staticGetArchetype().getPropertyAt(1), nullptr);
	EXPECT_STREQ(TestClass::staticGetArchetype().getPropertyAt(1)->getArchetype().getName(), "MultipleInheritedPropertyChild");
	EXPECT_NE(TestClass::staticGetArchetype().getPropertyAt(2), nullptr);
	EXPECT_STREQ(TestClass::staticGetArchetype().getPropertyAt(2)->getArchetype().getName(), "MultipleInheritedProperty");
}

//=========================================================
//================ Entity::getProperty<> ==================
//=========================================================

TEST(Rfk_Entity_getPropertyTemplate, Entity_getPropertyTemplateWithChildClasses)
{
	EXPECT_NE(TestClass::staticGetArchetype().getProperty<UniqueInheritedProperty>(true), nullptr);
	EXPECT_EQ(TestClass::staticGetArchetype().getProperty<UniqueInheritedProperty>(true)->value, 1);
	EXPECT_NE(TestClass::staticGetArchetype().getProperty<MultipleInheritedProperty>(true), nullptr);	//Catch child
	EXPECT_STREQ(TestClass::staticGetArchetype().getProperty<MultipleInheritedProperty>(true)->getArchetype().getName(), "MultipleInheritedPropertyChild");	//Catch child
	EXPECT_EQ(TestClass::staticGetArchetype().getProperty<MultipleInheritedProperty>(true)->value, 2);	//Catch child
	EXPECT_EQ(TestClass::staticGetArchetype().getProperty<ParseAllNested>(true), nullptr);				//Not found
}

TEST(Rfk_Entity_getPropertyTemplate, Entity_getPropertyTemplateWithoutChildClasses)
{
	EXPECT_NE(TestClass::staticGetArchetype().getProperty<UniqueInheritedProperty>(false), nullptr);
	EXPECT_EQ(TestClass::staticGetArchetype().getProperty<UniqueInheritedProperty>(false)->value, 1);
	EXPECT_NE(TestClass::staticGetArchetype().getProperty<MultipleInheritedProperty>(false), nullptr);	//Ignore child class
	EXPECT_STREQ(TestClass::staticGetArchetype().getProperty<MultipleInheritedProperty>(false)->getArchetype().getName(), "MultipleInheritedProperty");	//Ignore child class
	EXPECT_EQ(TestClass::staticGetArchetype().getProperty<MultipleInheritedProperty>(false)->value, 4);	//Ignore child class
	EXPECT_EQ(TestClass::staticGetArchetype().getProperty<ParseAllNested>(false), nullptr);				//Not found
}

//=========================================================
//================= Entity::getProperty ===================
//=========================================================

TEST(Rfk_Entity_getPropertyNonTemplate, Entity_getPropertyNonTemplateWithChildClasses)
{
	EXPECT_NE(TestClass::staticGetArchetype().getProperty(UniqueInheritedProperty::staticGetArchetype(), true), nullptr);
	EXPECT_EQ(reinterpret_cast<UniqueInheritedProperty const*>(TestClass::staticGetArchetype().getProperty(UniqueInheritedProperty::staticGetArchetype(), true))->value, 1);
	EXPECT_NE(TestClass::staticGetArchetype().getProperty(MultipleInheritedProperty::staticGetArchetype(), true), nullptr);	//Catch child
	EXPECT_STREQ(TestClass::staticGetArchetype().getProperty(MultipleInheritedProperty::staticGetArchetype(), true)->getArchetype().getName(), "MultipleInheritedPropertyChild");	//Catch child
	EXPECT_EQ(reinterpret_cast<MultipleInheritedProperty const*>(TestClass::staticGetArchetype().getProperty(MultipleInheritedProperty::staticGetArchetype(), true))->value, 2);	//Catch child
	EXPECT_EQ(TestClass::staticGetArchetype().getProperty(ParseAllNested::staticGetArchetype(), true), nullptr);				//Not found
}

TEST(Rfk_Entity_getPropertyNonTemplate, Entity_getPropertyNonTemplateWithoutChildClasses)
{
	EXPECT_NE(TestClass::staticGetArchetype().getProperty(UniqueInheritedProperty::staticGetArchetype(), false), nullptr);
	EXPECT_EQ(reinterpret_cast<UniqueInheritedProperty const*>(TestClass::staticGetArchetype().getProperty(UniqueInheritedProperty::staticGetArchetype(), false))->value, 1);
	EXPECT_NE(TestClass::staticGetArchetype().getProperty(MultipleInheritedProperty::staticGetArchetype(), false), nullptr);	//Ignore child class
	EXPECT_STREQ(TestClass::staticGetArchetype().getProperty(MultipleInheritedProperty::staticGetArchetype(), false)->getArchetype().getName(), "MultipleInheritedProperty");	//Ignore child class
	EXPECT_EQ(reinterpret_cast<MultipleInheritedProperty const*>(TestClass::staticGetArchetype().getProperty(MultipleInheritedProperty::staticGetArchetype(), false))->value, 4);	//Ignore child class
	EXPECT_EQ(TestClass::staticGetArchetype().getProperty(ParseAllNested::staticGetArchetype(), false), nullptr);				//Not found
}

//=========================================================
//============== Entity::getPropertyByName ================
//=========================================================

TEST(Rfk_Entity_getPropertyByName, Entity_getPropertyByName)
{
	EXPECT_EQ(TestClass::staticGetArchetype().getPropertyByName("UniqueInheritedPropertyChild"), nullptr);
	EXPECT_NE(TestClass::staticGetArchetype().getPropertyByName("UniqueInheritedProperty"), nullptr);
	EXPECT_EQ(TestClass::staticGetArchetype().getPropertyByName("UniqueInheritedProperty"), TestClass::staticGetArchetype().getPropertyAt(0));
	EXPECT_NE(TestClass::staticGetArchetype().getPropertyByName("MultipleInheritedPropertyChild"), nullptr);
	EXPECT_EQ(TestClass::staticGetArchetype().getPropertyByName("MultipleInheritedPropertyChild"), TestClass::staticGetArchetype().getPropertyAt(1));
	EXPECT_NE(TestClass::staticGetArchetype().getPropertyByName("MultipleInheritedProperty"), nullptr);
	EXPECT_EQ(TestClass::staticGetArchetype().getPropertyByName("MultipleInheritedProperty"), TestClass::staticGetArchetype().getPropertyAt(2));
}

//=========================================================
//============ Entity::getPropertyByPredicate =============
//=========================================================

TEST(Rfk_Entity_getPropertyByPredicate, Entity_getPropertyByPredicateWithoutUserData)
{
	EXPECT_EQ(TestClass::staticGetArchetype().getPropertyByPredicate([](rfk::Property const& prop, void* userData)
			  {
				  return MultipleInheritedProperty::staticGetArchetype().isBaseOf(prop.getArchetype()) &&
					  static_cast<MultipleInheritedProperty const&>(prop).value == 2;
			  }, nullptr),
		TestClass::staticGetArchetype().getPropertyAt(1));
}

TEST(Rfk_Entity_getPropertyByPredicate, Entity_getPropertyByPredicateWithUserData)
{
	int const expectedValue = 4;
	int const* addr = &expectedValue;

	EXPECT_EQ(TestClass::staticGetArchetype().getPropertyByPredicate([](rfk::Property const& prop, void* userData)
			  {


				  return MultipleInheritedProperty::staticGetArchetype().isBaseOf(prop.getArchetype()) &&
					  static_cast<MultipleInheritedProperty const&>(prop).value == **reinterpret_cast<int const**>(userData);
			  }, &addr),
		TestClass::staticGetArchetype().getPropertyAt(2));
}