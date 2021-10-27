#include <stdexcept>	//std::logic_error
#include <gtest/gtest.h>
#include <Refureku/Refureku.h>

#include "TestFunctions.h"
#include "ForwardDeclaredClass.h"

//=========================================================
//============== FunctionTests Code Coverage ==============
//=========================================================

TEST(FunctionTests, CodeCoverage)
{
	EXPECT_NO_THROW(func_return_noParam());
	EXPECT_NO_THROW(func_static_noParam());
	EXPECT_NO_THROW(func_noParam());
	EXPECT_NO_THROW(func_return_singleParam(1));
	EXPECT_NO_THROW(func_return_MultipleParams(1, 2));
	EXPECT_NO_THROW(func_singleParam(1));
	EXPECT_NO_THROW(func_MultipleParams(1, 2));
	EXPECT_NO_THROW(func_overloaded());
	EXPECT_NO_THROW(func_overloaded(1));
	EXPECT_THROW(func_noParam_throwLogicError(), std::logic_error);
	EXPECT_NO_THROW(func_inline_noParam());
	EXPECT_NO_THROW(func_returnNonReflected_noParam());
	
	NonReflectedClass nrc;
	EXPECT_NO_THROW(func_twoParamsNonReflected(nrc, 1));

	ForwardDeclaredClass fdc;
	EXPECT_NO_THROW(func_return_oneParam_forwardDeclared(fdc));
}

//=========================================================
//==================== rfk::getFunction ===================
//=========================================================

TEST(Rfk_getFunction, NonReflectedFunction)
{
	EXPECT_EQ(rfk::getFunction<&non_reflected_function>(), nullptr);
}

TEST(Rfk_getFunction, ExternFunction)
{
	EXPECT_NE(rfk::getFunction<&func_noParam_throwLogicError>(), nullptr);
}

TEST(Rfk_getFunction, StaticFunction)
{
	EXPECT_NE(rfk::getFunction<&func_static_noParam>(), nullptr);
}

TEST(Rfk_getFunction, InlineFunction)
{
	EXPECT_NE(rfk::getFunction<&func_inline_noParam>(), nullptr);
}

//=========================================================
//================= Function::isInline ====================
//=========================================================

TEST(Rfk_Function_isInline, Inline)
{
	EXPECT_TRUE(rfk::getDatabase().getFileLevelFunctionByName("func_inline_noParam")->isInline());
}

TEST(Rfk_Function_isInline, NotInline)
{
	EXPECT_FALSE(rfk::getDatabase().getFileLevelFunctionByName("func_noParam")->isInline());
}

//=========================================================
//================= Function::isStatic ====================
//=========================================================

TEST(Rfk_Function_isStatic, Static)
{
	EXPECT_TRUE(rfk::getDatabase().getFileLevelFunctionByName("func_static_noParam")->isStatic());
}

TEST(Rfk_Function_isStatic, NotStatic)
{
	EXPECT_FALSE(rfk::getDatabase().getFileLevelFunctionByName("func_return_noParam")->isStatic());
}

//=========================================================
//================== Function::invoke =====================
//=========================================================

TEST(Rfk_Function_invoke, SuccessfullCall)
{
	EXPECT_EQ(rfk::getDatabase().getFileLevelFunctionByName<int()>("func_overloaded")->invoke<int>(), 0);
	EXPECT_EQ(rfk::getDatabase().getFileLevelFunctionByName("func_return_singleParam")->invoke<int>(42), 42);
}

TEST(Rfk_Function_invoke, ThrowingCall)
{
	EXPECT_THROW(rfk::getDatabase().getFileLevelFunctionByName("func_noParam_throwLogicError")->invoke(), std::logic_error);
}

//=========================================================
//=============== Function::checkedInvoke =================
//=========================================================

TEST(Rfk_Function_checkedInvoke, SuccessfullCall)
{
	EXPECT_EQ(rfk::getDatabase().getFileLevelFunctionByName<int()>("func_overloaded")->checkedInvoke<int>(), 0);
	EXPECT_EQ(rfk::getDatabase().getFileLevelFunctionByName("func_return_singleParam")->checkedInvoke<int>(42), 42);
}

TEST(Rfk_Function_checkedInvoke, ThrowReturnTypeMismatch)
{
	EXPECT_THROW(rfk::getDatabase().getFileLevelFunctionByName("func_return_singleParam")->checkedInvoke(), rfk::ReturnTypeMismatch);
}

TEST(Rfk_Function_checkedInvoke, ReturnNonReflectedType)
{
	//Calling with a different non-reflected type is not catched by the checked call
	EXPECT_NO_THROW(rfk::getDatabase().getFileLevelFunctionByName("func_returnNonReflected_noParam")->checkedInvoke<NonReflectedClass2>());
	EXPECT_NO_THROW(rfk::getDatabase().getFileLevelFunctionByName("func_returnNonReflected_noParam")->checkedInvoke<NonReflectedClass>());
}

TEST(Rfk_Function_checkedInvoke, ThrowArgCountMismatch)
{
	EXPECT_THROW(rfk::getDatabase().getFileLevelFunctionByName("func_singleParam")->checkedInvoke<void>(1, 2), rfk::ArgCountMismatch);	//2 instead of 1
	EXPECT_THROW(rfk::getDatabase().getFileLevelFunctionByName("func_noParam")->checkedInvoke<void>(1), rfk::ArgCountMismatch);	//1 instead of 0
}

TEST(Rfk_Function_checkedInvoke, ThrowArgTypeMismatch)
{
	EXPECT_THROW(rfk::getDatabase().getFileLevelFunctionByName("func_singleParam")->checkedInvoke<void>(1.0f), rfk::ArgTypeMismatch);	//float instead of int
}

TEST(Rfk_Function_checkedInvoke, CatchForwardDeclaredTypeMismatch)
{
	ForwardDeclaredClass fdc;
	float value;

	EXPECT_THROW(rfk::getDatabase().getFileLevelFunctionByName("func_return_oneParam_forwardDeclared")->checkedInvoke<int&>(fdc), rfk::ReturnTypeMismatch);
	EXPECT_THROW(rfk::getDatabase().getFileLevelFunctionByName("func_return_oneParam_forwardDeclared")->checkedInvoke<ForwardDeclaredClass&>(value), rfk::ArgTypeMismatch);
	EXPECT_EQ(&rfk::getDatabase().getFileLevelFunctionByName("func_return_oneParam_forwardDeclared")->checkedInvoke<ForwardDeclaredClass&>(fdc), &fdc);	//Normal call
}

TEST(Rfk_Function_checkedInvoke, NonReflectedTypeBypassArgTypeMismatch)
{
	NonReflectedClass nrc;

	EXPECT_NO_THROW(rfk::getDatabase().getFileLevelFunctionByName("func_twoParamsNonReflected")->checkedInvoke<void>(nrc, 42));
	EXPECT_EQ(nrc.i, 42);
}

TEST(Rfk_Function_checkedInvoke, ThrowingCall)
{
	EXPECT_THROW(rfk::getDatabase().getFileLevelFunctionByName("func_noParam_throwLogicError")->checkedInvoke(), std::logic_error);
}