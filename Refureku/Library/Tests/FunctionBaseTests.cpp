#include <stdexcept>	//std::logic_error
#include <gtest/gtest.h>
#include <Refureku/Refureku.h>

#include "TestFunctions.h"
#include "ForwardDeclaredClass.h"

//=========================================================
//=========== FunctionBase::hasSameParameters =============
//=========================================================

//=========================================================
//=========== FunctionBase::hasSameSignature ==============
//=========================================================

TEST(Rfk_FunctionBase_hasSamePrototype, DifferentReturnTypeDifferentParams)
{
	rfk::Function const* func1 = rfk::getDatabase().getFunctionByName("func_noParam");
	rfk::Function const* func2 = rfk::getDatabase().getFunctionByName("func_return_singleParam");

	EXPECT_NE(func1, nullptr);
	EXPECT_NE(func2, nullptr);
	EXPECT_FALSE(func1->hasSameSignature(*func2));
}

TEST(Rfk_FunctionBase_hasSamePrototype, DifferentReturnTypeSameParams)
{
	rfk::Function const* func1 = rfk::getDatabase().getFunctionByName("func_return_singleParam");
	rfk::Function const* func2 = rfk::getDatabase().getFunctionByName("func_singleParam");

	EXPECT_NE(func1, nullptr);
	EXPECT_NE(func2, nullptr);
	EXPECT_FALSE(func1->hasSameSignature(*func2));
}

TEST(Rfk_FunctionBase_hasSamePrototype, SameReturnTypeDifferentParams)
{
	rfk::Function const* func1 = rfk::getDatabase().getFunctionByName("func_return_MultipleParams");
	rfk::Function const* func2 = rfk::getDatabase().getFunctionByName("func_return_singleParam");

	EXPECT_NE(func1, nullptr);
	EXPECT_NE(func2, nullptr);
	EXPECT_FALSE(func1->hasSameSignature(*func2));
}

TEST(Rfk_FunctionBase_hasSamePrototype, SameReturnTypeSameParams)
{
	rfk::Function const* func1 = rfk::getDatabase().getFunctionByName("func_return_singleParam");
	rfk::Function const* func2 = rfk::getDatabase().getFunctionByName<int(int)>("func_overloaded");

	EXPECT_NE(func1, nullptr);
	EXPECT_NE(func2, nullptr);
	EXPECT_FALSE(func1->hasSameSignature(*func2));
}

TEST(Rfk_FunctionBase_hasSamePrototype, ReturnVoidNoParams)
{
	rfk::Function const* func1 = rfk::getDatabase().getFunctionByName("func_static_noParam");
	rfk::Function const* func2 = rfk::getDatabase().getFunctionByName("func_noParam");

	EXPECT_NE(func1, nullptr);
	EXPECT_NE(func2, nullptr);
	EXPECT_TRUE(func1->hasSameSignature(*func2));
}

TEST(Rfk_FunctionBase_hasSamePrototype, SamePrototypeWithNonReflectedTypes)
{
	rfk::Function const* func = rfk::getDatabase().getFunctionByName("func_returnNonReflected_noParam");

	EXPECT_NE(func, nullptr);
	EXPECT_TRUE(func->hasSameSignature(*func));
}

TEST(Rfk_FunctionBase_hasSamePrototype, SamePrototypeWithForwardDeclaredTypes)
{
	rfk::Function const* func = rfk::getDatabase().getFunctionByName("func_return_oneParam_forwardDeclared");

	EXPECT_NE(func, nullptr);
	EXPECT_TRUE(func->hasSameSignature(*func));
}

//=========================================================
//========== FunctionBase::hasSameSignature<> =============
//=========================================================

TEST(Rfk_FunctionBase_hasSamePrototypeTemplate, DifferentReturnTypeDifferentParams)
{
	EXPECT_FALSE((rfk::getDatabase().getFunctionByName("func_noParam")->hasSameSignature<int, int>()));
	EXPECT_FALSE((rfk::getDatabase().getFunctionByName("func_return_singleParam")->hasSameSignature<void>()));
}

TEST(Rfk_FunctionBase_hasSamePrototypeTemplate, DifferentReturnTypeSameParams)
{
	EXPECT_FALSE((rfk::getDatabase().getFunctionByName("func_noParam")->hasSameSignature<int>()));
	EXPECT_FALSE((rfk::getDatabase().getFunctionByName("func_return_singleParam")->hasSameSignature<void, int>()));
}

TEST(Rfk_FunctionBase_hasSamePrototypeTemplate, SameReturnTypeDifferentParams)
{
	EXPECT_FALSE((rfk::getDatabase().getFunctionByName("func_noParam")->hasSameSignature<void, int>()));
	EXPECT_FALSE((rfk::getDatabase().getFunctionByName("func_return_singleParam")->hasSameSignature<int>()));
}

TEST(Rfk_FunctionBase_hasSamePrototypeTemplate, SameReturnTypeSameParams)
{
	EXPECT_TRUE((rfk::getDatabase().getFunctionByName("func_noParam")->hasSameSignature<void>()));
	EXPECT_TRUE((rfk::getDatabase().getFunctionByName("func_return_singleParam")->hasSameSignature<int, int>()));
}

TEST(Rfk_FunctionBase_hasSamePrototypeTemplate, SamePrototypeWithNonReflectedTypes)
{
	EXPECT_TRUE((rfk::getDatabase().getFunctionByName("func_returnNonReflected_noParam")->hasSameSignature<NonReflectedClass>()));
}

TEST(Rfk_FunctionBase_hasSamePrototypeTemplate, SamePrototypeWithForwardDeclaredTypes)
{
	EXPECT_TRUE((rfk::getDatabase().getFunctionByName("func_return_oneParam_forwardDeclared")->hasSameSignature<ForwardDeclaredClass&, ForwardDeclaredClass&>()));
}

//=========================================================
//============= FunctionBase::getReturnType ===============
//=========================================================

//=========================================================
//============ FunctionBase::getParameterAt ===============
//=========================================================

//=========================================================
//========== FunctionBase::getParametersCount =============
//=========================================================

//=========================================================
//========== FunctionBase::getInternalFunction ============
//=========================================================