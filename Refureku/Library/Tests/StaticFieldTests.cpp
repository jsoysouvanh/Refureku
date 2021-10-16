#include <gtest/gtest.h>
#include <Refureku/Refureku.h>

#include "TestStaticFields.h"

//=========================================================
//======== Check forward declared type archetype ==========
//=========================================================

TEST(Rfk_StaticField, ForwardDeclaredTypeArchetype)
{
	EXPECT_NE(TestStaticFieldsClass::staticGetArchetype().getStaticFieldByName("forwardDeclaredClassField")->getType().getArchetype(), nullptr);
}

//=========================================================
//========== Check non reflected type archetype ===========
//=========================================================

TEST(Rfk_StaticField, NonReflectedTypeArchetype)
{
	EXPECT_EQ(TestStaticFieldsClass::staticGetArchetype().getStaticFieldByName("nonReflectedClassField")->getType().getArchetype(), nullptr);
}

//=========================================================
//================ StaticField::getPtr ====================
//=========================================================

TEST(Rfk_StaticField_getPtr, NonConstVariable)
{
	EXPECT_NO_THROW(TestStaticFieldsClass::staticGetArchetype().getStaticFieldByName("intField")->getPtr());
	EXPECT_NE(TestStaticFieldsClass::staticGetArchetype().getStaticFieldByName("intField")->getPtr(), nullptr);
}

TEST(Rfk_StaticField_getPtr, ConstVariable)
{
	EXPECT_THROW(TestStaticFieldsClass::staticGetArchetype().getStaticFieldByName("constIntField")->getPtr(), rfk::ConstViolation);
}

//=========================================================
//============== StaticField::getConstPtr =================
//=========================================================

TEST(Rfk_StaticField_getConstPtr, NonConstVariable)
{
	EXPECT_NO_THROW(TestStaticFieldsClass::staticGetArchetype().getStaticFieldByName("intField")->getConstPtr());
	EXPECT_NE(TestStaticFieldsClass::staticGetArchetype().getStaticFieldByName("intField")->getConstPtr(), nullptr);
}

TEST(Rfk_StaticField_getConstPtr, ConstVariable)
{
	EXPECT_NO_THROW(TestStaticFieldsClass::staticGetArchetype().getStaticFieldByName("constIntField")->getConstPtr());
	EXPECT_NE(TestStaticFieldsClass::staticGetArchetype().getStaticFieldByName("constIntField")->getConstPtr(), nullptr);
}

//=========================================================
//================== StaticField::get<> ======================
//=========================================================

TEST(Rfk_StaticField_getTemplate, GetConstIntByValue)
{
	EXPECT_EQ(TestStaticFieldsClass::staticGetArchetype().getStaticFieldByName("constIntField")->get<int>(), 314);
}

TEST(Rfk_StaticField_getTemplate, GetConstIntByConstLVRef)
{
	EXPECT_EQ(TestStaticFieldsClass::staticGetArchetype().getStaticFieldByName("constIntField")->get<int const&>(), 314);
}

TEST(Rfk_StaticField_getTemplate, GetConstIntByNonConstLVRef)
{
	EXPECT_THROW(TestStaticFieldsClass::staticGetArchetype().getStaticFieldByName("constIntField")->get<int&>(), rfk::ConstViolation);
}

TEST(Rfk_StaticField_getTemplate, GetConstIntByNonConstRVRef)
{
	EXPECT_THROW(TestStaticFieldsClass::staticGetArchetype().getStaticFieldByName("constIntField")->get<int&&>(), rfk::ConstViolation);
}

TEST(Rfk_StaticField_getTemplate, GetConstIntByConstRVRef)
{
	//Doesn't compile since const rvalue is an invalid type
	//EXPECT_THROW(TestStaticFieldsClass::staticGetArchetype().getStaticFieldByName("constIntField")->get<int const&&>(), rfk::ConstViolation);
}

TEST(Rfk_StaticField_getTemplate, GetIntByRVRef)
{
	EXPECT_EQ(TestStaticFieldsClass::staticGetArchetype().getStaticFieldByName("intField")->get<int&&>(), TestStaticFieldsClass::intField);
}

TEST(Rfk_StaticField_getTemplate, GetTestClassByValue)
{
	EXPECT_EQ(TestStaticFieldsClass::staticGetArchetype().getStaticFieldByName("testClassField")->get<TestClass>(), TestClass());
}

TEST(Rfk_StaticField_getTemplate, GetTestClassByConstValue)
{
	EXPECT_EQ(TestStaticFieldsClass::staticGetArchetype().getStaticFieldByName("testClassField")->get<TestClass const>(), TestClass());
}

TEST(Rfk_StaticField_getTemplate, GetTestClassByLVRef)
{
	EXPECT_EQ(&TestStaticFieldsClass::staticGetArchetype().getStaticFieldByName("testClassField")->get<TestClass&>(), &TestStaticFieldsClass::testClassField);
}

TEST(Rfk_StaticField_getTemplate, GetTestClassByConstLVRef)
{
	EXPECT_EQ(&TestStaticFieldsClass::staticGetArchetype().getStaticFieldByName("testClassField")->get<TestClass const&>(), &TestStaticFieldsClass::testClassField);
}

//=========================================================
//=================== StaticField::set<> ======================
//=========================================================

TEST(Rfk_StaticField_setTemplate, SetNonConstClassByConstLVRef)
{
	ConstructionTrackedClass const c;

	TestStaticFieldsClass::staticGetArchetype().getStaticFieldByName("ctorTrackedClassField")->set(c);

	EXPECT_TRUE(TestStaticFieldsClass::ctorTrackedClassField.getCopyConstructed());
}

TEST(Rfk_StaticField_setTemplate, SetNonConstClassByNonConstLVRef)
{
	ConstructionTrackedClass c;

	TestStaticFieldsClass::staticGetArchetype().getStaticFieldByName("ctorTrackedClassField")->set(c);

	EXPECT_TRUE(TestStaticFieldsClass::ctorTrackedClassField.getCopyConstructed());
}

TEST(Rfk_StaticField_setTemplate, SetNonConstClassByRValue)
{
	TestStaticFieldsClass::staticGetArchetype().getStaticFieldByName("ctorTrackedClassField")->set(ConstructionTrackedClass());

	EXPECT_TRUE(TestStaticFieldsClass::ctorTrackedClassField.getMoveConstructed());
}

TEST(Rfk_StaticField_setTemplate, SetConstClassByConstLVRef)
{
	ConstructionTrackedClass const c;

	EXPECT_THROW(TestStaticFieldsClass::staticGetArchetype().getStaticFieldByName("constCtorTrackedClassField")->set(c), rfk::ConstViolation);
}

TEST(Rfk_StaticField_setTemplate, SetConstClassByNonConstLVRef)
{
	ConstructionTrackedClass c;

	EXPECT_THROW(TestStaticFieldsClass::staticGetArchetype().getStaticFieldByName("constCtorTrackedClassField")->set(c), rfk::ConstViolation);
}

TEST(Rfk_StaticField_setTemplate, SetConstClassByRValue)
{
	EXPECT_THROW(TestStaticFieldsClass::staticGetArchetype().getStaticFieldByName("constCtorTrackedClassField")->set(ConstructionTrackedClass()), rfk::ConstViolation);
}

//=========================================================
//================= StaticField::set ======================
//=========================================================

TEST(Rfk_StaticField_set, SetNonConstInt)
{
	rfk::StaticField const* field = TestStaticFieldsClass::staticGetArchetype().getStaticFieldByName("intField");
	int newValue = 2;

	EXPECT_NE(field->get<int>(), newValue);

	field->set(&newValue, sizeof(int));

	EXPECT_EQ(field->get<int>(), newValue);
}

TEST(Rfk_StaticField_set, SetConstInt)
{
	rfk::StaticField const* field = TestStaticFieldsClass::staticGetArchetype().getStaticFieldByName("constIntField");
	int newValue = 2;

	EXPECT_NE(field->get<int>(), newValue);

	EXPECT_THROW(field->set(&newValue, sizeof(int)), rfk::ConstViolation);
}