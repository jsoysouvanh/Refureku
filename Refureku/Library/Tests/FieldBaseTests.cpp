#include <gtest/gtest.h>
#include <Refureku/Refureku.h>

#include "TestFieldBase.h"

//=========================================================
//=============== FieldBase::getOuterEntity ===============
//=========================================================

TEST(Rfk_FieldBase_getOuterEntity, OwnClassField)
{
	EXPECT_EQ(TestFieldBaseClass::staticGetArchetype().getFieldByName("publicInt")->getOuterEntity(), &TestFieldBaseClass::staticGetArchetype());
}

TEST(Rfk_FieldBase_getOuterEntity, InheritedField)
{
	rfk::Field const* field = TestFieldBaseClassChild::staticGetArchetype().getFieldByName("publicInt", rfk::EFieldFlags::Default, true);

	EXPECT_NE(field, nullptr);
	EXPECT_NE(field->getOuterEntity(), &TestFieldBaseClassChild::staticGetArchetype());
	EXPECT_EQ(field->getOuterEntity(), &TestFieldBaseClass::staticGetArchetype());
}

//=========================================================
//================= FieldBase::getAccess ==================
//=========================================================

TEST(Rfk_FieldBase_getAccess, PrivateField)
{
	EXPECT_EQ(TestFieldBaseClass::staticGetArchetype().getFieldByName("privateInt")->getAccess(), rfk::EAccessSpecifier::Private);
}

TEST(Rfk_FieldBase_getAccess, PrivateStaticField)
{
	EXPECT_EQ(TestFieldBaseClass::staticGetArchetype().getStaticFieldByName("privateStaticInt")->getAccess(), rfk::EAccessSpecifier::Private);
}

TEST(Rfk_FieldBase_getAccess, ProtectedField)
{
	EXPECT_EQ(TestFieldBaseClass::staticGetArchetype().getFieldByName("protectedInt")->getAccess(), rfk::EAccessSpecifier::Protected);
}

TEST(Rfk_FieldBase_getAccess, ProtectedStaticField)
{
	EXPECT_EQ(TestFieldBaseClass::staticGetArchetype().getStaticFieldByName("protectedStaticInt")->getAccess(), rfk::EAccessSpecifier::Protected);
}

TEST(Rfk_FieldBase_getAccess, PublicField)
{
	EXPECT_EQ(TestFieldBaseClass::staticGetArchetype().getFieldByName("publicInt")->getAccess(), rfk::EAccessSpecifier::Public);
}

TEST(Rfk_FieldBase_getAccess, PublicStaticField)
{
	EXPECT_EQ(TestFieldBaseClass::staticGetArchetype().getStaticFieldByName("publicStaticInt")->getAccess(), rfk::EAccessSpecifier::Public);
}

//=========================================================
//================== FieldBase::isStatic ==================
//=========================================================

TEST(Rfk_FieldBase_isStatic, NonStaticField)
{
	EXPECT_FALSE(TestFieldBaseClass::staticGetArchetype().getFieldByName("privateInt")->isStatic());
}

TEST(Rfk_FieldBase_isStatic, StaticField)
{
	EXPECT_TRUE(TestFieldBaseClass::staticGetArchetype().getStaticFieldByName("privateStaticInt")->isStatic());
}

//=========================================================
//================= FieldBase::isMutable ==================
//=========================================================

TEST(Rfk_FieldBase_isMutable, NonMutableField)
{
	EXPECT_FALSE(TestFieldBaseClass::staticGetArchetype().getFieldByName("privateInt")->isMutable());
}

TEST(Rfk_FieldBase_isMutable, MutableField)
{
	EXPECT_TRUE(TestFieldBaseClass::staticGetArchetype().getFieldByName("privateMutableInt")->isMutable());
}

TEST(Rfk_FieldBase_isMutable, StaticField)
{
	EXPECT_FALSE(TestFieldBaseClass::staticGetArchetype().getStaticFieldByName("privateStaticInt")->isMutable());
}

//=========================================================
//================== FieldBase::getOwner ==================
//=========================================================

TEST(Rfk_FieldBase_isMutable, OwnClassField)
{
	EXPECT_EQ(TestFieldBaseClass::staticGetArchetype().getFieldByName("publicInt")->getOwner(), &TestFieldBaseClass::staticGetArchetype());
}

TEST(Rfk_FieldBase_isMutable, InheritedField)
{
	rfk::Field const* field = TestFieldBaseClassChild::staticGetArchetype().getFieldByName("publicInt", rfk::EFieldFlags::Default, true);

	EXPECT_NE(field, nullptr);
	EXPECT_EQ(field->getOwner(), &TestFieldBaseClassChild::staticGetArchetype());
	EXPECT_NE(field->getOwner(), &TestFieldBaseClass::staticGetArchetype());
}