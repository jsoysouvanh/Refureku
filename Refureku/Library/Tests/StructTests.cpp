#include <stdexcept>	//std::logic_error

#include <gtest/gtest.h>
#include <Refureku/Refureku.h>

#include "TestClass.h"
#include "TestClass2.h"
#include "BaseObject.h"
#include "TypeTemplateClassTemplate.h"

//=========================================================
//============= Struct::makeSharedInstance ================
//=========================================================

TEST(Rfk_Struct_makeSharedInstance, NoDefaultConstructible)
{
	EXPECT_EQ(rfk::getDatabase().getFileLevelClassByName("BaseObject")->makeSharedInstance<BaseObject>(), nullptr);
}

TEST(Rfk_Struct_makeSharedInstance, UseUserProvidedParamInstantiator)
{
	std::shared_ptr<BaseObject> obj = rfk::getDatabase().getFileLevelClassByName("BaseObject")->makeSharedInstance<BaseObject>(2);

	EXPECT_NE(obj, nullptr);
}

TEST(Rfk_Struct_makeSharedInstance, UseMissingInstantiator)
{
	std::shared_ptr<BaseObject> obj = rfk::getDatabase().getFileLevelClassByName("BaseObject")->makeSharedInstance<BaseObject>(3.14f);

	EXPECT_FALSE(obj);
}

TEST(Rfk_Struct_makeSharedInstance, UseThrowingInstantiator)
{
	EXPECT_THROW(std::shared_ptr<BaseObject> obj = rfk::getDatabase().getFileLevelClassByName("BaseObject")->makeSharedInstance<BaseObject>(1, 2), std::logic_error);
}

TEST(Rfk_Struct_makeSharedInstance, UseUserProvidedParamlessInstantiator)
{
	std::shared_ptr<BaseObject> obj = rfk::getDatabase().getFileLevelClassByName("ObjectDerived1")->makeSharedInstance<BaseObject>();

	EXPECT_NE(obj, nullptr);
	EXPECT_EQ(obj->getI(), 1);
}

TEST(Rfk_Struct_makeSharedInstance, UseDefaultInstantiator)
{
	std::shared_ptr<BaseObject> obj = rfk::getDatabase().getFileLevelClassByName("ObjectDerived2")->makeSharedInstance<BaseObject>();

	EXPECT_EQ(obj->getI(), 2);
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

//=========================================================
//========== Struct::getNestedStructByPredicate ===========
//=========================================================

TEST(Rfk_Struct_getNestedStructByPredicate, NullptrPredicate)
{
	EXPECT_EQ(TestClass::staticGetArchetype().getNestedStructByPredicate(nullptr, nullptr), nullptr);
}

TEST(Rfk_Struct_getNestedStructByPredicate, FindingPredicate)
{
	char const* name = "NestedStruct";
	auto predicate = [](rfk::Struct const& struct_, void* data)
	{
		return struct_.hasSameName(*reinterpret_cast<char const**>(data));
	};

	EXPECT_NE(TestClass::staticGetArchetype().getNestedStructByPredicate(predicate, &name), nullptr);
}

TEST(Rfk_Struct_getNestedStructByPredicate, NotFindingPredicate)
{
	char const* name = "InexistantStruct";
	auto predicate = [](rfk::Struct const& struct_, void* data)
	{
		return struct_.hasSameName(*reinterpret_cast<char**>(data));
	};

	EXPECT_EQ(TestClass::staticGetArchetype().getNestedStructByPredicate(predicate, &name), nullptr);
}

TEST(Rfk_Struct_getNestedStructByPredicate, ThrowingPredicate)
{
	auto predicate = [](rfk::Struct const&, void*) -> bool
	{
		throw std::logic_error("Something wrong happened!");
	};

	EXPECT_THROW(TestClass::staticGetArchetype().getNestedStructByPredicate(predicate, nullptr), std::logic_error);
}

//=========================================================
//========== Struct::getNestedStructsByPredicate ==========
//=========================================================

TEST(Rfk_Struct_getNestedStructsByPredicate, NullptrPredicate)
{
	EXPECT_EQ(TestClass::staticGetArchetype().getNestedStructsByPredicate(nullptr, nullptr).size(), 0u);
}

TEST(Rfk_Struct_getNestedStructsByPredicate, FindingPredicate)
{
	char const* name = "NestedStruct";
	auto predicate = [](rfk::Struct const& struct_, void*)
	{
		return struct_.getProperty<UniqueInheritedProperty>() != nullptr;
	};

	EXPECT_EQ(TestClass::staticGetArchetype().getNestedStructsByPredicate(predicate, &name).size(), 1u);
}

TEST(Rfk_Struct_getNestedStructsByPredicate, NotFindingPredicate)
{
	char const* name = "InexistantStruct";
	auto predicate = [](rfk::Struct const& struct_, void* data)
	{
		return struct_.hasSameName(*reinterpret_cast<char**>(data));
	};

	EXPECT_EQ(TestClass::staticGetArchetype().getNestedStructsByPredicate(predicate, &name).size(), 0u);
}

TEST(Rfk_Struct_getNestedStructsByPredicate, ThrowingPredicate)
{
	auto predicate = [](rfk::Struct const&, void*) -> bool
	{
		throw std::logic_error("Something wrong happened!");
	};

	EXPECT_THROW(TestClass::staticGetArchetype().getNestedStructsByPredicate(predicate, nullptr), std::logic_error);
}

//=========================================================
//============= Struct::getNestedClassByName ==============
//=========================================================

TEST(Rfk_Struct_getNestedClassByName, StructInsteadOfClass)
{
	EXPECT_EQ(TestClass::staticGetArchetype().getNestedClassByName("NestedStruct"), nullptr);
}

TEST(Rfk_Struct_getNestedClassByName, ValidNameValidAccess)
{
	EXPECT_NE(TestClass::staticGetArchetype().getNestedClassByName("NestedClass"), nullptr);
	EXPECT_NE(TestClass::staticGetArchetype().getNestedClassByName("NestedClass", rfk::EAccessSpecifier::Protected), nullptr);
}

TEST(Rfk_Struct_getNestedClassByName, UnvalidNameValidAccess)
{
	EXPECT_EQ(TestClass::staticGetArchetype().getNestedClassByName("NonExistantClass", rfk::EAccessSpecifier::Protected), nullptr);
}

TEST(Rfk_Struct_getNestedClassByName, ValidNameUnvalidAccess)
{
	EXPECT_EQ(TestClass::staticGetArchetype().getNestedClassByName("NestedClass", rfk::EAccessSpecifier::Private), nullptr);
	EXPECT_EQ(TestClass::staticGetArchetype().getNestedClassByName("NestedClass", rfk::EAccessSpecifier::Public), nullptr);
}

//=========================================================
//========== Struct::getNestedClassByPredicate ============
//=========================================================

TEST(Rfk_Struct_getNestedClassByPredicate, NullptrPredicate)
{
	EXPECT_EQ(TestClass::staticGetArchetype().getNestedClassByPredicate(nullptr, nullptr), nullptr);
}

TEST(Rfk_Struct_getNestedClassByPredicate, FindingPredicate)
{
	char const* name = "NestedClass";
	auto predicate = [](rfk::Class const& class_, void* data)
	{
		return class_.hasSameName(*reinterpret_cast<char const**>(data));
	};

	EXPECT_NE(TestClass::staticGetArchetype().getNestedClassByPredicate(predicate, &name), nullptr);
}

TEST(Rfk_Struct_getNestedClassByPredicate, NotFindingPredicate)
{
	char const* name = "InexistantClass";
	auto predicate = [](rfk::Class const& class_, void* data)
	{
		return class_.hasSameName(*reinterpret_cast<char**>(data));
	};

	EXPECT_EQ(TestClass::staticGetArchetype().getNestedClassByPredicate(predicate, &name), nullptr);
}

TEST(Rfk_Struct_getNestedClassByPredicate, ThrowingPredicate)
{
	auto predicate = [](rfk::Class const&, void*) -> bool
	{
		throw std::logic_error("Something wrong happened!");
	};

	EXPECT_THROW(TestClass::staticGetArchetype().getNestedClassByPredicate(predicate, nullptr), std::logic_error);
}

//=========================================================
//========== Struct::getNestedClassesByPredicate ==========
//=========================================================

TEST(Rfk_Struct_getNestedClassesByPredicate, NullptrPredicate)
{
	EXPECT_EQ(TestClass::staticGetArchetype().getNestedClassesByPredicate(nullptr, nullptr).size(), 0u);
}

TEST(Rfk_Struct_getNestedClassesByPredicate, FindingPredicate)
{
	char const* name = "NestedClass";
	auto predicate = [](rfk::Class const& class_, void*)
	{
		return class_.getProperty<UniqueInheritedProperty>() != nullptr;
	};

	EXPECT_EQ(TestClass::staticGetArchetype().getNestedClassesByPredicate(predicate, &name).size(), 1u);
}

TEST(Rfk_Struct_getNestedClassesByPredicate, NotFindingPredicate)
{
	char const* name = "InexistantClass";
	auto predicate = [](rfk::Class const& class_, void* data)
	{
		return class_.hasSameName(*reinterpret_cast<char**>(data));
	};

	EXPECT_EQ(TestClass::staticGetArchetype().getNestedClassesByPredicate(predicate, &name).size(), 0u);
}

TEST(Rfk_Struct_getNestedClassesByPredicate, ThrowingPredicate)
{
	auto predicate = [](rfk::Class const&, void*) -> bool
	{
		throw std::logic_error("Something wrong happened!");
	};

	EXPECT_THROW(TestClass::staticGetArchetype().getNestedClassesByPredicate(predicate, nullptr), std::logic_error);
}

//=========================================================
//============= Struct::getNestedEnumByName =============
//=========================================================

TEST(Rfk_Struct_getNestedEnumByName, StructInsteadOfEnum)
{
	EXPECT_EQ(TestClass::staticGetArchetype().getNestedEnumByName("NestedStruct"), nullptr);
}

TEST(Rfk_Struct_getNestedEnumByName, ValidNameValidAccess)
{
	EXPECT_NE(TestClass::staticGetArchetype().getNestedEnumByName("NestedEnum"), nullptr);
	EXPECT_NE(TestClass::staticGetArchetype().getNestedEnumByName("NestedEnum", rfk::EAccessSpecifier::Public), nullptr);
}

TEST(Rfk_Struct_getNestedEnumByName, UnvalidNameValidAccess)
{
	EXPECT_EQ(TestClass::staticGetArchetype().getNestedEnumByName("NonExistantEnum", rfk::EAccessSpecifier::Public), nullptr);
}

TEST(Rfk_Struct_getNestedEnumByName, ValidNameUnvalidAccess)
{
	EXPECT_EQ(TestClass::staticGetArchetype().getNestedEnumByName("NestedEnum", rfk::EAccessSpecifier::Private), nullptr);
	EXPECT_EQ(TestClass::staticGetArchetype().getNestedEnumByName("NestedEnum", rfk::EAccessSpecifier::Protected), nullptr);
}

//=========================================================
//========== Struct::getNestedStructByPredicate ===========
//=========================================================

TEST(Rfk_Struct_getNestedEnumByPredicate, NullptrPredicate)
{
	EXPECT_EQ(TestClass::staticGetArchetype().getNestedEnumByPredicate(nullptr, nullptr), nullptr);
}

TEST(Rfk_Struct_getNestedEnumByPredicate, FindingPredicate)
{
	char const* name = "NestedEnum";
	auto predicate = [](rfk::Enum const& class_, void* data)
	{
		return class_.hasSameName(*reinterpret_cast<char const**>(data));
	};

	EXPECT_NE(TestClass::staticGetArchetype().getNestedEnumByPredicate(predicate, &name), nullptr);
}

TEST(Rfk_Struct_getNestedEnumByPredicate, NotFindingPredicate)
{
	char const* name = "InexistantEnum";
	auto predicate = [](rfk::Enum const& class_, void* data)
	{
		return class_.hasSameName(*reinterpret_cast<char**>(data));
	};

	EXPECT_EQ(TestClass::staticGetArchetype().getNestedEnumByPredicate(predicate, &name), nullptr);
}

TEST(Rfk_Struct_getNestedEnumByPredicate, ThrowingPredicate)
{
	auto predicate = [](rfk::Enum const&, void*) -> bool
	{
		throw std::logic_error("Something wrong happened!");
	};

	EXPECT_THROW(TestClass::staticGetArchetype().getNestedEnumByPredicate(predicate, nullptr), std::logic_error);
}

//=========================================================
//========== Struct::getNestedStructsByPredicate ==========
//=========================================================

TEST(Rfk_Struct_getNestedEnumsByPredicate, NullptrPredicate)
{
	EXPECT_EQ(TestClass::staticGetArchetype().getNestedEnumsByPredicate(nullptr, nullptr).size(), 0u);
}

TEST(Rfk_Struct_getNestedEnumsByPredicate, FindingPredicate)
{
	char const* name = "NestedEnum";
	auto predicate = [](rfk::Enum const& class_, void*)
	{
		return class_.getProperty<UniqueInheritedProperty>() != nullptr;
	};

	EXPECT_EQ(TestClass::staticGetArchetype().getNestedEnumsByPredicate(predicate, &name).size(), 1u);
}

TEST(Rfk_Struct_getNestedEnumsByPredicate, NotFindingPredicate)
{
	char const* name = "InexistantEnum";
	auto predicate = [](rfk::Enum const& class_, void* data)
	{
		return class_.hasSameName(*reinterpret_cast<char**>(data));
	};

	EXPECT_EQ(TestClass::staticGetArchetype().getNestedEnumsByPredicate(predicate, &name).size(), 0u);
}

TEST(Rfk_Struct_getNestedEnumsByPredicate, ThrowingPredicate)
{
	auto predicate = [](rfk::Enum const&, void*) -> bool
	{
		throw std::logic_error("Something wrong happened!");
	};

	EXPECT_THROW(TestClass::staticGetArchetype().getNestedEnumsByPredicate(predicate, nullptr), std::logic_error);
}

//=========================================================
//=============== Struct::foreachArchetype ================
//=========================================================

TEST(Rfk_Struct_foreachNestedArchetype, NullptrVisitor)
{
	EXPECT_FALSE(TestClass::staticGetArchetype().foreachNestedArchetype(nullptr, nullptr));
}

TEST(Rfk_Struct_foreachNestedArchetype, CompleteLoop)
{
	int counter = 0;
	auto visitor = [](rfk::Archetype const&, void* data)
	{
		int& counter = *reinterpret_cast<int*>(data);
		counter++;

		return true;
	};

	EXPECT_TRUE(TestClass::staticGetArchetype().foreachNestedArchetype(visitor, &counter));

	EXPECT_EQ(counter, TestClass::staticGetArchetype().getNestedArchetypesCount());
}

TEST(Rfk_Struct_foreachNestedArchetype, BreakingLoop)
{
	int counter = 0;
	auto visitor = [](rfk::Archetype const&, void* data)
	{
		int& counter = *reinterpret_cast<int*>(data);
		counter++;

		return false;
	};

	EXPECT_FALSE(TestClass::staticGetArchetype().foreachNestedArchetype(visitor, &counter));

	EXPECT_EQ(counter, 1u);
}

TEST(Rfk_Struct_foreachNestedArchetype, ThrowingVisitor)
{
	auto visitor = [](rfk::Archetype const&, void*) -> bool
	{
		throw std::logic_error("Error");
	};

	EXPECT_THROW(TestClass::staticGetArchetype().foreachNestedArchetype(visitor, nullptr), std::logic_error);
}

//=========================================================
//=========== Struct::getNestedArchetypesCount ============
//=========================================================

TEST(Rfk_Struct_getNestedArchetypesCount, NoNestedArchetype)
{
	EXPECT_EQ(MultipleInheritanceClass::staticGetArchetype().getNestedArchetypesCount(), 0u);
}

TEST(Rfk_Struct_getNestedArchetypesCount, SeveralNestedArchetypes)
{
	EXPECT_EQ(TestClass::staticGetArchetype().getNestedArchetypesCount(), 6u);
}

//=========================================================
//================ Struct::getFieldByName =================
//=========================================================

TEST(Rfk_Struct_getFieldByName, ValidNameValidFlags)
{
	EXPECT_NE(TestClass::staticGetArchetype().getFieldByName("_intField"), nullptr);
	EXPECT_NE(TestClass::staticGetArchetype().getFieldByName("_intField", rfk::EFieldFlags::Private), nullptr);
}

TEST(Rfk_Struct_getFieldByName, ValidNameInvalidFlags)
{
	EXPECT_EQ(TestClass::staticGetArchetype().getFieldByName("_intField", rfk::EFieldFlags::Public), nullptr);
	EXPECT_EQ(TestClass::staticGetArchetype().getFieldByName("_intField", rfk::EFieldFlags::Public | rfk::EFieldFlags::Private), nullptr);
}

TEST(Rfk_Struct_getFieldByName, InvalidNameValidFlags)
{
	EXPECT_EQ(TestClass::staticGetArchetype().getFieldByName("i", rfk::EFieldFlags::Private), nullptr);
}

TEST(Rfk_Struct_getFieldByName, ValidNameValidFlagsWithoutInherited)
{
	EXPECT_EQ(TestClass2::staticGetArchetype().getFieldByName("_intField", rfk::EFieldFlags::Default, false), nullptr);
	EXPECT_EQ(TestClass2::staticGetArchetype().getFieldByName("_intField", rfk::EFieldFlags::Private, false), nullptr);
}

TEST(Rfk_Struct_getFieldByName, ValidNameValidFlagsWithInherited)
{
	EXPECT_NE(TestClass2::staticGetArchetype().getFieldByName("_intField", rfk::EFieldFlags::Default, true), nullptr);
	EXPECT_NE(TestClass2::staticGetArchetype().getFieldByName("_intField", rfk::EFieldFlags::Private, true), nullptr);
}

//=========================================================
//============= Struct::getFieldByPredicate ===============
//=========================================================

TEST(Rfk_Struct_getFieldByPredicate, NullptrPredicate)
{
	EXPECT_EQ(TestClass::staticGetArchetype().getFieldByPredicate(nullptr, nullptr), nullptr);
}

TEST(Rfk_Struct_getFieldByPredicate, ThrowingPredicate)
{
	auto predicate = [](rfk::Field const&, void*) -> bool
	{
		throw std::logic_error("Error");
	};

	EXPECT_THROW(TestClass::staticGetArchetype().getFieldByPredicate(predicate, nullptr), std::logic_error);
}

TEST(Rfk_Struct_getFieldByPredicate, FindingPredicate)
{
	char const* name = "_intField";
	auto predicate = [](rfk::Field const& field, void* data) -> bool
	{
		return field.hasSameName(*reinterpret_cast<char const**>(data));
	};

	EXPECT_NE(TestClass::staticGetArchetype().getFieldByPredicate(predicate, &name), nullptr);
}

TEST(Rfk_Struct_getFieldByPredicate, NonFindingPredicate)
{
	char const* name = "inexistantField";
	auto predicate = [](rfk::Field const& field, void* data) -> bool
	{
		return field.hasSameName(*reinterpret_cast<char const**>(data));
	};

	EXPECT_EQ(TestClass::staticGetArchetype().getFieldByPredicate(predicate, &name), nullptr);
}

//=========================================================
//============= Struct::getFieldsByPredicate ==============
//=========================================================

TEST(Rfk_Struct_getFieldsByPredicate, NullptrPredicate)
{
	EXPECT_EQ(TestClass::staticGetArchetype().getFieldsByPredicate(nullptr, nullptr).size(), 0u);
}

TEST(Rfk_Struct_getFieldsByPredicate, ThrowingPredicate)
{
	auto predicate = [](rfk::Field const&, void*) -> bool
	{
		throw std::logic_error("Error");
	};

	EXPECT_THROW(TestClass::staticGetArchetype().getFieldsByPredicate(predicate, nullptr), std::logic_error);
}

TEST(Rfk_Struct_getFieldsByPredicate, FindingPredicate)
{
	char const* name = "_intField";
	auto predicate = [](rfk::Field const& field, void* data) -> bool
	{
		return field.hasSameName(*reinterpret_cast<char const**>(data));
	};

	EXPECT_EQ(TestClass::staticGetArchetype().getFieldsByPredicate(predicate, &name).size(), 1u);
}

TEST(Rfk_Struct_getFieldsByPredicate, NonFindingPredicate)
{
	char const* name = "inexistantField";
	auto predicate = [](rfk::Field const& field, void* data) -> bool
	{
		return field.hasSameName(*reinterpret_cast<char const**>(data));
	};

	EXPECT_EQ(TestClass::staticGetArchetype().getFieldsByPredicate(predicate, &name).size(), 0u);
}

//=========================================================
//================= Struct::foreachField ==================
//=========================================================

TEST(Rfk_Struct_foreachField, NullptrVisitor)
{
	EXPECT_FALSE(TestClass::staticGetArchetype().foreachField(nullptr, nullptr));
}

TEST(Rfk_Struct_foreachField, CompleteLoop)
{
	int counter = 0;
	auto visitor = [](rfk::Field const&, void* data)
	{
		int& counter = *reinterpret_cast<int*>(data);
		counter++;

		return true;
	};

	EXPECT_TRUE(TestClass::staticGetArchetype().foreachField(visitor, &counter));

	EXPECT_EQ(counter, TestClass::staticGetArchetype().getFieldsCount());
}

TEST(Rfk_Struct_foreachField, BreakingLoop)
{
	int counter = 0;
	auto visitor = [](rfk::Field const&, void* data)
	{
		int& counter = *reinterpret_cast<int*>(data);
		counter++;

		return false;
	};

	EXPECT_FALSE(TestClass::staticGetArchetype().foreachField(visitor, &counter));

	EXPECT_EQ(counter, 1u);
}

TEST(Rfk_Struct_foreachField, ThrowingVisitor)
{
	auto visitor = [](rfk::Field const&, void*) -> bool
	{
		throw std::logic_error("Error");
	};

	EXPECT_THROW(TestClass::staticGetArchetype().foreachField(visitor, nullptr), std::logic_error);
}

//=========================================================
//================ Struct::getFieldsCount =================
//=========================================================

TEST(Rfk_Struct_getFieldsCount, NoFields)
{
	EXPECT_EQ(rfk::getDatabase().getNamespaceByName("test_namespace")->getStructByName("TestNamespaceNestedStruct")->getFieldsCount(), 0u);
}

TEST(Rfk_Struct_getFieldsCount, SeveralFields)
{
	EXPECT_EQ(TestClass::staticGetArchetype().getFieldsCount(), 2u);
}

TEST(Rfk_Struct_getFieldsCount, SeveralFieldsIncludingInherited)
{
	EXPECT_EQ(ObjectDerived1::staticGetArchetype().getFieldsCount(), 2u);	//1 + 1 inherited
}

//=========================================================
//============= Struct::getStaticFieldByName ==============
//=========================================================

TEST(Rfk_Struct_getStaticFieldByName, ValidNameValidFlags)
{
	EXPECT_NE(TestClass::staticGetArchetype().getStaticFieldByName("_intStaticField"), nullptr);
	EXPECT_NE(TestClass::staticGetArchetype().getStaticFieldByName("_intStaticField", rfk::EFieldFlags::Private), nullptr);
}

TEST(Rfk_Struct_getStaticFieldByName, ValidNameInvalidFlags)
{
	EXPECT_EQ(TestClass::staticGetArchetype().getStaticFieldByName("_intStaticField", rfk::EFieldFlags::Public), nullptr);
	EXPECT_EQ(TestClass::staticGetArchetype().getStaticFieldByName("_intStaticField", rfk::EFieldFlags::Public | rfk::EFieldFlags::Private), nullptr);
}

TEST(Rfk_Struct_getStaticFieldByName, InvalidNameValidFlags)
{
	EXPECT_EQ(TestClass::staticGetArchetype().getStaticFieldByName("i", rfk::EFieldFlags::Private), nullptr);
}

TEST(Rfk_Struct_getStaticFieldByName, ValidNameValidFlagsWithoutInherited)
{
	EXPECT_EQ(TestClass2::staticGetArchetype().getStaticFieldByName("_intStaticField", rfk::EFieldFlags::Default, false), nullptr);
	EXPECT_EQ(TestClass2::staticGetArchetype().getStaticFieldByName("_intStaticField", rfk::EFieldFlags::Private, false), nullptr);
}

TEST(Rfk_Struct_getStaticFieldByName, ValidNameValidFlagsWithInherited)
{
	EXPECT_NE(TestClass2::staticGetArchetype().getStaticFieldByName("_intStaticField", rfk::EFieldFlags::Default, true), nullptr);
	EXPECT_NE(TestClass2::staticGetArchetype().getStaticFieldByName("_intStaticField", rfk::EFieldFlags::Private, true), nullptr);
}

//=========================================================
//========== Struct::getStaticFieldByPredicate ============
//=========================================================

TEST(Rfk_Struct_getStaticFieldByPredicate, NullptrPredicate)
{
	EXPECT_EQ(TestClass::staticGetArchetype().getStaticFieldByPredicate(nullptr, nullptr), nullptr);
}

TEST(Rfk_Struct_getStaticFieldByPredicate, ThrowingPredicate)
{
	auto predicate = [](rfk::StaticField const&, void*) -> bool
	{
		throw std::logic_error("Error");
	};

	EXPECT_THROW(TestClass::staticGetArchetype().getStaticFieldByPredicate(predicate, nullptr), std::logic_error);
}

TEST(Rfk_Struct_getStaticFieldByPredicate, FindingPredicate)
{
	char const* name = "_intStaticField";
	auto predicate = [](rfk::StaticField const& field, void* data) -> bool
	{
		return field.hasSameName(*reinterpret_cast<char const**>(data));
	};

	EXPECT_NE(TestClass::staticGetArchetype().getStaticFieldByPredicate(predicate, &name), nullptr);
}

TEST(Rfk_Struct_getStaticFieldByPredicate, NonFindingPredicate)
{
	char const* name = "inexistantStaticField";
	auto predicate = [](rfk::StaticField const& field, void* data) -> bool
	{
		return field.hasSameName(*reinterpret_cast<char const**>(data));
	};

	EXPECT_EQ(TestClass::staticGetArchetype().getStaticFieldByPredicate(predicate, &name), nullptr);
}

//=========================================================
//========== Struct::getStaticFieldsByPredicate ===========
//=========================================================

TEST(Rfk_Struct_getStaticFieldsByPredicate, NullptrPredicate)
{
	EXPECT_EQ(TestClass::staticGetArchetype().getStaticFieldsByPredicate(nullptr, nullptr).size(), 0u);
}

TEST(Rfk_Struct_getStaticFieldsByPredicate, ThrowingPredicate)
{
	auto predicate = [](rfk::StaticField const&, void*) -> bool
	{
		throw std::logic_error("Error");
	};

	EXPECT_THROW(TestClass::staticGetArchetype().getStaticFieldsByPredicate(predicate, nullptr), std::logic_error);
}

TEST(Rfk_Struct_getStaticFieldsByPredicate, FindingPredicate)
{
	char const* name = "_intStaticField";
	auto predicate = [](rfk::StaticField const& field, void* data) -> bool
	{
		return field.hasSameName(*reinterpret_cast<char const**>(data));
	};

	EXPECT_EQ(TestClass::staticGetArchetype().getStaticFieldsByPredicate(predicate, &name).size(), 1u);
}

TEST(Rfk_Struct_getStaticFieldsByPredicate, NonFindingPredicate)
{
	char const* name = "inexistantStaticField";
	auto predicate = [](rfk::StaticField const& field, void* data) -> bool
	{
		return field.hasSameName(*reinterpret_cast<char const**>(data));
	};

	EXPECT_EQ(TestClass::staticGetArchetype().getStaticFieldsByPredicate(predicate, &name).size(), 0u);
}

//=========================================================
//============== Struct::foreachStaticField ===============
//=========================================================

TEST(Rfk_Struct_foreachStaticField, NullptrVisitor)
{
	EXPECT_FALSE(TestClass::staticGetArchetype().foreachStaticField(nullptr, nullptr));
}

TEST(Rfk_Struct_foreachStaticField, CompleteLoop)
{
	int counter = 0;
	auto visitor = [](rfk::StaticField const&, void* data)
	{
		int& counter = *reinterpret_cast<int*>(data);
		counter++;

		return true;
	};

	EXPECT_TRUE(TestClass::staticGetArchetype().foreachStaticField(visitor, &counter));

	EXPECT_EQ(counter, TestClass::staticGetArchetype().getStaticFieldsCount());
}

TEST(Rfk_Struct_foreachStaticField, BreakingLoop)
{
	int counter = 0;
	auto visitor = [](rfk::StaticField const&, void* data)
	{
		int& counter = *reinterpret_cast<int*>(data);
		counter++;

		return false;
	};

	EXPECT_FALSE(TestClass::staticGetArchetype().foreachStaticField(visitor, &counter));

	EXPECT_EQ(counter, 1u);
}

TEST(Rfk_Struct_foreachStaticField, ThrowingVisitor)
{
	auto visitor = [](rfk::StaticField const&, void*) -> bool
	{
		throw std::logic_error("Error");
	};

	EXPECT_THROW(TestClass::staticGetArchetype().foreachStaticField(visitor, nullptr), std::logic_error);
}

//=========================================================
//============= Struct::getStaticFieldsCount ==============
//=========================================================

TEST(Rfk_Struct_getStaticFieldsCount, NoStaticFields)
{
	EXPECT_EQ(rfk::getDatabase().getNamespaceByName("test_namespace")->getStructByName("TestNamespaceNestedStruct")->getStaticFieldsCount(), 0u);
}

TEST(Rfk_Struct_getStaticFieldsCount, SeveralStaticFields)
{
	EXPECT_EQ(TestClass::staticGetArchetype().getStaticFieldsCount(), 2u);
}

TEST(Rfk_Struct_getStaticFieldsCount, SeveralStaticFieldsWithIncludingInherited)
{
	EXPECT_EQ(TestClass2::staticGetArchetype().getStaticFieldsCount(), 2u);	//0 + 2 inherited
}

//=========================================================
//================ Struct::getMethodByName ================
//=========================================================

TEST(Rfk_Struct_getMethodByName, ValidNameValidFlags)
{
	EXPECT_NE(TestClass::staticGetArchetype().getMethodByName("getIntField"), nullptr);
	EXPECT_NE(TestClass::staticGetArchetype().getMethodByName("getIntField", rfk::EMethodFlags::Public), nullptr);
}

TEST(Rfk_Struct_getMethodByName, ValidNameInvalidFlags)
{
	EXPECT_EQ(TestClass::staticGetArchetype().getMethodByName("getIntField", rfk::EMethodFlags::Private), nullptr);
	EXPECT_EQ(TestClass::staticGetArchetype().getMethodByName("getIntField", rfk::EMethodFlags::Public | rfk::EMethodFlags::Private), nullptr);
}

TEST(Rfk_Struct_getMethodByName, InvalidNameValidFlags)
{
	EXPECT_EQ(TestClass::staticGetArchetype().getMethodByName("GetIntField", rfk::EMethodFlags::Public), nullptr);
}

TEST(Rfk_Struct_getMethodByName, ValidNameValidFlagsWithoutInherited)
{
	EXPECT_EQ(TestClass2::staticGetArchetype().getMethodByName("getIntField", rfk::EMethodFlags::Default, false), nullptr);
	EXPECT_EQ(TestClass2::staticGetArchetype().getMethodByName("getIntField", rfk::EMethodFlags::Public, false), nullptr);
}

TEST(Rfk_Struct_getMethodByName, ValidNameValidFlagsWithInherited)
{
	EXPECT_NE(TestClass2::staticGetArchetype().getMethodByName("getIntField", rfk::EMethodFlags::Default, true), nullptr);
	EXPECT_NE(TestClass2::staticGetArchetype().getMethodByName("getIntField", rfk::EMethodFlags::Public, true), nullptr);
}

//=========================================================
//================ Struct::getMethodsByName ===============
//=========================================================

TEST(Rfk_Struct_getMethodsByName, ValidNameValidFlags)
{
	EXPECT_EQ(TestClass::staticGetArchetype().getMethodsByName("getIntField").size(), 2u);
}

TEST(Rfk_Struct_getMethodsByName, ValidNameInvalidFlags)
{
	EXPECT_EQ(TestClass::staticGetArchetype().getMethodsByName("getIntField", rfk::EMethodFlags::Private).size(), 0u);
	EXPECT_EQ(TestClass::staticGetArchetype().getMethodsByName("getIntField", rfk::EMethodFlags::Public | rfk::EMethodFlags::Private).size(), 0u);
}

TEST(Rfk_Struct_getMethodsByName, InvalidNameValidFlags)
{
	EXPECT_EQ(TestClass::staticGetArchetype().getMethodsByName("GetIntField", rfk::EMethodFlags::Public).size(), 0u);
}

TEST(Rfk_Struct_getMethodsByName, ValidNameValidFlagsWithoutInherited)
{
	EXPECT_EQ(TestClass2::staticGetArchetype().getMethodsByName("getIntField", rfk::EMethodFlags::Default, false).size(), 0u);
	EXPECT_EQ(TestClass2::staticGetArchetype().getMethodsByName("getIntField", rfk::EMethodFlags::Public, false).size(), 0u);
}

TEST(Rfk_Struct_getMethodsByName, ValidNameValidFlagsWithInherited)
{
	EXPECT_EQ(TestClass2::staticGetArchetype().getMethodsByName("getIntField", rfk::EMethodFlags::Default, true).size(), 2u);
	EXPECT_EQ(TestClass2::staticGetArchetype().getMethodsByName("getIntField", rfk::EMethodFlags::Public, true).size(), 2u);
}

//=========================================================
//============= Struct::getMethodByPredicate ==============
//=========================================================

TEST(Rfk_Struct_getMethodByPredicate, NullptrPredicate)
{
	EXPECT_EQ(TestClass::staticGetArchetype().getMethodByPredicate(nullptr, nullptr), nullptr);
}

TEST(Rfk_Struct_getMethodByPredicate, ThrowingPredicate)
{
	auto predicate = [](rfk::Method const&, void*) -> bool
	{
		throw std::logic_error("Error");
	};

	EXPECT_THROW(TestClass::staticGetArchetype().getMethodByPredicate(predicate, nullptr), std::logic_error);
}

TEST(Rfk_Struct_getMethodByPredicate, FindingPredicate)
{
	char const* name = "getIntField";
	auto predicate = [](rfk::Method const& method, void* data) -> bool
	{
		return method.hasSameName(*reinterpret_cast<char const**>(data));
	};

	EXPECT_NE(TestClass::staticGetArchetype().getMethodByPredicate(predicate, &name), nullptr);
}

TEST(Rfk_Struct_getMethodByPredicate, NonFindingPredicate)
{
	char const* name = "inexistantMethod";
	auto predicate = [](rfk::Method const& method, void* data) -> bool
	{
		return method.hasSameName(*reinterpret_cast<char const**>(data));
	};

	EXPECT_EQ(TestClass::staticGetArchetype().getMethodByPredicate(predicate, &name), nullptr);
}

//=========================================================
//============= Struct::getMethodsByPredicate =============
//=========================================================

TEST(Rfk_Struct_getMethodsByPredicate, NullptrPredicate)
{
	EXPECT_EQ(TestClass::staticGetArchetype().getMethodsByPredicate(nullptr, nullptr).size(), 0u);
}

TEST(Rfk_Struct_getMethodsByPredicate, ThrowingPredicate)
{
	auto predicate = [](rfk::Method const&, void*) -> bool
	{
		throw std::logic_error("Error");
	};

	EXPECT_THROW(TestClass::staticGetArchetype().getMethodsByPredicate(predicate, nullptr), std::logic_error);
}

TEST(Rfk_Struct_getMethodsByPredicate, FindingPredicate)
{
	char const* name = "getIntField";
	auto predicate = [](rfk::Method const& method, void* data) -> bool
	{
		return method.hasSameName(*reinterpret_cast<char const**>(data));
	};

	EXPECT_EQ(TestClass::staticGetArchetype().getMethodsByPredicate(predicate, &name).size(), 2u);
}

TEST(Rfk_Struct_getMethodsByPredicate, FindingPredicateWithInherited)
{
	char const* name = "getIntField";
	auto predicate = [](rfk::Method const& method, void* data) -> bool
	{
		return method.hasSameName(*reinterpret_cast<char const**>(data));
	};

	EXPECT_EQ(TestClass2::staticGetArchetype().getMethodsByPredicate(predicate, &name, false).size(), 0u);
	EXPECT_EQ(TestClass2::staticGetArchetype().getMethodsByPredicate(predicate, &name, true).size(), 2u);
}

TEST(Rfk_Struct_getMethodsByPredicate, NonFindingPredicate)
{
	char const* name = "inexistantMethod";
	auto predicate = [](rfk::Method const& method, void* data) -> bool
	{
		return method.hasSameName(*reinterpret_cast<char const**>(data));
	};

	EXPECT_EQ(TestClass::staticGetArchetype().getMethodsByPredicate(predicate, &name).size(), 0u);
}

//=========================================================
//================= Struct::foreachMethod =================
//=========================================================

TEST(Rfk_Struct_foreachMethod, NullptrVisitor)
{
	EXPECT_FALSE(TestClass::staticGetArchetype().foreachMethod(nullptr, nullptr));
}

TEST(Rfk_Struct_foreachMethod, CompleteLoop)
{
	int counter = 0;
	auto visitor = [](rfk::Method const&, void* data)
	{
		int& counter = *reinterpret_cast<int*>(data);
		counter++;

		return true;
	};

	EXPECT_TRUE(TestClass::staticGetArchetype().foreachMethod(visitor, &counter));

	EXPECT_EQ(counter, TestClass::staticGetArchetype().getMethodsCount());
}

TEST(Rfk_Struct_foreachMethod, CompleteLoopWithInherited)
{
	int counter = 0;
	auto visitor = [](rfk::Method const&, void* data)
	{
		int& counter = *reinterpret_cast<int*>(data);
		counter++;

		return true;
	};

	EXPECT_TRUE(TestClass2::staticGetArchetype().foreachMethod(visitor, &counter, true));

	EXPECT_EQ(counter, TestClass2::staticGetArchetype().getMethodsCount() + TestClass::staticGetArchetype().getMethodsCount());
}

TEST(Rfk_Struct_foreachMethod, BreakingLoop)
{
	int counter = 0;
	auto visitor = [](rfk::Method const&, void* data)
	{
		int& counter = *reinterpret_cast<int*>(data);
		counter++;

		return false;
	};

	EXPECT_FALSE(TestClass::staticGetArchetype().foreachMethod(visitor, &counter));

	EXPECT_EQ(counter, 1u);
}

TEST(Rfk_Struct_foreachMethod, ThrowingVisitor)
{
	auto visitor = [](rfk::Method const&, void*) -> bool
	{
		throw std::logic_error("Error");
	};

	EXPECT_THROW(TestClass::staticGetArchetype().foreachMethod(visitor, nullptr), std::logic_error);
}

//=========================================================
//================ Struct::getMethodsCount ================
//=========================================================

TEST(Rfk_Struct_getMethodsCount, NoMethods)
{
	EXPECT_EQ(rfk::getDatabase().getNamespaceByName("test_namespace")->getStructByName("TestNamespaceNestedStruct")->getMethodsCount(), 0u);
}

TEST(Rfk_Struct_getMethodsCount, SeveralMethods)
{
	EXPECT_EQ(TestClass::staticGetArchetype().getMethodsCount(), 2u);
	EXPECT_EQ(TestClass2::staticGetArchetype().getMethodsCount(), 0u);	//Doesn't include inherited like fields
}

//=========================================================
//============= Struct::getStaticMethodByName =============
//=========================================================

TEST(Rfk_Struct_getStaticMethodByName, ValidNameValidFlags)
{
	EXPECT_NE(TestClass::staticGetArchetype().getStaticMethodByName("getIntStaticField"), nullptr);
	EXPECT_NE(TestClass::staticGetArchetype().getStaticMethodByName("getIntStaticField", rfk::EMethodFlags::Public), nullptr);
	EXPECT_NE(TestClass::staticGetArchetype().getStaticMethodByName("getIntStaticField", rfk::EMethodFlags::Public | rfk::EMethodFlags::Static), nullptr);
}

TEST(Rfk_Struct_getStaticMethodByName, ValidNameInvalidFlags)
{
	EXPECT_EQ(TestClass::staticGetArchetype().getStaticMethodByName("getIntStaticField", rfk::EMethodFlags::Private), nullptr);
	EXPECT_EQ(TestClass::staticGetArchetype().getStaticMethodByName("getIntStaticField", rfk::EMethodFlags::Public | rfk::EMethodFlags::Private), nullptr);
}

TEST(Rfk_Struct_getStaticMethodByName, InvalidNameValidFlags)
{
	EXPECT_EQ(TestClass::staticGetArchetype().getStaticMethodByName("GetIntStaticField", rfk::EMethodFlags::Public), nullptr);
}

TEST(Rfk_Struct_getStaticMethodByName, ValidNameValidFlagsWithoutInherited)
{
	EXPECT_EQ(TestClass2::staticGetArchetype().getStaticMethodByName("getIntStaticField", rfk::EMethodFlags::Default, false), nullptr);
	EXPECT_EQ(TestClass2::staticGetArchetype().getStaticMethodByName("getIntStaticField", rfk::EMethodFlags::Public, false), nullptr);
}

TEST(Rfk_Struct_getStaticMethodByName, ValidNameValidFlagsWithInherited)
{
	EXPECT_NE(TestClass2::staticGetArchetype().getStaticMethodByName("getIntStaticField", rfk::EMethodFlags::Default, true), nullptr);
	EXPECT_NE(TestClass2::staticGetArchetype().getStaticMethodByName("getIntStaticField", rfk::EMethodFlags::Public, true), nullptr);
}

//=========================================================
//============ Struct::getStaticMethodsByName =============
//=========================================================

TEST(Rfk_Struct_getStaticMethodsByName, ValidNameValidFlags)
{
	EXPECT_EQ(TestClass::staticGetArchetype().getStaticMethodsByName("getIntStaticField").size(), 2u);
}

TEST(Rfk_Struct_getStaticMethodsByName, ValidNameInvalidFlags)
{
	EXPECT_EQ(TestClass::staticGetArchetype().getStaticMethodsByName("getIntStaticField", rfk::EMethodFlags::Private).size(), 0u);
	EXPECT_EQ(TestClass::staticGetArchetype().getStaticMethodsByName("getIntStaticField", rfk::EMethodFlags::Public | rfk::EMethodFlags::Private).size(), 0u);
}

TEST(Rfk_Struct_getStaticMethodsByName, InvalidNameValidFlags)
{
	EXPECT_EQ(TestClass::staticGetArchetype().getStaticMethodsByName("GetIntStaticField", rfk::EMethodFlags::Public).size(), 0u);
}

TEST(Rfk_Struct_getStaticMethodsByName, ValidNameValidFlagsWithoutInherited)
{
	EXPECT_EQ(TestClass2::staticGetArchetype().getStaticMethodsByName("getIntStaticField", rfk::EMethodFlags::Default, false).size(), 0u);
	EXPECT_EQ(TestClass2::staticGetArchetype().getStaticMethodsByName("getIntStaticField", rfk::EMethodFlags::Public, false).size(), 0u);
}

TEST(Rfk_Struct_getStaticMethodsByName, ValidNameValidFlagsWithInherited)
{
	EXPECT_EQ(TestClass2::staticGetArchetype().getStaticMethodsByName("getIntStaticField", rfk::EMethodFlags::Default, true).size(), 2u);
	EXPECT_EQ(TestClass2::staticGetArchetype().getStaticMethodsByName("getIntStaticField", rfk::EMethodFlags::Public, true).size(), 2u);
}

//=========================================================
//========== Struct::getStaticMethodByPredicate ===========
//=========================================================

TEST(Rfk_Struct_getStaticMethodByPredicate, NullptrPredicate)
{
	EXPECT_EQ(TestClass::staticGetArchetype().getStaticMethodByPredicate(nullptr, nullptr), nullptr);
}

TEST(Rfk_Struct_getStaticMethodByPredicate, ThrowingPredicate)
{
	auto predicate = [](rfk::StaticMethod const&, void*) -> bool
	{
		throw std::logic_error("Error");
	};

	EXPECT_THROW(TestClass::staticGetArchetype().getStaticMethodByPredicate(predicate, nullptr), std::logic_error);
}

TEST(Rfk_Struct_getStaticMethodByPredicate, FindingPredicate)
{
	char const* name = "getIntStaticField";
	auto predicate = [](rfk::StaticMethod const& method, void* data) -> bool
	{
		return method.hasSameName(*reinterpret_cast<char const**>(data));
	};

	EXPECT_NE(TestClass::staticGetArchetype().getStaticMethodByPredicate(predicate, &name), nullptr);
}

TEST(Rfk_Struct_getStaticMethodByPredicate, NonFindingPredicate)
{
	char const* name = "inexistantStaticMethod";
	auto predicate = [](rfk::StaticMethod const& method, void* data) -> bool
	{
		return method.hasSameName(*reinterpret_cast<char const**>(data));
	};

	EXPECT_EQ(TestClass::staticGetArchetype().getStaticMethodByPredicate(predicate, &name), nullptr);
}

//=========================================================
//========== Struct::getStaticMethodsByPredicate ==========
//=========================================================

TEST(Rfk_Struct_getStaticMethodsByPredicate, NullptrPredicate)
{
	EXPECT_EQ(TestClass::staticGetArchetype().getStaticMethodsByPredicate(nullptr, nullptr).size(), 0u);
}

TEST(Rfk_Struct_getStaticMethodsByPredicate, ThrowingPredicate)
{
	auto predicate = [](rfk::StaticMethod const&, void*) -> bool
	{
		throw std::logic_error("Error");
	};

	EXPECT_THROW(TestClass::staticGetArchetype().getStaticMethodsByPredicate(predicate, nullptr), std::logic_error);
}

TEST(Rfk_Struct_getStaticMethodsByPredicate, FindingPredicate)
{
	char const* name = "getIntStaticField";
	auto predicate = [](rfk::StaticMethod const& method, void* data) -> bool
	{
		return method.hasSameName(*reinterpret_cast<char const**>(data));
	};

	EXPECT_EQ(TestClass::staticGetArchetype().getStaticMethodsByPredicate(predicate, &name).size(), 2u);
}

TEST(Rfk_Struct_getStaticMethodsByPredicate, FindingPredicateWithInherited)
{
	char const* name = "getIntStaticField";
	auto predicate = [](rfk::StaticMethod const& method, void* data) -> bool
	{
		return method.hasSameName(*reinterpret_cast<char const**>(data));
	};

	EXPECT_EQ(TestClass2::staticGetArchetype().getStaticMethodsByPredicate(predicate, &name, false).size(), 0u);
	EXPECT_EQ(TestClass2::staticGetArchetype().getStaticMethodsByPredicate(predicate, &name, true).size(), 2u);
}

TEST(Rfk_Struct_getStaticMethodsByPredicate, NonFindingPredicate)
{
	char const* name = "inexistantStaticMethod";
	auto predicate = [](rfk::StaticMethod const& method, void* data) -> bool
	{
		return method.hasSameName(*reinterpret_cast<char const**>(data));
	};

	EXPECT_EQ(TestClass::staticGetArchetype().getStaticMethodsByPredicate(predicate, &name).size(), 0u);
}

//=========================================================
//============== Struct::foreachStaticMethod ==============
//=========================================================

TEST(Rfk_Struct_foreachStaticMethod, NullptrVisitor)
{
	EXPECT_FALSE(TestClass::staticGetArchetype().foreachStaticMethod(nullptr, nullptr));
}

TEST(Rfk_Struct_foreachStaticMethod, CompleteLoop)
{
	int counter = 0;
	auto visitor = [](rfk::StaticMethod const&, void* data)
	{
		int& counter = *reinterpret_cast<int*>(data);
		counter++;

		return true;
	};

	EXPECT_TRUE(TestClass::staticGetArchetype().foreachStaticMethod(visitor, &counter));

	EXPECT_EQ(counter, TestClass::staticGetArchetype().getStaticMethodsCount());
}

TEST(Rfk_Struct_foreachStaticMethod, CompleteLoopWithInherited)
{
	int counter = 0;
	auto visitor = [](rfk::StaticMethod const&, void* data)
	{
		int& counter = *reinterpret_cast<int*>(data);
		counter++;

		return true;
	};

	EXPECT_TRUE(TestClass2::staticGetArchetype().foreachStaticMethod(visitor, &counter, true));

	EXPECT_EQ(counter, TestClass2::staticGetArchetype().getStaticMethodsCount() + TestClass::staticGetArchetype().getStaticMethodsCount());
}

TEST(Rfk_Struct_foreachStaticMethod, BreakingLoop)
{
	int counter = 0;
	auto visitor = [](rfk::StaticMethod const&, void* data)
	{
		int& counter = *reinterpret_cast<int*>(data);
		counter++;

		return false;
	};

	EXPECT_FALSE(TestClass::staticGetArchetype().foreachStaticMethod(visitor, &counter));

	EXPECT_EQ(counter, 1u);
}

TEST(Rfk_Struct_foreachStaticMethod, ThrowingVisitor)
{
	auto visitor = [](rfk::StaticMethod const&, void*) -> bool
	{
		throw std::logic_error("Error");
	};

	EXPECT_THROW(TestClass::staticGetArchetype().foreachStaticMethod(visitor, nullptr), std::logic_error);
}

//=========================================================
//============= Struct::getStaticMethodsCount =============
//=========================================================

TEST(Rfk_Struct_getStaticMethodsCount, NoStaticMethods)
{
	EXPECT_EQ(rfk::getDatabase().getNamespaceByName("test_namespace")->getStructByName("TestNamespaceNestedStruct")->getStaticMethodsCount(), 0u);
}

TEST(Rfk_Struct_getStaticMethodsCount, SeveralStaticMethods)
{
	EXPECT_EQ(TestClass::staticGetArchetype().getStaticMethodsCount(), 2u);
	EXPECT_EQ(TestClass2::staticGetArchetype().getStaticMethodsCount(), 0u);	//Doesn't include inherited like fields
}

//=========================================================
//================= Struct::getClassKind ==================
//=========================================================

TEST(Rfk_Struct_getClassKind, StandardClass)
{
	EXPECT_EQ(TestClass::staticGetArchetype().getClassKind(), rfk::EClassKind::Standard);
}

TEST(Rfk_Struct_getClassKind, ClassTemplate)
{
	EXPECT_EQ(rfk::classTemplateCast(rfk::getArchetype<SingleTypeTemplateClassTemplate>())->getClassKind(), rfk::EClassKind::Template);
}

TEST(Rfk_Struct_getClassKind, ClassTemplateInstantiation)
{
	EXPECT_EQ(SingleTypeTemplateClassTemplate<int>::staticGetArchetype().getClassKind(), rfk::EClassKind::TemplateInstantiation);
}

//=========================================================
//============== Struct::getOrderedFields =================
//=========================================================

TEST(Rfk_Struct_getOrderedFields, NoParentsVirtualClass)
{
	rfk::Vector<rfk::Field const*> fields = TestGetOrderedFieldsBase::staticGetArchetype().getOrderedFields();

	EXPECT_EQ(fields.size(), 6u);
	EXPECT_STREQ(fields[0]->getName(), "i");
	EXPECT_STREQ(fields[1]->getName(), "j");
	EXPECT_STREQ(fields[2]->getName(), "k");
	EXPECT_STREQ(fields[3]->getName(), "l");
	EXPECT_STREQ(fields[4]->getName(), "m");
	EXPECT_STREQ(fields[5]->getName(), "n");
}

TEST(Rfk_Struct_getOrderedFields, NoParentsNonVirtualClass)
{
	rfk::Vector<rfk::Field const*> fields = TestGetOrderedFieldsBase2::staticGetArchetype().getOrderedFields();

	EXPECT_EQ(fields.size(), 3u);
	EXPECT_STREQ(fields[0]->getName(), "o");
	EXPECT_STREQ(fields[1]->getName(), "p");
	EXPECT_STREQ(fields[2]->getName(), "q");
}

TEST(Rfk_Struct_getOrderedFields, SingleInheritanceClassExcludeInheritedFields)
{
	rfk::Vector<rfk::Field const*> fields = TestGetOrderedFieldsSingleInheritanceChild::staticGetArchetype().getOrderedFields(false);

	EXPECT_EQ(fields.size(), 3u);
	EXPECT_STREQ(fields[0]->getName(), "r");
	EXPECT_STREQ(fields[1]->getName(), "s");
	EXPECT_STREQ(fields[2]->getName(), "t");
}

TEST(Rfk_Struct_getOrderedFields, SingleInheritanceClassIncludeInheritedFields)
{
	rfk::Vector<rfk::Field const*> fields = TestGetOrderedFieldsSingleInheritanceChild::staticGetArchetype().getOrderedFields(true);

	EXPECT_EQ(fields.size(), 9u);
	EXPECT_STREQ(fields[0]->getName(), "i");
	EXPECT_STREQ(fields[1]->getName(), "j");
	EXPECT_STREQ(fields[2]->getName(), "k");
	EXPECT_STREQ(fields[3]->getName(), "l");
	EXPECT_STREQ(fields[4]->getName(), "m");
	EXPECT_STREQ(fields[5]->getName(), "n");
	EXPECT_STREQ(fields[6]->getName(), "r");
	EXPECT_STREQ(fields[7]->getName(), "s");
	EXPECT_STREQ(fields[8]->getName(), "t");
}

TEST(Rfk_Struct_getOrderedFields, MultipleInheritanceClassExcludeInheritedFields)
{
	rfk::Vector<rfk::Field const*> fields = TestGetOrderedFieldsMultipleInheritanceChild::staticGetArchetype().getOrderedFields(false);

	EXPECT_EQ(fields.size(), 3u);
	EXPECT_STREQ(fields[0]->getName(), "r");
	EXPECT_STREQ(fields[1]->getName(), "s");
	EXPECT_STREQ(fields[2]->getName(), "t");
}

TEST(Rfk_Struct_getOrderedFields, MultipleInheritanceClassIncludeInheritedFields)
{
	rfk::Vector<rfk::Field const*> fields = TestGetOrderedFieldsMultipleInheritanceChild::staticGetArchetype().getOrderedFields(true);

	EXPECT_EQ(fields.size(), 12u);
	EXPECT_STREQ(fields[0]->getName(), "i");
	EXPECT_STREQ(fields[1]->getName(), "j");
	EXPECT_STREQ(fields[2]->getName(), "k");
	EXPECT_STREQ(fields[3]->getName(), "l");
	EXPECT_STREQ(fields[4]->getName(), "m");
	EXPECT_STREQ(fields[5]->getName(), "n");
	EXPECT_STREQ(fields[6]->getName(), "o");
	EXPECT_STREQ(fields[7]->getName(), "p");
	EXPECT_STREQ(fields[8]->getName(), "q");
	EXPECT_STREQ(fields[9]->getName(), "r");
	EXPECT_STREQ(fields[10]->getName(), "s");
	EXPECT_STREQ(fields[11]->getName(), "t");
}