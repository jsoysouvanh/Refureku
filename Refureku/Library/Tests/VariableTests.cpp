#include <gtest/gtest.h>
#include <Refureku/Refureku.h>

#include "TestVariables.h"
#include "ForwardDeclaredClass.h"

//=========================================================
//================= Function::isStatic ====================
//=========================================================

TEST(Rfk_Variable_isStatic, Static)
{
	EXPECT_TRUE(rfk::getDatabase().getFileLevelVariableByName("var_global_static")->isStatic());
}

TEST(Rfk_Variable_isStatic, NonStatic)
{
	EXPECT_FALSE(rfk::getDatabase().getFileLevelVariableByName("var_global_extern")->isStatic());
}

//=========================================================
//================== Variable::getPtr =====================
//=========================================================

TEST(Rfk_Variable_getPtr, NonConstVariable)
{
	EXPECT_NO_THROW(rfk::getDatabase().getFileLevelVariableByName("var_global_extern")->getPtr());
}

TEST(Rfk_Variable_getPtr, ConstVariable)
{
	EXPECT_THROW(rfk::getDatabase().getFileLevelVariableByName("var_global_extern_const")->getPtr(), rfk::ConstViolation);
}

//=========================================================
//=============== Variable::getConstPtr ===================
//=========================================================

TEST(Rfk_Variable_getConstPtr, NonConstVariable)
{
	EXPECT_NO_THROW(rfk::getDatabase().getFileLevelVariableByName("var_global_extern")->getConstPtr());
}

TEST(Rfk_Variable_getConstPtr, ConstVariable)
{
	EXPECT_NO_THROW(rfk::getDatabase().getFileLevelVariableByName("var_global_extern_const")->getConstPtr());
}

//=========================================================
//================== Variable::get<> ======================
//=========================================================

TEST(Rfk_Variable_getTemplate, GetConstIntByValue)
{
	EXPECT_EQ(rfk::getDatabase().getFileLevelVariableByName("var_global_extern_const")->get<int>(), 42);
}

TEST(Rfk_Variable_getTemplate, GetConstIntByConstLVRef)
{
	EXPECT_EQ(rfk::getDatabase().getFileLevelVariableByName("var_global_extern_const")->get<int const&>(), 42);
}

TEST(Rfk_Variable_getTemplate, GetConstIntByNonConstLVRef)
{
	EXPECT_THROW(rfk::getDatabase().getFileLevelVariableByName("var_global_extern_const")->get<int&>(), rfk::ConstViolation);
}

TEST(Rfk_Variable_getTemplate, GetConstIntByNonConstRVRef)
{
	EXPECT_THROW(rfk::getDatabase().getFileLevelVariableByName("var_global_extern_const")->get<int&&>(), rfk::ConstViolation);
}

TEST(Rfk_Variable_getTemplate, GetConstIntByConstRVRef)
{
	//Doesn't compile since const rvalue is an invalid type
	//EXPECT_THROW(rfk::getDatabase().getFileLevelVariableByName("var_global_extern_const")->get<int const&&>(), rfk::ConstViolation);
}

TEST(Rfk_Variable_getTemplate, GetIntByRVRef)
{
	EXPECT_EQ(rfk::getDatabase().getFileLevelVariableByName("var_global_static")->get<int&&>(), var_global_static);
}

TEST(Rfk_Variable_getTemplate, GetTestClassByValue)
{
	EXPECT_EQ(rfk::getDatabase().getFileLevelVariableByName("var_global_extern")->get<TestClass>(), TestClass());
}

TEST(Rfk_Variable_getTemplate, GetTestClassByConstValue)
{
	EXPECT_EQ(rfk::getDatabase().getFileLevelVariableByName("var_global_extern")->get<TestClass const>(), TestClass());
}

TEST(Rfk_Variable_getTemplate, GetTestClassByLVRef)
{
	EXPECT_EQ(&rfk::getDatabase().getFileLevelVariableByName("var_global_extern")->get<TestClass&>(), &var_global_extern);
}

TEST(Rfk_Variable_getTemplate, GetTestClassByConstLVRef)
{
	EXPECT_EQ(&rfk::getDatabase().getFileLevelVariableByName("var_global_extern")->get<TestClass const&>(), &var_global_extern);
}

//=========================================================
//=================== Variable::set<> ======================
//=========================================================

TEST(Rfk_Variable_setTemplate, SetNonConstClassByConstLVRef)
{
	ConstructionTrackedClass const c;

	rfk::getDatabase().getFileLevelVariableByName("var_global_extern_constructionTracked")->set(c);

	EXPECT_TRUE(var_global_extern_constructionTracked.getCopyConstructed());
}

TEST(Rfk_Variable_setTemplate, SetNonConstClassByNonConstLVRef)
{
	ConstructionTrackedClass c;

	rfk::getDatabase().getFileLevelVariableByName("var_global_extern_constructionTracked")->set(c);

	EXPECT_TRUE(var_global_extern_constructionTracked.getCopyConstructed());
}

TEST(Rfk_Variable_setTemplate, SetNonConstClassByRValue)
{
	rfk::getDatabase().getFileLevelVariableByName("var_global_extern_constructionTracked")->set(ConstructionTrackedClass());

	EXPECT_TRUE(var_global_extern_constructionTracked.getMoveConstructed());
}

TEST(Rfk_Variable_setTemplate, SetConstClassByConstLVRef)
{
	ConstructionTrackedClass const c;

	EXPECT_THROW(rfk::getDatabase().getFileLevelVariableByName("var_global_extern_const_constructionTracked")->set(c), rfk::ConstViolation);
}

TEST(Rfk_Variable_setTemplate, SetConstClassByNonConstLVRef)
{
	ConstructionTrackedClass c;

	EXPECT_THROW(rfk::getDatabase().getFileLevelVariableByName("var_global_extern_const_constructionTracked")->set(c), rfk::ConstViolation);
}

TEST(Rfk_Variable_setTemplate, SetConstClassByRValue)
{
	EXPECT_THROW(rfk::getDatabase().getFileLevelVariableByName("var_global_extern_const_constructionTracked")->set(ConstructionTrackedClass()), rfk::ConstViolation);
}

//=========================================================
//=================== Variable::set =======================
//=========================================================

TEST(Rfk_Variable_set, SetNonConstInt)
{
	int newValue = 2;

	EXPECT_NE(rfk::getDatabase().getFileLevelVariableByName("var_global_static")->get<int>(), newValue);

	rfk::getDatabase().getFileLevelVariableByName("var_global_static")->set(&newValue, sizeof(int));

	EXPECT_EQ(rfk::getDatabase().getFileLevelVariableByName("var_global_static")->get<int>(), newValue);
}

TEST(Rfk_Variable_set, SetConstInt)
{
	int newValue = 2;

	EXPECT_NE(rfk::getDatabase().getFileLevelVariableByName("var_global_extern_const")->get<int>(), newValue);

	EXPECT_THROW(rfk::getDatabase().getFileLevelVariableByName("var_global_extern_const")->set(&newValue, sizeof(int)), rfk::ConstViolation);
}