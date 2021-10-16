#include <stdexcept>	//std::logic_error

#include <gtest/gtest.h>
#include <Refureku/Refureku.h>

#include "TestStaticMethods.h"
#include "ForwardDeclaredClass.h"

//=========================================================
//================ StaticMethod::invoke ===================
//=========================================================

TEST(Rfk_StaticMethod_invoke, SuccessfullCall)
{
	EXPECT_EQ(TestStaticMethodClass::staticGetArchetype().getStaticMethodByName("returnIntNoParam")->invoke<int>(), 0);
	EXPECT_EQ(TestStaticMethodClass::staticGetArchetype().getStaticMethodByName("returnIntParamInt")->invoke<int>(42), 42);
}

TEST(Rfk_StaticMethod_invoke, ThrowingCall)
{
	EXPECT_THROW(TestStaticMethodClass::staticGetArchetype().getStaticMethodByName("throwing")->invoke(), std::logic_error);
}

//=========================================================
//============= StaticMethod::checkedInvoke ===============
//=========================================================

TEST(Rfk_StaticMethod_checkedInvoke, SuccessfullCall)
{
	EXPECT_EQ(TestStaticMethodClass::staticGetArchetype().getStaticMethodByName("returnIntNoParam")->checkedInvoke<int>(), 0);
	EXPECT_EQ(TestStaticMethodClass::staticGetArchetype().getStaticMethodByName("returnIntParamInt")->checkedInvoke<int>(42), 42);
}

TEST(Rfk_StaticMethod_checkedInvoke, ThrowReturnTypeMismatch)
{
	EXPECT_THROW(TestStaticMethodClass::staticGetArchetype().getStaticMethodByName("returnIntNoParam")->checkedInvoke<float>(), rfk::ReturnTypeMismatch);
}

TEST(Rfk_StaticMethod_checkedInvoke, ReturnNonReflectedType)
{
	NonReflectedClass nrc;

	//Calling with a different non-reflected type is not catched by the checked call
	EXPECT_NO_THROW(TestStaticMethodClass::staticGetArchetype().getStaticMethodByName("returnNonReflectedNoParam")->checkedInvoke<NonReflectedClass2&>(nrc));
	EXPECT_NO_THROW(TestStaticMethodClass::staticGetArchetype().getStaticMethodByName("returnNonReflectedNoParam")->checkedInvoke<NonReflectedClass&>(nrc));
}

TEST(Rfk_StaticMethod_checkedInvoke, ThrowArgCountMismatch)
{
	EXPECT_THROW(TestStaticMethodClass::staticGetArchetype().getStaticMethodByName("returnIntParamInt")->checkedInvoke<int>(1, 2), rfk::ArgCountMismatch);	//2 instead of 1
	EXPECT_THROW(TestStaticMethodClass::staticGetArchetype().getStaticMethodByName("noReturnNoParam")->checkedInvoke<void>(1), rfk::ArgCountMismatch);		//1 instead of 0
}

TEST(Rfk_StaticMethod_checkedInvoke, ThrowArgTypeMismatch)
{
	EXPECT_THROW(TestStaticMethodClass::staticGetArchetype().getStaticMethodByName("returnIntParamInt")->checkedInvoke<int>(1.0f), rfk::ArgTypeMismatch);	//float instead of int
}

TEST(Rfk_StaticMethod_checkedInvoke, CatchForwardDeclaredTypeMismatch)
{
	ForwardDeclaredClass fdc;
	float value;

	EXPECT_THROW(TestStaticMethodClass::staticGetArchetype().getStaticMethodByName("returnFwdClassParamFwdClass")->checkedInvoke<int&>(&fdc), rfk::ReturnTypeMismatch);
	EXPECT_THROW(TestStaticMethodClass::staticGetArchetype().getStaticMethodByName("returnFwdClassParamFwdClass")->checkedInvoke<ForwardDeclaredClass*>(value), rfk::ArgTypeMismatch);
	EXPECT_EQ(TestStaticMethodClass::staticGetArchetype().getStaticMethodByName("returnFwdClassParamFwdClass")->checkedInvoke<ForwardDeclaredClass*>(&fdc), &fdc);	//Normal call
}

TEST(Rfk_StaticMethod_checkedInvoke, NonReflectedTypeBypassArgTypeMismatch)
{
	NonReflectedClass nrc;

	EXPECT_NO_THROW(TestStaticMethodClass::staticGetArchetype().getStaticMethodByName("returnNonReflectedNoParam")->checkedInvoke<NonReflectedClass&>(nrc));
	EXPECT_EQ(nrc.i, 42);
}

TEST(Rfk_StaticMethod_checkedInvoke, ThrowingCall)
{
	EXPECT_THROW(TestStaticMethodClass::staticGetArchetype().getStaticMethodByName("throwing")->checkedInvoke(), std::logic_error);
}