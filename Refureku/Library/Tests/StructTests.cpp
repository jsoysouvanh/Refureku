#include <stdexcept>	//std::logic_error

#include <gtest/gtest.h>
#include <Refureku/Refureku.h>

#include "TestClass.h"
#include "TestClass2.h"
#include "BaseObject.h"

//=========================================================
//================ Struct::makeInstance ===================
//=========================================================

TEST(Rfk_Struct_makeInstance, NoDefaultConstructible)
{
	EXPECT_EQ(rfk::getDatabase().getClassByName("BaseObject")->makeInstance<BaseObject>(), nullptr);
}

TEST(Rfk_Struct_makeInstance, UseUserProvidedParamInstantiator)
{
	BaseObject* obj = rfk::getDatabase().getClassByName("BaseObject")->makeInstance<BaseObject>(2);

	EXPECT_NE(obj, nullptr);

	delete obj;
}

TEST(Rfk_Struct_makeInstance, UseUserProvidedParamlessInstantiator)
{
	BaseObject* obj = rfk::getDatabase().getClassByName("ObjectDerived1")->makeInstance<BaseObject>();

	EXPECT_NE(obj, nullptr);
	EXPECT_EQ(obj->getI(), 1);

	delete obj;
}

TEST(Rfk_Struct_makeInstance, InstantiateChildClass)
{
	BaseObject* obj = rfk::getDatabase().getClassByName("ObjectDerived2")->makeInstance<BaseObject>();

	EXPECT_EQ(obj->getI(), 2);

	delete obj;
}

//=========================================================
//============= Struct::getDirectSubclasses ===============
//=========================================================

TEST(Rfk_Struct_getDirectSubclasses, NoChildClasses)
{
	EXPECT_EQ(ObjectDerivedDerived::staticGetArchetype().getDirectSubclasses().size(), 0u);
}

TEST(Rfk_Struct_getDirectSubclasses, OneChildClass)
{
	EXPECT_EQ(ObjectDerived2::staticGetArchetype().getDirectSubclasses().size(), 1u);
}

TEST(Rfk_Struct_getDirectSubclasses, MultipleChildClass)
{
	EXPECT_GE(TestClass::staticGetArchetype().getDirectSubclasses().size(), 2u);
}

//=========================================================
//================= Struct::isSubclassOf ==================
//=========================================================

TEST(Rfk_Struct_isSubclassOf, SelfClass)
{
	EXPECT_FALSE(ObjectDerivedDerived::staticGetArchetype().isSubclassOf(ObjectDerivedDerived::staticGetArchetype()));
}

TEST(Rfk_Struct_isSubclassOf, DirectParent)
{
	EXPECT_TRUE(ObjectDerivedDerived::staticGetArchetype().isSubclassOf(ObjectDerived1::staticGetArchetype()));
}

TEST(Rfk_Struct_isSubclassOf, NonDirectParent)
{
	EXPECT_TRUE(ObjectDerivedDerived::staticGetArchetype().isSubclassOf(BaseObject::staticGetArchetype()));
}

TEST(Rfk_Struct_isSubclassOf, NotParent)
{
	EXPECT_FALSE(ObjectDerivedDerived::staticGetArchetype().isSubclassOf(TestClass::staticGetArchetype()));
}

//=========================================================
//=================== Struct::isBaseOf ====================
//=========================================================

TEST(Rfk_Struct_isBaseOf, SelfClass)
{
	EXPECT_TRUE(BaseObject::staticGetArchetype().isBaseOf(BaseObject::staticGetArchetype()));
}

TEST(Rfk_Struct_isBaseOf, DirectChild)
{
	EXPECT_TRUE(BaseObject::staticGetArchetype().isBaseOf(ObjectDerived1::staticGetArchetype()));
	EXPECT_TRUE(BaseObject::staticGetArchetype().isBaseOf(ObjectDerived2::staticGetArchetype()));
}

TEST(Rfk_Struct_isBaseOf, NonDirectChild)
{
	EXPECT_TRUE(BaseObject::staticGetArchetype().isBaseOf(ObjectDerivedDerived::staticGetArchetype()));
}

TEST(Rfk_Struct_isSubclassOf, NonBaseClass)
{
	EXPECT_FALSE(BaseObject::staticGetArchetype().isBaseOf(TestClass::staticGetArchetype()));
}

//=========================================================
//============= Struct::getDirectParentsCount =============
//=========================================================

TEST(Rfk_Struct_getDirectParentsCount, NoDirectParents)
{
	EXPECT_EQ(TestClass::staticGetArchetype().getDirectParentsCount(), 0u);
}

TEST(Rfk_Struct_getDirectParentsCount, OneDirectNonReflectedParent)
{
	EXPECT_EQ(BaseObject::staticGetArchetype().getDirectParentsCount(), 0u);
}

TEST(Rfk_Struct_getDirectParentsCount, OneDirectReflectedParent)
{
	EXPECT_EQ(ObjectDerived1::staticGetArchetype().getDirectParentsCount(), 1u);
}

TEST(Rfk_Struct_getDirectParentsCount, MultipleDirectParents)
{
	EXPECT_GE(MultipleInheritanceClass::staticGetArchetype().getDirectParentsCount(), 2u);
}

//=========================================================
//=============== Struct::getDirectParentAt ===============
//=========================================================

TEST(Rfk_Struct_getDirectParentAt, CheckName)
{
	EXPECT_TRUE(ObjectDerived1::staticGetArchetype().getDirectParentAt(0).getArchetype().hasSameName("BaseObject"));
	EXPECT_TRUE(MultipleInheritanceClass::staticGetArchetype().getDirectParentAt(0).getArchetype().hasSameName("ObjectDerived2"));
	EXPECT_TRUE(MultipleInheritanceClass::staticGetArchetype().getDirectParentAt(1).getArchetype().hasSameName("TestClass"));
}

TEST(Rfk_Struct_getDirectParentAt, CheckInheritanceAccess)
{
	EXPECT_EQ(ObjectDerived1::staticGetArchetype().getDirectParentAt(0).getInheritanceAccessSpecifier(), rfk::EAccessSpecifier::Public);
	//TODO: Add tests for Protected and Private, but probably breaks the generated code
}

//=========================================================
//============== Struct::foreachDirectParent ==============
//=========================================================

TEST(Rfk_Struct_foreachDirectParent, NullptrVisitor)
{
	EXPECT_FALSE(MultipleInheritanceClass::staticGetArchetype().foreachDirectParent(nullptr, nullptr));
}

TEST(Rfk_Struct_foreachDirectParent, CompleteLoop)
{
	int counter = 0;
	auto visitor = [](rfk::ParentStruct const&, void* data)
	{
		int& counter = *reinterpret_cast<int*>(data);
		counter++;

		return true;
	};

	EXPECT_TRUE(MultipleInheritanceClass::staticGetArchetype().foreachDirectParent(visitor, &counter));

	EXPECT_EQ(counter, MultipleInheritanceClass::staticGetArchetype().getDirectParentsCount());
}

TEST(Rfk_Struct_foreachDirectParent, BreakingLoop)
{
	int counter = 0;
	auto visitor = [](rfk::ParentStruct const&, void* data)
	{
		int& counter = *reinterpret_cast<int*>(data);
		counter++;

		return false;
	};

	EXPECT_FALSE(MultipleInheritanceClass::staticGetArchetype().foreachDirectParent(visitor, &counter));

	EXPECT_EQ(counter, 1u);
}

TEST(Rfk_Struct_foreachDirectParent, ThrowingVisitor)
{
	auto visitor = [](rfk::ParentStruct const&, void*) -> bool
	{
		throw std::logic_error("Error");
	};

	EXPECT_THROW(MultipleInheritanceClass::staticGetArchetype().foreachDirectParent(visitor, nullptr), std::logic_error);
}

//=========================================================
//============= Struct::getNestedStructByName =============
//=========================================================

TEST(Rfk_Struct_getNestedStructByName, ClassInsteadOfStruct)
{
	EXPECT_EQ(TestClass::staticGetArchetype().getNestedStructByName("NestedClass"), nullptr);
}

TEST(Rfk_Struct_getNestedStructByName, ValidNameValidAccess)
{
	EXPECT_NE(TestClass::staticGetArchetype().getNestedStructByName("NestedStruct"), nullptr);
	EXPECT_NE(TestClass::staticGetArchetype().getNestedStructByName("NestedStruct", rfk::EAccessSpecifier::Private), nullptr);
}

TEST(Rfk_Struct_getNestedStructByName, UnvalidNameValidAccess)
{
	EXPECT_EQ(TestClass::staticGetArchetype().getNestedStructByName("NonExistantStruct", rfk::EAccessSpecifier::Private), nullptr);
}

TEST(Rfk_Struct_getNestedStructByName, ValidNameUnvalidAccess)
{
	EXPECT_EQ(TestClass::staticGetArchetype().getNestedStructByName("NestedStruct", rfk::EAccessSpecifier::Protected), nullptr);
	EXPECT_EQ(TestClass::staticGetArchetype().getNestedStructByName("NestedStruct", rfk::EAccessSpecifier::Public), nullptr);
}