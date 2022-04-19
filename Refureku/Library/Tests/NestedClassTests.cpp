#include <gtest/gtest.h>
#include <Refureku/Refureku.h>

#include "TestNestedClasses.h"

//=========================================================
//============ NonNestedClass nested classes ==============
//=========================================================

TEST(Rfk_GetArchetype_NestedClasses, NonNestedClass_PublicNestedClassLvl1)
{
	EXPECT_EQ(&NonNestedClass::PublicClassNestedLvl1::staticGetArchetype(), rfk::getArchetype<NonNestedClass::PublicClassNestedLvl1>());
}

TEST(Rfk_GetArchetype_NestedClasses, NonNestedClass_ProtectedNestedClassLvl1)
{
	EXPECT_NE(NestedClassInspector::getProtectedClassNestedLvl1Archetype(), nullptr);
}

TEST(Rfk_GetArchetype_NestedClasses, NonNestedClass_PrivateNestedClassLvl1)
{
	EXPECT_NE(NestedClassInspector::getPrivateClassNestedLvl1Archetype(), nullptr);
}

//=========================================================
//= NonNestedClass::PrivateNestedClassLvl1 nested classes =
//=========================================================

TEST(Rfk_GetArchetype_NestedClasses, NonNestedClass_PrivateNestedClassLvl1_PrivateClassNestedLvl2)
{
	EXPECT_NE(NestedClassInspector::getPrivateClassNestedLvl1_PrivateClassNestedLvl2_Archetype(), nullptr);
}

TEST(Rfk_GetArchetype_NestedClasses, NonNestedClass_PrivateNestedClassLvl1_ProtectedClassNestedLvl2)
{
	EXPECT_NE(NestedClassInspector::getPrivateClassNestedLvl1_ProtectedClassNestedLvl2_Archetype(), nullptr);
}

TEST(Rfk_GetArchetype_NestedClasses, NonNestedClass_PrivateNestedClassLvl1_PublicClassNestedLvl2)
{
	EXPECT_NE(NestedClassInspector::getPrivateClassNestedLvl1_PublicClassNestedLvl2_Archetype(), nullptr);
}

//=========================================================
// NonNestedClass::ProtectedNestedClassLvl1 nested classes 
//=========================================================

TEST(Rfk_GetArchetype_NestedClasses, NonNestedClass_ProtectedNestedClassLvl1_PrivateClassNestedLvl2)
{
	EXPECT_NE(NestedClassInspector::getProtectedClassNestedLvl1_PrivateClassNestedLvl2_Archetype(), nullptr);
}

TEST(Rfk_GetArchetype_NestedClasses, NonNestedClass_ProtectedNestedClassLvl1_ProtectedClassNestedLvl2)
{
	EXPECT_NE(NestedClassInspector::getProtectedClassNestedLvl1_ProtectedClassNestedLvl2_Archetype(), nullptr);
}

TEST(Rfk_GetArchetype_NestedClasses, NonNestedClass_ProtectedNestedClassLvl1_PublicClassNestedLvl2)
{
	EXPECT_NE(NestedClassInspector::getProtectedClassNestedLvl1_PublicClassNestedLvl2_Archetype(), nullptr);
}