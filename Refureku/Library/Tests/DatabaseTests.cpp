#include <stdexcept>	//std::logic_error

#include <gtest/gtest.h>
#include <Refureku/Refureku.h>

#include "TestStruct.h"
#include "TestEnum.h"
#include "TestNamespace.h"
#include "SingleTypeTemplateClassTemplate.h"
#include "MultipleTypeTemplateClassTemplate.h"
#include "TestDatabase.h"

//=========================================================
//=============== Database::getEntityById =================
//=========================================================

TEST(Rfk_Database_getEntityById, FundamentalArchetype)
{
	EXPECT_NE(rfk::getDatabase().getEntityById(rfk::getArchetype<void>()->getId()), nullptr);
}

TEST(Rfk_Database_getEntityById, FileLevelEnum)
{
	EXPECT_NE(rfk::getDatabase().getEntityById(rfk::getEnum<FileLevelEnum>()->getId()), nullptr);
}

TEST(Rfk_Database_getEntityById, NamespaceNestedEnum)
{
	EXPECT_NE(rfk::getDatabase().getEntityById(rfk::getEnum<filelevel_namespace::NamespaceEnum>()->getId()), nullptr);
}

TEST(Rfk_Database_getEntityById, ClassNestedEnum)
{
	EXPECT_NE(rfk::getDatabase().getEntityById(rfk::getEnum<FileLevelClass::ClassEnum>()->getId()), nullptr);
}

TEST(Rfk_Database_getEntityById, FileLevelClass)
{
	EXPECT_NE(rfk::getDatabase().getEntityById(FileLevelClass::staticGetArchetype().getId()), nullptr);
}

TEST(Rfk_Database_getEntityById, NamespaceNestedClass)
{
	EXPECT_NE(rfk::getDatabase().getEntityById(filelevel_namespace::NamespaceClass::staticGetArchetype().getId()), nullptr);
}

TEST(Rfk_Database_getEntityById, ClassNestedClass)
{
	EXPECT_NE(rfk::getDatabase().getEntityById(FileLevelClass::ClassClass::staticGetArchetype().getId()), nullptr);
}

TEST(Rfk_Database_getEntityById, FileLevelStruct)
{
	EXPECT_NE(rfk::getDatabase().getEntityById(FileLevelStruct::staticGetArchetype().getId()), nullptr);
}

TEST(Rfk_Database_getEntityById, NamespaceNestedStruct)
{
	EXPECT_NE(rfk::getDatabase().getEntityById(filelevel_namespace::NamespaceStruct::staticGetArchetype().getId()), nullptr);
}

TEST(Rfk_Database_getEntityById, ClassNestedStruct)
{
	EXPECT_NE(rfk::getDatabase().getEntityById(FileLevelClass::ClassStruct::staticGetArchetype().getId()), nullptr);
}

TEST(Rfk_Database_getEntityById, ReflectedEnumValue)
{
	EXPECT_NE(rfk::getDatabase().getEntityById(rfk::getEnum<FileLevelEnum>()->getEnumValueAt(0).getId()), nullptr);
}

TEST(Rfk_Database_getEntityById, NonReflectedEnumValue)
{
	EXPECT_NE(rfk::getDatabase().getEntityById(rfk::getEnum<FileLevelEnum>()->getEnumValueAt(1).getId()), nullptr);
}

TEST(Rfk_Database_getEntityById, ClassTemplate)
{
	EXPECT_NE(rfk::getDatabase().getEntityById(rfk::getArchetype<SingleTypeTemplateClassTemplate>()->getId()), nullptr);
}

TEST(Rfk_Database_getEntityById, ClassTemplateInstance)
{
	EXPECT_NE(rfk::getDatabase().getEntityById(SingleTypeTemplateClassTemplate<int>::staticGetArchetype().getId()), nullptr);
}

TEST(Rfk_Database_getEntityById, FileLevelNamespace)
{
	EXPECT_NE(rfk::getDatabase().getEntityById(rfk::getDatabase().getNamespaceByName("filelevel_namespace")->getId()), nullptr);
}

TEST(Rfk_Database_getEntityById, NamespaceNestedNamespace)
{
	EXPECT_NE(rfk::getDatabase().getEntityById(rfk::getDatabase().getNamespaceByName("filelevel_namespace::nested_namespace")->getId()), nullptr);
}

TEST(Rfk_Database_getEntityById, FileLevelVariable)
{
	EXPECT_NE(rfk::getDatabase().getEntityById(rfk::getDatabase().getVariableByName("fileLevelVar")->getId()), nullptr);
}

TEST(Rfk_Database_getEntityById, NamespaceNestedVariable)
{
	EXPECT_NE(rfk::getDatabase().getEntityById(rfk::getDatabase().getNamespaceByName("filelevel_namespace")->getVariableByName("namespaceVar")->getId()), nullptr);
}

TEST(Rfk_Database_getEntityById, FileLevelFunction)
{
	EXPECT_NE(rfk::getDatabase().getEntityById(rfk::getDatabase().getFunctionByName("fileLevelFunc")->getId()), nullptr);
}

TEST(Rfk_Database_getEntityById, NamespaceNestedFunction)
{
	EXPECT_NE(rfk::getDatabase().getEntityById(rfk::getDatabase().getNamespaceByName("filelevel_namespace")->getFunctionByName("namespaceFunc")->getId()), nullptr);
}

TEST(Rfk_Database_getEntityById, Method)
{
	EXPECT_NE(rfk::getDatabase().getEntityById(FileLevelClass::staticGetArchetype().getMethodByName("method")->getId()), nullptr);
}

TEST(Rfk_Database_getEntityById, StaticMethod)
{
	EXPECT_NE(rfk::getDatabase().getEntityById(FileLevelClass::staticGetArchetype().getStaticMethodByName("staticMethod")->getId()), nullptr);
}

TEST(Rfk_Database_getEntityById, Field)
{
	EXPECT_NE(rfk::getDatabase().getEntityById(FileLevelClass::staticGetArchetype().getFieldByName("_field")->getId()), nullptr);
}

TEST(Rfk_Database_getEntityById, StaticField)
{
	EXPECT_NE(rfk::getDatabase().getEntityById(FileLevelClass::staticGetArchetype().getStaticFieldByName("_staticField")->getId()), nullptr);
}

//=========================================================
//============= Database::getNamespaceById ================
//=========================================================

TEST(Rfk_Database_getNamespaceById, NamespaceId)
{
	rfk::Namespace const* n = rfk::getDatabase().getNamespaceByName("filelevel_namespace");

	EXPECT_NE(n, nullptr);
	EXPECT_NE(rfk::getDatabase().getNamespaceById(n->getId()), nullptr);
}

TEST(Rfk_Database_getNamespaceById, NonNamespaceEntityId)
{
	EXPECT_EQ(rfk::getDatabase().getNamespaceById(FileLevelClass::staticGetArchetype().getId()), nullptr);
}

//=========================================================
//============ Database::getNamespaceByName ===============
//=========================================================

TEST(Rfk_Database_getNamespaceByName, NonNestedNamespace)
{
	EXPECT_NE(rfk::getDatabase().getNamespaceByName("filelevel_namespace"), nullptr);
}

TEST(Rfk_Database_getNamespaceByName, NestedNamespace)
{
	EXPECT_EQ(rfk::getDatabase().getNamespaceByName("nested_namespace"), nullptr);
	EXPECT_NE(rfk::getDatabase().getNamespaceByName("filelevel_namespace::nested_namespace"), nullptr);
}

TEST(Rfk_Database_getNamespaceByName, BadNamespaceFormat)
{
	EXPECT_THROW(rfk::getDatabase().getNamespaceByName("filelevel_namespace:nested_namespace"), rfk::BadNamespaceFormat);
	EXPECT_THROW(rfk::getDatabase().getNamespaceByName("filelevel_namespace::nested_namespace:"), rfk::BadNamespaceFormat);
	EXPECT_THROW(rfk::getDatabase().getNamespaceByName(":filelevel_namespace::nested_namespace"), rfk::BadNamespaceFormat);
}

TEST(Rfk_Database_getNamespaceByName, NonNamespaceEntity)
{
	EXPECT_EQ(rfk::getDatabase().getNamespaceByName("FileLevelEnum"), nullptr);
}

//=========================================================
//====== Database::getFileLevelNamespaceByPredicate =======
//=========================================================

TEST(Rfk_Database_getFileLevelNamespaceByPredicate, NullptrPredicate)
{
	EXPECT_EQ(rfk::getDatabase().getFileLevelNamespaceByPredicate(nullptr, nullptr), nullptr);
}

TEST(Rfk_Database_getFileLevelNamespaceByPredicate, ThrowingPredicate)
{
	auto predicate = [](rfk::Namespace const&, void*) -> bool
	{
		throw std::logic_error("Error");
	};

	EXPECT_THROW(rfk::getDatabase().getFileLevelNamespaceByPredicate(predicate, nullptr), std::logic_error);
}

TEST(Rfk_Database_getFileLevelNamespaceByPredicate, FindingPredicate)
{
	char const* propName = "TestDabataseProperty";
	auto predicate = [](rfk::Namespace const& n, void* userData) -> bool
	{
		return n.getPropertyByName(*reinterpret_cast<char const**>(userData)) != nullptr;
	};

	EXPECT_NE(rfk::getDatabase().getFileLevelNamespaceByPredicate(predicate, &propName), nullptr);
}

TEST(Rfk_Database_getFileLevelNamespaceByPredicate, NonFindingPredicate)
{
	char const* propName = "NonExistantProperty";
	auto predicate = [](rfk::Namespace const& n, void* userData) -> bool
	{
		return n.getPropertyByName(*reinterpret_cast<char const**>(userData)) != nullptr;
	};

	EXPECT_EQ(rfk::getDatabase().getFileLevelNamespaceByPredicate(predicate, &propName), nullptr);
}

//=========================================================
//====== Database::getFileLevelNamespacesByPredicate ======
//=========================================================

TEST(Rfk_Database_getFileLevelNamespacesByPredicate, NullptrPredicate)
{
	EXPECT_TRUE(rfk::getDatabase().getFileLevelNamespacesByPredicate(nullptr, nullptr).empty());
}

TEST(Rfk_Database_getFileLevelNamespacesByPredicate, ThrowingPredicate)
{
	auto predicate = [](rfk::Namespace const&, void*) -> bool
	{
		throw std::logic_error("Error");
	};

	EXPECT_THROW(rfk::getDatabase().getFileLevelNamespacesByPredicate(predicate, nullptr), std::logic_error);
}

TEST(Rfk_Database_getFileLevelNamespacesByPredicate, FindingPredicate)
{
	char const* propName = "TestDabataseProperty";
	auto predicate = [](rfk::Namespace const& n, void* userData) -> bool
	{
		return n.getPropertyByName(*reinterpret_cast<char const**>(userData)) != nullptr;
	};

	EXPECT_EQ(rfk::getDatabase().getFileLevelNamespacesByPredicate(predicate, &propName).size(), 2u);
}

TEST(Rfk_Database_getFileLevelNamespacesByPredicate, NonFindingPredicate)
{
	char const* propName = "NonExistantProperty";
	auto predicate = [](rfk::Namespace const& n, void* userData) -> bool
	{
		return n.getPropertyByName(*reinterpret_cast<char const**>(userData)) != nullptr;
	};

	EXPECT_TRUE(rfk::getDatabase().getFileLevelNamespacesByPredicate(predicate, &propName).empty());
}

//=========================================================
// Database::foreachFileLevelNamespace / getFileLevelNamespacesCount
//=========================================================

TEST(Rfk_Database_foreachFileLevelNamespace_getFileLevelNamespacesCount, NullptrVisitor)
{
	EXPECT_FALSE(rfk::getDatabase().foreachFileLevelNamespace(nullptr, nullptr));
}

TEST(Rfk_Database_foreachFileLevelNamespace_getFileLevelNamespacesCount, ThrowingVisitor)
{
	auto visitor = [](rfk::Namespace const&, void*) -> bool
	{
		throw std::logic_error("Error");
	};

	EXPECT_THROW(rfk::getDatabase().foreachFileLevelNamespace(visitor, nullptr), std::logic_error);
}

TEST(Rfk_Database_foreachFileLevelNamespace_getFileLevelNamespacesCount, CompleteLoop)
{
	int counter = 0;
	auto visitor = [](rfk::Namespace const&, void* data)
	{
		int& counter = *reinterpret_cast<int*>(data);
		counter++;

		return true;
	};

	EXPECT_TRUE(rfk::getDatabase().foreachFileLevelNamespace(visitor, &counter));
	EXPECT_EQ(counter, rfk::getDatabase().getFileLevelNamespacesCount());
}

TEST(Rfk_Database_foreachFileLevelNamespace_getFileLevelNamespacesCount, BreakingLoop)
{
	int counter = 0;
	auto visitor = [](rfk::Namespace const&, void* data)
	{
		int& counter = *reinterpret_cast<int*>(data);
		counter++;

		return false;
	};

	EXPECT_FALSE(rfk::getDatabase().foreachFileLevelNamespace(visitor, &counter));
	EXPECT_EQ(counter, 1u);
}

//=========================================================
//============= Database::getArchetypeById ================
//=========================================================

TEST(Rfk_Database_getArchetypeById, ClassId)
{
	EXPECT_NE(rfk::getDatabase().getArchetypeById(FileLevelClass::staticGetArchetype().getId()), nullptr);
}

TEST(Rfk_Database_getArchetypeById, StructId)
{
	EXPECT_NE(rfk::getDatabase().getArchetypeById(FileLevelStruct::staticGetArchetype().getId()), nullptr);
}

TEST(Rfk_Database_getArchetypeById, EnumId)
{
	EXPECT_NE(rfk::getDatabase().getArchetypeById(rfk::getEnum<FileLevelEnum>()->getId()), nullptr);
}

TEST(Rfk_Database_getArchetypeById, NonArchetypeEntityId)
{
	EXPECT_EQ(rfk::getDatabase().getArchetypeById(rfk::getEnum<FileLevelEnum>()->getEnumValueAt(0).getId()), nullptr);
	EXPECT_EQ(rfk::getDatabase().getArchetypeById(rfk::getDatabase().getNamespaceByName("filelevel_namespace")->getId()), nullptr);
}

//=========================================================
//======== Database::getFileLevelArchetypeByName ==========
//=========================================================

TEST(Rfk_Database_getFileLevelArchetypeByName, NonNestedClass)
{
	EXPECT_NE(rfk::getDatabase().getFileLevelArchetypeByName("FileLevelClass"), nullptr);
}

TEST(Rfk_Database_getFileLevelArchetypeByName, NonNestedStruct)
{
	EXPECT_NE(rfk::getDatabase().getFileLevelArchetypeByName("FileLevelStruct"), nullptr);
}

TEST(Rfk_Database_getFileLevelArchetypeByName, NonNestedEnum)
{
	EXPECT_NE(rfk::getDatabase().getFileLevelArchetypeByName("FileLevelEnum"), nullptr);
}

TEST(Rfk_Database_getFileLevelArchetypeByName, FundamentalArchetype)
{
	EXPECT_NE(rfk::getDatabase().getFileLevelArchetypeByName("int"), nullptr);
}

TEST(Rfk_Database_getFileLevelArchetypeByName, NestedClass)
{
	EXPECT_EQ(rfk::getDatabase().getFileLevelArchetypeByName("ClassClass"), nullptr);
}

TEST(Rfk_Database_getFileLevelArchetypeByName, NestedStruct)
{
	EXPECT_EQ(rfk::getDatabase().getFileLevelArchetypeByName("ClassStruct"), nullptr);
}

TEST(Rfk_Database_getFileLevelArchetypeByName, NestedEnum)
{
	EXPECT_EQ(rfk::getDatabase().getFileLevelArchetypeByName("ClassEnum"), nullptr);
}

TEST(Rfk_Database_getFileLevelArchetypeByName, NonArchetypeEntities)
{
	EXPECT_EQ(rfk::getDatabase().getFileLevelArchetypeByName("filelevel_namespace"), nullptr);
	EXPECT_EQ(rfk::getDatabase().getFileLevelArchetypeByName("fileLevelVar"), nullptr);
	EXPECT_EQ(rfk::getDatabase().getFileLevelArchetypeByName("fileLevelFunc"), nullptr);
}

//=========================================================
//====== Database::getFileLevelArchetypesByPredicate ======
//=========================================================

TEST(Rfk_Database_getFileLevelArchetypesByPredicate, NullptrPredicate)
{
	EXPECT_TRUE(rfk::getDatabase().getFileLevelArchetypesByPredicate(nullptr, nullptr).empty());
}

TEST(Rfk_Database_getFileLevelArchetypesByPredicate, ThrowingPredicate)
{
	auto predicate = [](rfk::Archetype const&, void*) -> bool
	{
		throw std::logic_error("Error");
	};

	EXPECT_THROW(rfk::getDatabase().getFileLevelArchetypesByPredicate(predicate, nullptr), std::logic_error);
}

TEST(Rfk_Database_getFileLevelArchetypesByPredicate, FindingPredicate)
{
	char const* propName = "TestDabataseProperty";
	auto predicate = [](rfk::Archetype const& a, void* userData) -> bool
	{
		return a.getPropertyByName(*reinterpret_cast<char const**>(userData)) != nullptr;
	};

	EXPECT_EQ(rfk::getDatabase().getFileLevelArchetypesByPredicate(predicate, &propName).size(), 6u);
}

TEST(Rfk_Database_getFileLevelArchetypesByPredicate, NonFindingPredicate)
{
	char const* propName = "SomeInexistantProperty";
	auto predicate = [](rfk::Archetype const& a, void* userData) -> bool
	{
		return a.getPropertyByName(*reinterpret_cast<char const**>(userData)) != nullptr;
	};

	EXPECT_TRUE(rfk::getDatabase().getFileLevelArchetypesByPredicate(predicate, &propName).empty());
}

//=========================================================
//=============== Database::getStructById =================
//=========================================================

TEST(Rfk_Database_getStructById, StructId)
{
	EXPECT_NE(rfk::getDatabase().getStructById(FileLevelStruct::staticGetArchetype().getId()), nullptr);
}

TEST(Rfk_Database_getStructById, NonStructEntityId)
{
	EXPECT_EQ(rfk::getDatabase().getStructById(rfk::getEnum<FileLevelEnum>()->getId()), nullptr);
	EXPECT_EQ(rfk::getDatabase().getStructById(FileLevelClass::staticGetArchetype().getId()), nullptr);
}

//=========================================================
//============= Database::getStructByName =================
//=========================================================

TEST(Rfk_Database_getStructByName, NonNestedStruct)
{
	EXPECT_NE(rfk::getDatabase().getFileLevelStructByName("FileLevelStruct"), nullptr);
}

TEST(Rfk_Database_getStructByName, NestedStruct)
{
	EXPECT_EQ(rfk::getDatabase().getFileLevelStructByName("ClassStruct"), nullptr);
}

TEST(Rfk_Database_getStructByName, NonStructEntity)
{
	EXPECT_EQ(rfk::getDatabase().getFileLevelStructByName("TestDabataseProperty"), nullptr);
	EXPECT_EQ(rfk::getDatabase().getFileLevelStructByName("filelevel_namespace"), nullptr);
	EXPECT_EQ(rfk::getDatabase().getFileLevelStructByName("fileLevelVar"), nullptr);
	EXPECT_EQ(rfk::getDatabase().getFileLevelStructByName("fileLevelFunc"), nullptr);
}

//=========================================================
//======== Database::getFileLevelStructByPredicate ========
//=========================================================

TEST(Rfk_Database_getFileLevelStructByPredicate, NullptrPredicate)
{
	EXPECT_EQ(rfk::getDatabase().getFileLevelStructByPredicate(nullptr, nullptr), nullptr);
}

TEST(Rfk_Database_getFileLevelStructByPredicate, ThrowingPredicate)
{
	auto predicate = [](rfk::Struct const&, void*) -> bool
	{
		throw std::logic_error("Error");
	};

	EXPECT_THROW(rfk::getDatabase().getFileLevelStructByPredicate(predicate, nullptr), std::logic_error);
}

TEST(Rfk_Database_getFileLevelStructByPredicate, FindingPredicate)
{
	char const* propName = "TestDabataseProperty";
	auto predicate = [](rfk::Struct const& n, void* userData) -> bool
	{
		return n.getPropertyByName(*reinterpret_cast<char const**>(userData)) != nullptr;
	};

	EXPECT_NE(rfk::getDatabase().getFileLevelStructByPredicate(predicate, &propName), nullptr);
}

TEST(Rfk_Database_getFileLevelStructByPredicate, NonFindingPredicate)
{
	char const* propName = "NonExistantProperty";
	auto predicate = [](rfk::Struct const& n, void* userData) -> bool
	{
		return n.getPropertyByName(*reinterpret_cast<char const**>(userData)) != nullptr;
	};

	EXPECT_EQ(rfk::getDatabase().getFileLevelStructByPredicate(predicate, &propName), nullptr);
}

//=========================================================
//======= Database::getFileLevelStructsByPredicate ========
//=========================================================

TEST(Rfk_Database_getFileLevelStructsByPredicate, NullptrPredicate)
{
	EXPECT_TRUE(rfk::getDatabase().getFileLevelStructsByPredicate(nullptr, nullptr).empty());
}

TEST(Rfk_Database_getFileLevelStructsByPredicate, ThrowingPredicate)
{
	auto predicate = [](rfk::Struct const&, void*) -> bool
	{
		throw std::logic_error("Error");
	};

	EXPECT_THROW(rfk::getDatabase().getFileLevelStructsByPredicate(predicate, nullptr), std::logic_error);
}

TEST(Rfk_Database_getFileLevelStructsByPredicate, FindingPredicate)
{
	char const* propName = "TestDabataseProperty";
	auto predicate = [](rfk::Struct const& n, void* userData) -> bool
	{
		return n.getPropertyByName(*reinterpret_cast<char const**>(userData)) != nullptr;
	};

	EXPECT_EQ(rfk::getDatabase().getFileLevelStructsByPredicate(predicate, &propName).size(), 2u);
}

TEST(Rfk_Database_getFileLevelStructsByPredicate, NonFindingPredicate)
{
	char const* propName = "NonExistantProperty";
	auto predicate = [](rfk::Struct const& n, void* userData) -> bool
	{
		return n.getPropertyByName(*reinterpret_cast<char const**>(userData)) != nullptr;
	};

	EXPECT_TRUE(rfk::getDatabase().getFileLevelStructsByPredicate(predicate, &propName).empty());
}

//=========================================================
// Database::foreachFileLevelStruct / getFileLevelStructsCount
//=========================================================

TEST(Rfk_Database_foreachFileLevelStruct_getFileLevelStructsCount, NullptrVisitor)
{
	EXPECT_FALSE(rfk::getDatabase().foreachFileLevelStruct(nullptr, nullptr));
}

TEST(Rfk_Database_foreachFileLevelStruct_getFileLevelStructsCount, ThrowingVisitor)
{
	auto visitor = [](rfk::Struct const&, void*) -> bool
	{
		throw std::logic_error("Error");
	};

	EXPECT_THROW(rfk::getDatabase().foreachFileLevelStruct(visitor, nullptr), std::logic_error);
}

TEST(Rfk_Database_foreachFileLevelStruct_getFileLevelStructsCount, CompleteLoop)
{
	int counter = 0;
	auto visitor = [](rfk::Struct const&, void* data)
	{
		int& counter = *reinterpret_cast<int*>(data);
		counter++;

		return true;
	};

	EXPECT_TRUE(rfk::getDatabase().foreachFileLevelStruct(visitor, &counter));
	EXPECT_EQ(counter, rfk::getDatabase().getFileLevelStructsCount());
}

TEST(Rfk_Database_foreachFileLevelStruct_getFileLevelStructsCount, BreakingLoop)
{
	int counter = 0;
	auto visitor = [](rfk::Struct const&, void* data)
	{
		int& counter = *reinterpret_cast<int*>(data);
		counter++;

		return false;
	};

	EXPECT_FALSE(rfk::getDatabase().foreachFileLevelStruct(visitor, &counter));
	EXPECT_EQ(counter, 1u);
}

//=========================================================
//=============== Database::getClassById =================
//=========================================================

TEST(Rfk_Database_getClassById, ClassId)
{
	EXPECT_NE(rfk::getDatabase().getClassById(FileLevelClass::staticGetArchetype().getId()), nullptr);
}

TEST(Rfk_Database_getClassById, NonClassEntityId)
{
	EXPECT_EQ(rfk::getDatabase().getClassById(rfk::getEnum<FileLevelEnum>()->getId()), nullptr);
	EXPECT_EQ(rfk::getDatabase().getClassById(FileLevelStruct::staticGetArchetype().getId()), nullptr);
}

//=========================================================
//============= Database::getClassByName =================
//=========================================================

TEST(Rfk_Database_getClassByName, NonNestedClass)
{
	EXPECT_NE(rfk::getDatabase().getFileLevelClassByName("FileLevelClass"), nullptr);
}

TEST(Rfk_Database_getClassByName, NestedClass)
{
	EXPECT_EQ(rfk::getDatabase().getFileLevelClassByName("ClassClass"), nullptr);
}

TEST(Rfk_Database_getClassByName, NonClassEntity)
{
	EXPECT_EQ(rfk::getDatabase().getFileLevelClassByName("FileLevelStruct"), nullptr);
	EXPECT_EQ(rfk::getDatabase().getFileLevelClassByName("FileLevelEnum"), nullptr);
	EXPECT_EQ(rfk::getDatabase().getFileLevelClassByName("filelevel_namespace"), nullptr);
	EXPECT_EQ(rfk::getDatabase().getFileLevelClassByName("fileLevelVar"), nullptr);
	EXPECT_EQ(rfk::getDatabase().getFileLevelClassByName("fileLevelFunc"), nullptr);
}

//=========================================================
//======== Database::getFileLevelClassByPredicate ========
//=========================================================

TEST(Rfk_Database_getFileLevelClassByPredicate, NullptrPredicate)
{
	EXPECT_EQ(rfk::getDatabase().getFileLevelClassByPredicate(nullptr, nullptr), nullptr);
}

TEST(Rfk_Database_getFileLevelClassByPredicate, ThrowingPredicate)
{
	auto predicate = [](rfk::Class const&, void*) -> bool
	{
		throw std::logic_error("Error");
	};

	EXPECT_THROW(rfk::getDatabase().getFileLevelClassByPredicate(predicate, nullptr), std::logic_error);
}

TEST(Rfk_Database_getFileLevelClassByPredicate, FindingPredicate)
{
	char const* propName = "TestDabataseProperty";
	auto predicate = [](rfk::Class const& n, void* userData) -> bool
	{
		return n.getPropertyByName(*reinterpret_cast<char const**>(userData)) != nullptr;
	};

	EXPECT_NE(rfk::getDatabase().getFileLevelClassByPredicate(predicate, &propName), nullptr);
}

TEST(Rfk_Database_getFileLevelClassByPredicate, NonFindingPredicate)
{
	char const* propName = "NonExistantProperty";
	auto predicate = [](rfk::Class const& n, void* userData) -> bool
	{
		return n.getPropertyByName(*reinterpret_cast<char const**>(userData)) != nullptr;
	};

	EXPECT_EQ(rfk::getDatabase().getFileLevelClassByPredicate(predicate, &propName), nullptr);
}

//=========================================================
//======= Database::getFileLevelClassesByPredicate ========
//=========================================================

TEST(Rfk_Database_getFileLevelClasssByPredicate, NullptrPredicate)
{
	EXPECT_TRUE(rfk::getDatabase().getFileLevelClassesByPredicate(nullptr, nullptr).empty());
}

TEST(Rfk_Database_getFileLevelClasssByPredicate, ThrowingPredicate)
{
	auto predicate = [](rfk::Class const&, void*) -> bool
	{
		throw std::logic_error("Error");
	};

	EXPECT_THROW(rfk::getDatabase().getFileLevelClassesByPredicate(predicate, nullptr), std::logic_error);
}

TEST(Rfk_Database_getFileLevelClasssByPredicate, FindingPredicate)
{
	char const* propName = "TestDabataseProperty";
	auto predicate = [](rfk::Class const& n, void* userData) -> bool
	{
		return n.getPropertyByName(*reinterpret_cast<char const**>(userData)) != nullptr;
	};

	EXPECT_EQ(rfk::getDatabase().getFileLevelClassesByPredicate(predicate, &propName).size(), 2u);
}

TEST(Rfk_Database_getFileLevelClasssByPredicate, NonFindingPredicate)
{
	char const* propName = "NonExistantProperty";
	auto predicate = [](rfk::Class const& n, void* userData) -> bool
	{
		return n.getPropertyByName(*reinterpret_cast<char const**>(userData)) != nullptr;
	};

	EXPECT_TRUE(rfk::getDatabase().getFileLevelClassesByPredicate(predicate, &propName).empty());
}

//=========================================================
// Database::foreachFileLevelClass / getFileLevelClassesCount
//=========================================================

TEST(Rfk_Database_foreachFileLevelClass_getFileLevelClasssCount, NullptrVisitor)
{
	EXPECT_FALSE(rfk::getDatabase().foreachFileLevelClass(nullptr, nullptr));
}

TEST(Rfk_Database_foreachFileLevelClass_getFileLevelClasssCount, ThrowingVisitor)
{
	auto visitor = [](rfk::Class const&, void*) -> bool
	{
		throw std::logic_error("Error");
	};

	EXPECT_THROW(rfk::getDatabase().foreachFileLevelClass(visitor, nullptr), std::logic_error);
}

TEST(Rfk_Database_foreachFileLevelClass_getFileLevelClasssCount, CompleteLoop)
{
	int counter = 0;
	auto visitor = [](rfk::Class const&, void* data)
	{
		int& counter = *reinterpret_cast<int*>(data);
		counter++;

		return true;
	};

	EXPECT_TRUE(rfk::getDatabase().foreachFileLevelClass(visitor, &counter));
	EXPECT_EQ(counter, rfk::getDatabase().getFileLevelClassesCount());
}

TEST(Rfk_Database_foreachFileLevelClass_getFileLevelClasssCount, BreakingLoop)
{
	int counter = 0;
	auto visitor = [](rfk::Class const&, void* data)
	{
		int& counter = *reinterpret_cast<int*>(data);
		counter++;

		return false;
	};

	EXPECT_FALSE(rfk::getDatabase().foreachFileLevelClass(visitor, &counter));
	EXPECT_EQ(counter, 1u);
}

//=========================================================
//================ Database::getEnumById ==================
//=========================================================

TEST(Rfk_Database_getEnumById, EnumId)
{
	EXPECT_NE(rfk::getDatabase().getEnumById(rfk::getEnum<FileLevelEnum>()->getId()), nullptr);
}

TEST(Rfk_Database_getEnumById, NonEnumEntityId)
{
	EXPECT_EQ(rfk::getDatabase().getEnumById(rfk::getDatabase().getNamespaceByName("filelevel_namespace")->getId()), nullptr);
	EXPECT_EQ(rfk::getDatabase().getEnumById(FileLevelClass::staticGetArchetype().getId()), nullptr);
	EXPECT_EQ(rfk::getDatabase().getEnumById(FileLevelStruct::staticGetArchetype().getId()), nullptr);
}

//=========================================================
//============== Database::getEnumByName ==================
//=========================================================

TEST(Rfk_Database_getEnumByName, NonNestedEnum)
{
	EXPECT_NE(rfk::getDatabase().getFileLevelEnumByName("FileLevelEnum"), nullptr);
}

TEST(Rfk_Database_getEnumByName, NestedEnum)
{
	EXPECT_EQ(rfk::getDatabase().getFileLevelEnumByName("ClassEnum"), nullptr);
}

TEST(Rfk_Database_getEnumByName, NonEnumEntity)
{
	EXPECT_EQ(rfk::getDatabase().getFileLevelEnumByName("FileLevelStruct"), nullptr);
	EXPECT_EQ(rfk::getDatabase().getFileLevelEnumByName("FileLevelClass"), nullptr);
	EXPECT_EQ(rfk::getDatabase().getFileLevelEnumByName("filelevel_namespace"), nullptr);
	EXPECT_EQ(rfk::getDatabase().getFileLevelEnumByName("fileLevelVar"), nullptr);
	EXPECT_EQ(rfk::getDatabase().getFileLevelEnumByName("fileLevelFunc"), nullptr);
}

//=========================================================
//========= Database::getFileLevelEnumByPredicate =========
//=========================================================

TEST(Rfk_Database_getFileLevelEnumByPredicate, NullptrPredicate)
{
	EXPECT_EQ(rfk::getDatabase().getFileLevelEnumByPredicate(nullptr, nullptr), nullptr);
}

TEST(Rfk_Database_getFileLevelEnumByPredicate, ThrowingPredicate)
{
	auto predicate = [](rfk::Enum const&, void*) -> bool
	{
		throw std::logic_error("Error");
	};

	EXPECT_THROW(rfk::getDatabase().getFileLevelEnumByPredicate(predicate, nullptr), std::logic_error);
}

TEST(Rfk_Database_getFileLevelEnumByPredicate, FindingPredicate)
{
	char const* propName = "TestDabataseProperty";
	auto predicate = [](rfk::Enum const& n, void* userData) -> bool
	{
		return n.getPropertyByName(*reinterpret_cast<char const**>(userData)) != nullptr;
	};

	EXPECT_NE(rfk::getDatabase().getFileLevelEnumByPredicate(predicate, &propName), nullptr);
}

TEST(Rfk_Database_getFileLevelEnumByPredicate, NonFindingPredicate)
{
	char const* propName = "NonExistantProperty";
	auto predicate = [](rfk::Enum const& n, void* userData) -> bool
	{
		return n.getPropertyByName(*reinterpret_cast<char const**>(userData)) != nullptr;
	};

	EXPECT_EQ(rfk::getDatabase().getFileLevelEnumByPredicate(predicate, &propName), nullptr);
}

//=========================================================
//======== Database::getFileLevelEnumsByPredicate =========
//=========================================================

TEST(Rfk_Database_getFileLevelEnumsByPredicate, NullptrPredicate)
{
	EXPECT_TRUE(rfk::getDatabase().getFileLevelEnumsByPredicate(nullptr, nullptr).empty());
}

TEST(Rfk_Database_getFileLevelEnumsByPredicate, ThrowingPredicate)
{
	auto predicate = [](rfk::Enum const&, void*) -> bool
	{
		throw std::logic_error("Error");
	};

	EXPECT_THROW(rfk::getDatabase().getFileLevelEnumsByPredicate(predicate, nullptr), std::logic_error);
}

TEST(Rfk_Database_getFileLevelEnumsByPredicate, FindingPredicate)
{
	char const* propName = "TestDabataseProperty";
	auto predicate = [](rfk::Enum const& n, void* userData) -> bool
	{
		return n.getPropertyByName(*reinterpret_cast<char const**>(userData)) != nullptr;
	};

	EXPECT_EQ(rfk::getDatabase().getFileLevelEnumsByPredicate(predicate, &propName).size(), 2u);
}

TEST(Rfk_Database_getFileLevelEnumsByPredicate, NonFindingPredicate)
{
	char const* propName = "NonExistantProperty";
	auto predicate = [](rfk::Enum const& n, void* userData) -> bool
	{
		return n.getPropertyByName(*reinterpret_cast<char const**>(userData)) != nullptr;
	};

	EXPECT_TRUE(rfk::getDatabase().getFileLevelEnumsByPredicate(predicate, &propName).empty());
}

//=========================================================
// Database::foreachFileLevelEnum / getFileLevelEnumsCount
//=========================================================

TEST(Rfk_Database_foreachFileLevelEnum_getFileLevelEnumsCount, NullptrVisitor)
{
	EXPECT_FALSE(rfk::getDatabase().foreachFileLevelEnum(nullptr, nullptr));
}

TEST(Rfk_Database_foreachFileLevelEnum_getFileLevelEnumsCount, ThrowingVisitor)
{
	auto visitor = [](rfk::Enum const&, void*) -> bool
	{
		throw std::logic_error("Error");
	};

	EXPECT_THROW(rfk::getDatabase().foreachFileLevelEnum(visitor, nullptr), std::logic_error);
}

TEST(Rfk_Database_foreachFileLevelEnum_getFileLevelEnumsCount, CompleteLoop)
{
	int counter = 0;
	auto visitor = [](rfk::Enum const&, void* data)
	{
		int& counter = *reinterpret_cast<int*>(data);
		counter++;

		return true;
	};

	EXPECT_TRUE(rfk::getDatabase().foreachFileLevelEnum(visitor, &counter));
	EXPECT_EQ(counter, rfk::getDatabase().getFileLevelEnumsCount());
}

TEST(Rfk_Database_foreachFileLevelEnum_getFileLevelEnumsCount, BreakingLoop)
{
	int counter = 0;
	auto visitor = [](rfk::Enum const&, void* data)
	{
		int& counter = *reinterpret_cast<int*>(data);
		counter++;

		return false;
	};

	EXPECT_FALSE(rfk::getDatabase().foreachFileLevelEnum(visitor, &counter));
	EXPECT_EQ(counter, 1u);
}

//=========================================================
//======== Database::getFundamentalArchetypeById ==========
//=========================================================

TEST(Rfk_Database_getFundamentalArchetypeById, FundamentalArchetypeId)
{
	EXPECT_NE(rfk::getDatabase().getFundamentalArchetypeById(rfk::getArchetype<int>()->getId()), nullptr);
}

TEST(Rfk_Database_getFundamentalArchetypeById, NonFundamentalArchetypeId)
{
	EXPECT_EQ(rfk::getDatabase().getFundamentalArchetypeById(FileLevelClass::staticGetArchetype().getId()), nullptr);
	EXPECT_EQ(rfk::getDatabase().getFundamentalArchetypeById(FileLevelStruct::staticGetArchetype().getId()), nullptr);
	EXPECT_EQ(rfk::getDatabase().getFundamentalArchetypeById(rfk::getEnum<FileLevelEnum>()->getId()), nullptr);
}

//=========================================================
//======= Database::getFundamentalArchetypeByName =========
//=========================================================

TEST(Rfk_Database_getFundamentalArchetypeByName, FundamentalArchetypeName)
{
	EXPECT_NE(rfk::getDatabase().getFundamentalArchetypeByName("int"), nullptr);
	EXPECT_NE(rfk::getDatabase().getFundamentalArchetypeByName("void"), nullptr);
	EXPECT_NE(rfk::getDatabase().getFundamentalArchetypeByName("char"), nullptr);
}

TEST(Rfk_Database_getFundamentalArchetypeByName, NonFundamentalArchetypeName)
{
	EXPECT_EQ(rfk::getDatabase().getFundamentalArchetypeByName("FileLevelClass"), nullptr);
	EXPECT_EQ(rfk::getDatabase().getFundamentalArchetypeByName("FileLevelStruct"), nullptr);
	EXPECT_EQ(rfk::getDatabase().getFundamentalArchetypeByName("FileLevelEnum"), nullptr);
}

//=========================================================
//============== Database::getVariableById ================
//=========================================================

