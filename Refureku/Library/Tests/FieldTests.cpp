#include <gtest/gtest.h>
#include <Refureku/Refureku.h>

#include "TestFields.h"

//=========================================================
//======== Check forward declared type archetype ==========
//=========================================================

TEST(Rfk_Field, ForwardDeclaredTypeArchetype)
{
	EXPECT_NE(TestFieldsClass::staticGetArchetype().getFieldByName("forwardDeclaredClassField")->getType().getArchetype(), nullptr);
}

//=========================================================
//========== Check non reflected type archetype ===========
//=========================================================

TEST(Rfk_Field, NonReflectedTypeArchetype)
{
	EXPECT_EQ(TestFieldsClass::staticGetArchetype().getFieldByName("nonReflectedClassField")->getType().getArchetype(), nullptr);
}

//=========================================================
//=================== Field::getPtr =======================
//=========================================================

TEST(Rfk_Field_getPtr, NonConstVariable)
{
	TestFieldsClass instance;

	EXPECT_NO_THROW(TestFieldsClass::staticGetArchetype().getFieldByName("intField")->getPtr(instance));
	EXPECT_NE(TestFieldsClass::staticGetArchetype().getFieldByName("intField")->getPtr(instance), nullptr);
}

TEST(Rfk_Field_getPtr, ConstVariable)
{
	TestFieldsClass instance;
	
	EXPECT_THROW(TestFieldsClass::staticGetArchetype().getFieldByName("constIntField")->getPtr(instance), rfk::ConstViolation);
}

TEST(Rfk_Field_getPtr, ThrowInvalidArchetype)
{
	TestFieldsUnrelatedClass instance;

	EXPECT_THROW(TestFieldsClass::staticGetArchetype().getFieldByName("constIntField")->getPtr(instance), rfk::InvalidArchetype);
}

TEST(Rfk_Field_getPtr, PointerFirstParentDownCastOnly)
{
	TestFieldsClassChild instance;

	EXPECT_EQ(TestFieldsClassChild::staticGetArchetype().getFieldByName("intField", rfk::EFieldFlags::Default, true)->getPtr(static_cast<TestFieldsClass&>(instance)), &instance.intField);
}

TEST(Rfk_Field_getPtr, PointerSecondParentDownCastOnly)
{
	TestFieldsClassChild instance;

	EXPECT_EQ(TestFieldsClassChild::staticGetArchetype().getFieldByName("intField2", rfk::EFieldFlags::Default, true)->getPtr(static_cast<TestFieldsClass2&>(instance)), &instance.intField2);
}

TEST(Rfk_Field_getPtr, PointerDownUpCast)
{
	TestFieldsClassChild instance;

	EXPECT_EQ(TestFieldsClassChild::staticGetArchetype().getFieldByName("intField", rfk::EFieldFlags::Default, true)->getPtr(static_cast<TestFieldsClass2&>(instance)), &instance.intField);
	EXPECT_EQ(TestFieldsClassChild::staticGetArchetype().getFieldByName("intField2", rfk::EFieldFlags::Default, true)->getPtr(static_cast<TestFieldsClass&>(instance)), &instance.intField2);
}

//=========================================================
//================= Field::getConstPtr ====================
//=========================================================

TEST(Rfk_Field_getConstPtr, NonConstVariable)
{
	TestFieldsClass instance;

	EXPECT_NO_THROW(TestFieldsClass::staticGetArchetype().getFieldByName("intField")->getConstPtr(instance));
	EXPECT_NE(TestFieldsClass::staticGetArchetype().getFieldByName("intField")->getConstPtr(instance), nullptr);
}

TEST(Rfk_Field_getConstPtr, ConstVariable)
{
	TestFieldsClass instance;

	EXPECT_NO_THROW(TestFieldsClass::staticGetArchetype().getFieldByName("constIntField")->getConstPtr(instance));
	EXPECT_NE(TestFieldsClass::staticGetArchetype().getFieldByName("constIntField")->getConstPtr(instance), nullptr);
}

TEST(Rfk_Field_getConstPtr, ThrowInvalidArchetype)
{
	TestFieldsUnrelatedClass instance;

	EXPECT_THROW(TestFieldsClass::staticGetArchetype().getFieldByName("constIntField")->getConstPtr(instance), rfk::InvalidArchetype);
}

TEST(Rfk_Field_getConstPtr, PointerFirstParentDownCastOnly)
{
	TestFieldsClassChild instance;

	EXPECT_EQ(TestFieldsClassChild::staticGetArchetype().getFieldByName("intField", rfk::EFieldFlags::Default, true)->getConstPtr(static_cast<TestFieldsClass&>(instance)), &instance.intField);
}

TEST(Rfk_Field_getConstPtr, PointerSecondParentDownCastOnly)
{
	TestFieldsClassChild instance;

	EXPECT_EQ(TestFieldsClassChild::staticGetArchetype().getFieldByName("intField2", rfk::EFieldFlags::Default, true)->getConstPtr(static_cast<TestFieldsClass2&>(instance)), &instance.intField2);
}

TEST(Rfk_Field_getConstPtr, PointerDownUpCast)
{
	TestFieldsClassChild instance;

	EXPECT_EQ(TestFieldsClassChild::staticGetArchetype().getFieldByName("intField", rfk::EFieldFlags::Default, true)->getConstPtr(static_cast<TestFieldsClass2&>(instance)), &instance.intField);
	EXPECT_EQ(TestFieldsClassChild::staticGetArchetype().getFieldByName("intField2", rfk::EFieldFlags::Default, true)->getConstPtr(static_cast<TestFieldsClass&>(instance)), &instance.intField2);
}

//=========================================================
//==================== Field::get<> =======================
//=========================================================

TEST(Rfk_Field_getTemplate, GetConstIntByValue)
{
	TestFieldsClass instance;

	EXPECT_EQ(TestFieldsClass::staticGetArchetype().getFieldByName("constIntField")->get<int>(instance), 314);
}

TEST(Rfk_Field_getTemplate, GetConstIntByConstLVRef)
{
	TestFieldsClass instance;

	EXPECT_EQ(TestFieldsClass::staticGetArchetype().getFieldByName("constIntField")->get<int const&>(instance), 314);
}

TEST(Rfk_Field_getTemplate, GetConstIntByNonConstLVRef)
{
	TestFieldsClass instance;

	EXPECT_THROW(TestFieldsClass::staticGetArchetype().getFieldByName("constIntField")->get<int&>(instance), rfk::ConstViolation);
}

TEST(Rfk_Field_getTemplate, GetConstIntByNonConstRVRef)
{
	TestFieldsClass instance;

	EXPECT_THROW(TestFieldsClass::staticGetArchetype().getFieldByName("constIntField")->get<int&&>(instance), rfk::ConstViolation);
}

TEST(Rfk_Field_getTemplate, GetConstIntByConstRVRef)
{
	TestFieldsClass instance;

	//Doesn't compile since const rvalue is an invalid type
	//EXPECT_THROW(TestFieldsClass::staticGetArchetype().getFieldByName("constIntField")->get<int const&&>(instance), rfk::ConstViolation);
}

TEST(Rfk_Field_getTemplate, GetIntByRVRef)
{
	TestFieldsClass instance;

	EXPECT_EQ(TestFieldsClass::staticGetArchetype().getFieldByName("intField")->get<int&&>(instance), instance.intField);	//True for int, not true for movable classes
}

TEST(Rfk_Field_getTemplate, GetTestClassByValue)
{
	TestFieldsClass instance;

	EXPECT_EQ(TestFieldsClass::staticGetArchetype().getFieldByName("testClassField")->get<TestClass>(instance), TestClass());
}

TEST(Rfk_Field_getTemplate, GetTestClassByConstValue)
{
	TestFieldsClass instance;

	EXPECT_EQ(TestFieldsClass::staticGetArchetype().getFieldByName("testClassField")->get<TestClass const>(instance), TestClass());
}

TEST(Rfk_Field_getTemplate, GetTestClassByLVRef)
{
	TestFieldsClass instance;

	EXPECT_EQ(&TestFieldsClass::staticGetArchetype().getFieldByName("testClassField")->get<TestClass&>(instance), &instance.testClassField);
}

TEST(Rfk_Field_getTemplate, GetTestClassByConstLVRef)
{
	TestFieldsClass instance;

	EXPECT_EQ(&TestFieldsClass::staticGetArchetype().getFieldByName("testClassField")->get<TestClass const&>(instance), &instance.testClassField);
}

TEST(Rfk_Field_getTemplate, ThrowInvalidArchetype)
{
	TestFieldsUnrelatedClass instance;

	EXPECT_THROW(TestFieldsClass::staticGetArchetype().getFieldByName("constIntField")->get<int>(instance), rfk::InvalidArchetype);
}

TEST(Rfk_Field_getTemplate, PointerFirstParentDownCastOnly)
{
	TestFieldsClassChild instance;

	EXPECT_EQ(TestFieldsClassChild::staticGetArchetype().getFieldByName("intField", rfk::EFieldFlags::Default, true)->get<int>(static_cast<TestFieldsClass&>(instance)), instance.intField);
}

TEST(Rfk_Field_getTemplate, PointerSecondParentDownCastOnly)
{
	TestFieldsClassChild instance;

	EXPECT_EQ(TestFieldsClassChild::staticGetArchetype().getFieldByName("intField2", rfk::EFieldFlags::Default, true)->get<int>(static_cast<TestFieldsClass2&>(instance)), instance.intField2);
}

TEST(Rfk_Field_getTemplate, PointerDownUpCast)
{
	TestFieldsClassChild instance;

	EXPECT_EQ(TestFieldsClassChild::staticGetArchetype().getFieldByName("intField", rfk::EFieldFlags::Default, true)->get<int>(static_cast<TestFieldsClass2&>(instance)), instance.intField);
	EXPECT_EQ(TestFieldsClassChild::staticGetArchetype().getFieldByName("intField2", rfk::EFieldFlags::Default, true)->get<int>(static_cast<TestFieldsClass&>(instance)), instance.intField2);
}

//=========================================================
//================= Field::getUnsafe<> ====================
//=========================================================

TEST(Rfk_Field_getUnsafeTemplate, GetConstIntByValue)
{
	TestFieldsClass instance;

	EXPECT_EQ(TestFieldsClass::staticGetArchetype().getFieldByName("constIntField")->getUnsafe<int>(&instance), 314);
}

TEST(Rfk_Field_getUnsafeTemplate, GetConstIntByConstLVRef)
{
	TestFieldsClass instance;

	EXPECT_EQ(TestFieldsClass::staticGetArchetype().getFieldByName("constIntField")->getUnsafe<int const&>(&instance), 314);
}

TEST(Rfk_Field_getUnsafeTemplate, GetConstIntByNonConstLVRef)
{
	TestFieldsClass instance;

	EXPECT_THROW(TestFieldsClass::staticGetArchetype().getFieldByName("constIntField")->getUnsafe<int&>(&instance), rfk::ConstViolation);
}

TEST(Rfk_Field_getUnsafeTemplate, GetConstIntByNonConstRVRef)
{
	TestFieldsClass instance;

	EXPECT_THROW(TestFieldsClass::staticGetArchetype().getFieldByName("constIntField")->getUnsafe<int&&>(&instance), rfk::ConstViolation);
}

TEST(Rfk_Field_getUnsafeTemplate, GetIntByRVRef)
{
	TestFieldsClass instance;

	EXPECT_EQ(TestFieldsClass::staticGetArchetype().getFieldByName("intField")->getUnsafe<int&&>(&instance), instance.intField);	//True for int, not true for movable classes
}

TEST(Rfk_Field_getUnsafeTemplate, GetTestClassByValue)
{
	TestFieldsClass instance;

	EXPECT_EQ(TestFieldsClass::staticGetArchetype().getFieldByName("testClassField")->getUnsafe<TestClass>(&instance), TestClass());
}

TEST(Rfk_Field_getUnsafeTemplate, GetTestClassByConstValue)
{
	TestFieldsClass instance;

	EXPECT_EQ(TestFieldsClass::staticGetArchetype().getFieldByName("testClassField")->getUnsafe<TestClass const>(&instance), TestClass());
}

TEST(Rfk_Field_getUnsafeTemplate, GetTestClassByLVRef)
{
	TestFieldsClass instance;

	EXPECT_EQ(&TestFieldsClass::staticGetArchetype().getFieldByName("testClassField")->getUnsafe<TestClass&>(&instance), &instance.testClassField);
}

TEST(Rfk_Field_getUnsafeTemplate, GetTestClassByConstLVRef)
{
	TestFieldsClass instance;

	EXPECT_EQ(&TestFieldsClass::staticGetArchetype().getFieldByName("testClassField")->getUnsafe<TestClass const&>(&instance), &instance.testClassField);
}

//=========================================================
//==================== Field::set<> =======================
//=========================================================

TEST(Rfk_Field_setTemplate, SetNonConstClassByConstLVRef)
{
	TestFieldsClass instance;
	ConstructionTrackedClass const c;

	TestFieldsClass::staticGetArchetype().getFieldByName("ctorTrackedClassField")->set(instance, c);

	EXPECT_TRUE(instance.ctorTrackedClassField.getCopyConstructed());
}

TEST(Rfk_Field_setTemplate, SetNonConstClassByNonConstLVRef)
{
	TestFieldsClass instance;
	ConstructionTrackedClass c;

	TestFieldsClass::staticGetArchetype().getFieldByName("ctorTrackedClassField")->set(instance, c);

	EXPECT_TRUE(instance.ctorTrackedClassField.getCopyConstructed());
}

TEST(Rfk_Field_setTemplate, SetNonConstClassByRValue)
{
	TestFieldsClass instance;
	TestFieldsClass::staticGetArchetype().getFieldByName("ctorTrackedClassField")->set(instance, ConstructionTrackedClass());

	EXPECT_TRUE(instance.ctorTrackedClassField.getMoveConstructed());
}

TEST(Rfk_Field_setTemplate, SetConstClassByConstLVRef)
{
	TestFieldsClass instance;
	ConstructionTrackedClass const c;

	EXPECT_THROW(TestFieldsClass::staticGetArchetype().getFieldByName("constCtorTrackedClassField")->set(instance, c), rfk::ConstViolation);
}

TEST(Rfk_Field_setTemplate, SetConstClassByNonConstLVRef)
{
	TestFieldsClass instance;
	ConstructionTrackedClass c;

	EXPECT_THROW(TestFieldsClass::staticGetArchetype().getFieldByName("constCtorTrackedClassField")->set(instance, c), rfk::ConstViolation);
}

TEST(Rfk_Field_setTemplate, SetConstClassByRValue)
{
	TestFieldsClass instance;

	EXPECT_THROW(TestFieldsClass::staticGetArchetype().getFieldByName("constCtorTrackedClassField")->set(instance, ConstructionTrackedClass()), rfk::ConstViolation);
}

TEST(Rfk_Field_setTemplate, ThrowInvalidArchetype)
{
	TestFieldsUnrelatedClass instance;

	EXPECT_THROW(TestFieldsClass::staticGetArchetype().getFieldByName("constIntField")->set<int>(instance, 100), rfk::InvalidArchetype);
}

TEST(Rfk_Field_setTemplate, PointerFirstParentDownCastOnly)
{
	TestFieldsClassChild instance;

	TestFieldsClassChild::staticGetArchetype().getFieldByName("intField", rfk::EFieldFlags::Default, true)->set<int>(static_cast<TestFieldsClass&>(instance), 100);

	EXPECT_EQ(instance.intField, 100);
}

TEST(Rfk_Field_setTemplate, PointerSecondParentDownCastOnly)
{
	TestFieldsClassChild instance;

	TestFieldsClassChild::staticGetArchetype().getFieldByName("intField2", rfk::EFieldFlags::Default, true)->set<int>(static_cast<TestFieldsClass2&>(instance), 100);

	EXPECT_EQ(instance.intField2, 100);
}

TEST(Rfk_Field_setTemplate, PointerDownUpCast)
{
	TestFieldsClassChild instance;

	TestFieldsClassChild::staticGetArchetype().getFieldByName("intField", rfk::EFieldFlags::Default, true)->set<int>(static_cast<TestFieldsClass2&>(instance), 100);
	TestFieldsClassChild::staticGetArchetype().getFieldByName("intField2", rfk::EFieldFlags::Default, true)->set<int>(static_cast<TestFieldsClass&>(instance), 101);

	EXPECT_EQ(instance.intField, 100);
	EXPECT_EQ(instance.intField2, 101);
}

//=========================================================
//================= Field::setUnsafe<> ====================
//=========================================================

TEST(Rfk_Field_setUnsafeTemplate, SetNonConstClassByConstLVRef)
{
	TestFieldsClass instance;
	ConstructionTrackedClass const c;

	TestFieldsClass::staticGetArchetype().getFieldByName("ctorTrackedClassField")->setUnsafe(&instance, c);

	EXPECT_TRUE(instance.ctorTrackedClassField.getCopyConstructed());
}

TEST(Rfk_Field_setUnsafeTemplate, SetNonConstClassByNonConstLVRef)
{
	TestFieldsClass instance;
	ConstructionTrackedClass c;

	TestFieldsClass::staticGetArchetype().getFieldByName("ctorTrackedClassField")->setUnsafe(&instance, c);

	EXPECT_TRUE(instance.ctorTrackedClassField.getCopyConstructed());
}

TEST(Rfk_Field_setUnsafeTemplate, SetNonConstClassByRValue)
{
	TestFieldsClass instance;
	TestFieldsClass::staticGetArchetype().getFieldByName("ctorTrackedClassField")->setUnsafe(&instance, ConstructionTrackedClass());

	EXPECT_TRUE(instance.ctorTrackedClassField.getMoveConstructed());
}

TEST(Rfk_Field_setUnsafeTemplate, SetConstClassByConstLVRef)
{
	TestFieldsClass instance;
	ConstructionTrackedClass const c;

	EXPECT_THROW(TestFieldsClass::staticGetArchetype().getFieldByName("constCtorTrackedClassField")->setUnsafe(&instance, c), rfk::ConstViolation);
}

TEST(Rfk_Field_setUnsafeTemplate, SetConstClassByNonConstLVRef)
{
	TestFieldsClass instance;
	ConstructionTrackedClass c;

	EXPECT_THROW(TestFieldsClass::staticGetArchetype().getFieldByName("constCtorTrackedClassField")->setUnsafe(&instance, c), rfk::ConstViolation);
}

TEST(Rfk_Field_setUnsafeTemplate, SetConstClassByRValue)
{
	TestFieldsClass instance;

	EXPECT_THROW(TestFieldsClass::staticGetArchetype().getFieldByName("constCtorTrackedClassField")->setUnsafe(&instance, ConstructionTrackedClass()), rfk::ConstViolation);
}

//=========================================================
//==================== Field::set =========================
//=========================================================

TEST(Rfk_Field_set, SetNonConstInt)
{
	rfk::Field const* field = TestFieldsClass::staticGetArchetype().getFieldByName("intField");
	int newValue = 2;

	TestFieldsClass instance;
	EXPECT_NE(field->getUnsafe<int>(&instance), newValue);

	field->set(instance, &newValue, sizeof(int));

	EXPECT_EQ(field->getUnsafe<int>(&instance), newValue);
}

TEST(Rfk_Field_set, SetConstInt)
{
	rfk::Field const* field = TestFieldsClass::staticGetArchetype().getFieldByName("constIntField");
	int newValue = 2;

	TestFieldsClass instance;
	EXPECT_NE(field->getUnsafe<int>(&instance), newValue);

	EXPECT_THROW(field->set(instance, &newValue, sizeof(int)), rfk::ConstViolation);
}

TEST(Rfk_Field_set, ThrowInvalidArchetype)
{
	TestFieldsUnrelatedClass instance;
	int newValue = 100;

	EXPECT_THROW(TestFieldsClass::staticGetArchetype().getFieldByName("constIntField")->set(instance, &newValue, sizeof(int)), rfk::InvalidArchetype);
}

TEST(Rfk_Field_set, PointerFirstParentDownCastOnly)
{
	TestFieldsClassChild instance;
	int newValue = 100;

	TestFieldsClassChild::staticGetArchetype().getFieldByName("intField", rfk::EFieldFlags::Default, true)->set(static_cast<TestFieldsClass&>(instance), &newValue, sizeof(int));

	EXPECT_EQ(instance.intField, 100);
}

TEST(Rfk_Field_set, PointerSecondParentDownCastOnly)
{
	TestFieldsClassChild instance;
	int newValue = 100;

	TestFieldsClassChild::staticGetArchetype().getFieldByName("intField2", rfk::EFieldFlags::Default, true)->set(static_cast<TestFieldsClass2&>(instance), &newValue, sizeof(int));

	EXPECT_EQ(instance.intField2, 100);
}

TEST(Rfk_Field_set, PointerDownUpCast)
{
	TestFieldsClassChild instance;
	int newValue = 100;
	int newValue2 = 101;

	TestFieldsClassChild::staticGetArchetype().getFieldByName("intField", rfk::EFieldFlags::Default, true)->set(static_cast<TestFieldsClass2&>(instance), &newValue, sizeof(int));
	TestFieldsClassChild::staticGetArchetype().getFieldByName("intField2", rfk::EFieldFlags::Default, true)->set(static_cast<TestFieldsClass&>(instance), &newValue2, sizeof(int));

	EXPECT_EQ(instance.intField, 100);
	EXPECT_EQ(instance.intField2, 101);
}

//=========================================================
//================= Field::setUnsafe ======================
//=========================================================

TEST(Rfk_Field_setUnsafe, SetNonConstInt)
{
	rfk::Field const* field = TestFieldsClass::staticGetArchetype().getFieldByName("intField");
	int newValue = 2;

	TestFieldsClass instance;
	EXPECT_NE(field->getUnsafe<int>(&instance), newValue);

	field->setUnsafe(&instance, &newValue, sizeof(int));

	EXPECT_EQ(field->getUnsafe<int>(&instance), newValue);
}

TEST(Rfk_Field_setUnsafe, SetConstInt)
{
	rfk::Field const* field = TestFieldsClass::staticGetArchetype().getFieldByName("constIntField");
	int newValue = 2;

	TestFieldsClass instance;
	EXPECT_NE(field->getUnsafe<int>(&instance), newValue);

	EXPECT_THROW(field->setUnsafe(&instance, &newValue, sizeof(int)), rfk::ConstViolation);
}