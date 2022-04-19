#include <gtest/gtest.h>
#include <Refureku/Refureku.h>

#include "TestNestedEnums.h"

//=========================================================
//============= rfk::getArchetype<NestedEnum> =============
//=========================================================

TEST(Rfk_GetArchetype_NestedEnums, NonNestedEnum_PublicNestedEnumLvl1)
{
	EXPECT_EQ(rfk::getArchetype<NonNestedEnum::PublicEnumNestedLvl1>(), NestedEnumInspector::getPublicEnumNestedLvl1Archetype());
	EXPECT_EQ(rfk::getArchetype<NonNestedEnum::PublicEnumNestedLvl1>(), rfk::getEnum<NonNestedEnum::PublicEnumNestedLvl1>());
}

TEST(Rfk_GetArchetype_NestedEnums, NonNestedEnum_ProtectedNestedEnumLvl1)
{
	EXPECT_NE(NestedEnumInspector::getProtectedEnumNestedLvl1Archetype(), nullptr);
}

TEST(Rfk_GetArchetype_NestedEnums, NonNestedEnum_PrivateNestedClassLvl1_PrivateNestedEnumLvl2)
{
	EXPECT_NE(NestedEnumInspector::getPrivateClassNestedLvl1_PrivateEnumNestedLvl2_Archetype(), nullptr);
}

TEST(Rfk_GetArchetype_NestedEnums, NonNestedEnum_PrivateNestedClassLvl1_ProtectedNestedEnumLvl2)
{
	EXPECT_NE(NestedEnumInspector::getPrivateClassNestedLvl1_ProtectedEnumNestedLvl2_Archetype(), nullptr);
}

TEST(Rfk_GetArchetype_NestedEnums, NonNestedEnum_PrivateNestedClassLvl1_PublicNestedEnumLvl2)
{
	EXPECT_NE(NestedEnumInspector::getPrivateClassNestedLvl1_PublicEnumNestedLvl2_Archetype(), nullptr);
}

//=========================================================
//================ rfk::getEnum<NestedEnum> ===============
//=========================================================

TEST(Rfk_GetEnum_NestedEnums, NonNestedEnum_PublicNestedEnumLvl1)
{
	EXPECT_EQ(rfk::getEnum<NonNestedEnum::PublicEnumNestedLvl1>(), NestedEnumInspector::getPublicEnumNestedLvl1Enum());
}

TEST(Rfk_GetEnum_NestedEnums, NonNestedEnum_ProtectedNestedEnumLvl1)
{
	EXPECT_NE(NestedEnumInspector::getProtectedEnumNestedLvl1Enum(), nullptr);
}

TEST(Rfk_GetEnum_NestedEnums, NonNestedEnum_PrivateNestedClassLvl1_PrivateNestedEnumLvl2)
{
	EXPECT_NE(NestedEnumInspector::getPrivateClassNestedLvl1_PrivateEnumNestedLvl2_Enum(), nullptr);
}

TEST(Rfk_GetEnum_NestedEnums, NonNestedEnum_PrivateNestedClassLvl1_ProtectedNestedEnumLvl2)
{
	EXPECT_NE(NestedEnumInspector::getPrivateClassNestedLvl1_ProtectedEnumNestedLvl2_Enum(), nullptr);
}

TEST(Rfk_GetEnum_NestedEnums, NonNestedEnum_PrivateNestedClassLvl1_PublicNestedEnumLvl2)
{
	EXPECT_NE(NestedEnumInspector::getPrivateClassNestedLvl1_PublicEnumNestedLvl2_Enum(), nullptr);
}