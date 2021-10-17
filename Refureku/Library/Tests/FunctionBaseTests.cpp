#include <stdexcept>	//std::logic_error
#include <gtest/gtest.h>
#include <Refureku/Refureku.h>

#include "TestFunctions.h"
#include "ForwardDeclaredClass.h"

//=========================================================
//=========== FunctionBase::hasSameParameters =============
//=========================================================

TEST(Rfk_FunctionBase_hasSameParameters, DifferentParamCount)
{
	EXPECT_FALSE((rfk::getDatabase().getFunctionByName("func_return_singleParam")->hasSameParameters<>()));
	EXPECT_FALSE((rfk::getDatabase().getFunctionByName("func_return_singleParam")->hasSameParameters<int, int>()));
	EXPECT_FALSE((rfk::getDatabase().getFunctionByName("func_return_MultipleParams")->hasSameParameters<int>()));
	EXPECT_FALSE((rfk::getDatabase().getFunctionByName("func_return_MultipleParams")->hasSameParameters<int, int, int>()));
}

TEST(Rfk_FunctionBase_hasSameParameters, SameParamCountDifferentTypes)
{
	EXPECT_FALSE((rfk::getDatabase().getFunctionByName("func_return_singleParam")->hasSameParameters<float>()));
	EXPECT_FALSE((rfk::getDatabase().getFunctionByName("func_return_MultipleParams")->hasSameParameters<float, float>()));
}

TEST(Rfk_FunctionBase_hasSameParameters, SameParameters)
{
	EXPECT_TRUE((rfk::getDatabase().getFunctionByName("func_return_singleParam")->hasSameParameters<int>()));
	EXPECT_TRUE((rfk::getDatabase().getFunctionByName("func_return_MultipleParams")->hasSameParameters<int, int>()));
}

TEST(Rfk_FunctionBase_hasSameParameters, NoParameters)
{
	EXPECT_TRUE((rfk::getDatabase().getFunctionByName("func_noParam")->hasSameParameters<>()));
}

TEST(Rfk_FunctionBase_hasSameParameters, SameParametersWithUnreflectedTypes)
{
	EXPECT_TRUE((rfk::getDatabase().getFunctionByName("func_twoParamsNonReflected")->hasSameParameters<NonReflectedClass&, int>()));
}

TEST(Rfk_FunctionBase_hasSameParameters, SameParametersWithForwardDeclaredTypes)
{
	EXPECT_TRUE((rfk::getDatabase().getFunctionByName("func_return_oneParam_forwardDeclared")->hasSameParameters<ForwardDeclaredClass&>()));
}

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
	EXPECT_TRUE(func1->hasSameSignature(*func2));
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

TEST(Rfk_FunctionBase_getReturnType, Void)
{
	EXPECT_TRUE(rfk::getDatabase().getFunctionByName("func_noParam")->getReturnType() == rfk::getType<void>());
}

TEST(Rfk_FunctionBase_getReturnType, FundamentalType)
{
	EXPECT_TRUE(rfk::getDatabase().getFunctionByName("func_return_singleParam")->getReturnType() == rfk::getType<int>());
}

TEST(Rfk_FunctionBase_getReturnType, NonReflectedType)
{
	EXPECT_TRUE(rfk::getDatabase().getFunctionByName("func_returnNonReflected_noParam")->getReturnType() == rfk::getType<NonReflectedClass>());
}

TEST(Rfk_FunctionBase_getReturnType, ForwardDeclaredType)
{
	EXPECT_TRUE(rfk::getDatabase().getFunctionByName("func_return_oneParam_forwardDeclared")->getReturnType() == rfk::getType<ForwardDeclaredClass&>());
}

//=========================================================
//========== FunctionBase::getParametersCount =============
//=========================================================

TEST(Rfk_FunctionBase_getParametersCount, NoParam)
{
	EXPECT_EQ(rfk::getDatabase().getFunctionByName("func_noParam")->getParametersCount(), 0u);
}

TEST(Rfk_FunctionBase_getParametersCount, OneParam)
{
	EXPECT_EQ(rfk::getDatabase().getFunctionByName("func_return_singleParam")->getParametersCount(), 1u);
}

TEST(Rfk_FunctionBase_getParametersCount, TwoParams)
{
	EXPECT_EQ(rfk::getDatabase().getFunctionByName("func_return_MultipleParams")->getParametersCount(), 2u);
}

//=========================================================
//============ FunctionBase::getParameterAt ===============
//=========================================================

TEST(Rfk_FunctionBase_getParameterAt, CheckParamType)
{
	EXPECT_EQ(rfk::getDatabase().getFunctionByName("func_return_singleParam")->getParameterAt(0).getType(), rfk::getType<int>());
	EXPECT_EQ(rfk::getDatabase().getFunctionByName("func_twoParamsNonReflected")->getParameterAt(0).getType(), rfk::getType<NonReflectedClass&>());
	EXPECT_EQ(rfk::getDatabase().getFunctionByName("func_twoParamsNonReflected")->getParameterAt(1).getType(), rfk::getType<int>());
}

TEST(Rfk_FunctionBase_getParameterAt, CheckParamName)
{
	EXPECT_TRUE(rfk::getDatabase().getFunctionByName("func_return_singleParam")->getParameterAt(0).hasSameName("i"));
	EXPECT_TRUE(rfk::getDatabase().getFunctionByName("func_twoParamsNonReflected")->getParameterAt(0).hasSameName("param"));
	EXPECT_TRUE(rfk::getDatabase().getFunctionByName("func_twoParamsNonReflected")->getParameterAt(1).hasSameName("value"));
}

TEST(Rfk_FunctionBase_getParameterAt, CheckAnonymousParamName)
{
	EXPECT_TRUE(rfk::getDatabase().getFunctionByName("func_MultipleParams")->getParameterAt(0).hasSameName(""));
	EXPECT_TRUE(rfk::getDatabase().getFunctionByName("func_MultipleParams")->getParameterAt(1).hasSameName(""));
}

//=========================================================
//========== FunctionBase::getInternalFunction ============
//=========================================================

TEST(Rfk_FunctionBase_getInternalFunction, _)
{
	//No meant to be used by end user... but well it is possible
	EXPECT_NE(rfk::getDatabase().getFunctionByName("func_MultipleParams")->getInternalFunction(), nullptr);
}