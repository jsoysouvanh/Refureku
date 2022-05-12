#include <stdexcept>	//std::logic_error

#include <gtest/gtest.h>
#include <Refureku/Refureku.h>

#include "TestMethods.h"
#include "ForwardDeclaredClass.h"

//=========================================================
//=================== Method::invoke ======================
//=========================================================

TEST(Rfk_Method_invoke, CallNonConstMethodOnNonConstInstance)
{
	TestMethodClass instance;

	EXPECT_EQ(TestMethodClass::staticGetArchetype().getMethodByName("returnIntNoParam")->invoke<int>(instance), 0);
	EXPECT_EQ(TestMethodClass::staticGetArchetype().getMethodByName("returnIntParamInt")->invoke<int>(instance, 42), 42);
}

TEST(Rfk_Method_invoke, CallNonConstMethodOnConstInstance)
{
	TestMethodClass const instance;

	EXPECT_THROW(TestMethodClass::staticGetArchetype().getMethodByName("returnIntNoParam")->invoke<int>(instance), rfk::ConstViolation);
	EXPECT_THROW(TestMethodClass::staticGetArchetype().getMethodByName("returnIntParamInt")->invoke<int>(instance, 42), rfk::ConstViolation);
}

TEST(Rfk_Method_invoke, CallConstMethodOnNonConstInstance)
{
	TestMethodClass instance;

	EXPECT_NO_THROW(TestMethodClass::staticGetArchetype().getMethodByName("constNoReturnNoParam")->invoke(instance));
}

TEST(Rfk_Method_invoke, CallConstMethodOnConstInstance)
{
	TestMethodClass const instance;

	EXPECT_NO_THROW(TestMethodClass::staticGetArchetype().getMethodByName("constNoReturnNoParam")->invoke(instance));
}

TEST(Rfk_Method_invoke, ThrowingCall)
{
	TestMethodClass instance;

	EXPECT_THROW(TestMethodClass::staticGetArchetype().getMethodByName("throwing")->invoke(instance), std::logic_error);
}

TEST(Rfk_Method_invoke, ThrowInvalidCaller)
{
	TestMethodClass2 instance;

	EXPECT_THROW(TestMethodClass::staticGetArchetype().getMethodByName("virtualNoReturnNoParam")->invoke(instance), rfk::InvalidArchetype);
}

//4. The virtual method is introduced by the second inherited class (and the first inherited class is polymorphic)
TEST(Rfk_Method_invoke, CallParentIntroducedVirtualMethodOnMultiplePInheritancePClass)
{
	MultiplePInheritancePClassMethodOverride instance;

	EXPECT_EQ(
		MultiplePInheritancePClassMethodOverride::staticGetArchetype().getMethodByName("methodNoInheritancePClass4", rfk::EMethodFlags::Default, true)
			->invoke<EMethodTestCallResult>(instance),
		EMethodTestCallResult::NoInheritancePClass
	);
}

//6. The virtual method is introduced by the second inherited class (and the first inherited class is polymorphic) and overriden by instance
//   AND the overriden version in instance is NOT reflected
TEST(Rfk_Method_invoke, CallParentIntroducedOverridenVirtualMethodOnMultiplePInheritancePClass)
{
	MultiplePInheritancePClassMethodOverride instance;

	EXPECT_EQ(
		MultiplePInheritancePClassMethodOverride::staticGetArchetype().getMethodByName("methodNoInheritancePClass", rfk::EMethodFlags::Default, true)
			->invoke<EMethodTestCallResult>(instance),
		EMethodTestCallResult::MultiplePInheritancePClassMethodOverride
	);
}

//6.2 The virtual method is introduced by the second inherited class (and the first inherited class is polymorphic) and overriden by instance
//    AND the overriden version in instance is reflected
TEST(Rfk_Method_invoke, CallParentIntroducedNonReflectedOverridenVirtualMethodOnMultiplePInheritancePClass)
{
	MultiplePInheritancePClassMethodOverride instance;

	EXPECT_EQ(
		MultiplePInheritancePClassMethodOverride::staticGetArchetype().getMethodByName("methodNoInheritancePClass2")
			->invoke<EMethodTestCallResult>(instance),
		EMethodTestCallResult::MultiplePInheritancePClassMethodOverride
	);
}

//7. The virtual method is introduced by a grandparent class (but in the first inheritance branch: virtual table offset = 0)
//   A<vmethod    B
//   ^            ^
//   |------------|
//		   |
//         C
//		   ^
//         D<instance
TEST(Rfk_Method_invoke, CallGrandParentIntroducedVirtualMethodFirstInheritanceBranch)
{
	SinglePInheritancePClassLevel2 instance;

	EXPECT_EQ(
		SinglePInheritancePClassLevel2::staticGetArchetype().getMethodByName("methodSinglePInheritancePClass", rfk::EMethodFlags::Default, true)
			->invoke<EMethodTestCallResult>(instance),
		EMethodTestCallResult::SinglePInheritancePClass
	);
}

//8. The virtual method is introduced by a grandparent class (but NOT in the first inheritance branch: virtual table offset != 0)
//   A            B<vmethod
//   ^            ^
//   |------------|
//		   |
//         C
//		   ^
//         D<instance
// We can't add this test since it is UB to call invokeUnsafe with invalid instance pointer (can't adjust the pointer).
TEST(Rfk_Method_invoke, CallGrandParentIntroducedVirtualMethodNotFirstInheritanceBranch)
{
	SinglePInheritancePClassLevel2 instance;

	EXPECT_EQ(
		SinglePInheritancePClassLevel2::staticGetArchetype().getMethodByName("methodNoInheritancePClass4", rfk::EMethodFlags::Default, true)
			->invoke<EMethodTestCallResult>(instance),
		EMethodTestCallResult::NoInheritancePClass
	);
}

//=========================================================
//================ Method::invokeUnsafe ===================
//=========================================================

//1. self class doesn't inherit from any class
TEST(Rfk_Method_invokeUnsafe, CallSelfIntroducedMethodOnNoInheritanceNPClass)
{
	NoInheritanceNPClass instance;
	
	EXPECT_EQ(
		NoInheritanceNPClass::staticGetArchetype().getMethodByName("methodNoInheritanceNPClass")->invokeUnsafe<EMethodTestCallResult>(&instance),
		EMethodTestCallResult::NoInheritanceNPClass
	);
}

//2. self class inherits from one non-polymorphic class
TEST(Rfk_Method_invokeUnsafe, CallSelfIntroducedMethodOnSingleNPInheritanceNPClass)
{
	SingleNPInheritanceNPClass instance;

	EXPECT_EQ(
		SingleNPInheritanceNPClass::staticGetArchetype().getMethodByName("methodSingleNPInheritanceNPClass")->invokeUnsafe<EMethodTestCallResult>(&instance),
		EMethodTestCallResult::SingleNPInheritanceNPClass
	);
}

//3. self class inherits from multiple non-polymorphic classes
TEST(Rfk_Method_invokeUnsafe, CallSelfIntroducedMethodOnMultipleNPInheritanceNPClass)
{
	MultipleNPInheritanceNPClass instance;

	EXPECT_EQ(
		MultipleNPInheritanceNPClass::staticGetArchetype().getMethodByName("methodMultipleNPInheritanceNPClass")->invokeUnsafe<EMethodTestCallResult>(&instance),
		EMethodTestCallResult::MultipleNPInheritanceNPClass
	);
}

//4. self class inherits from multiple classes including polymorphic classes
TEST(Rfk_Method_invokeUnsafe, CallSelfIntroducedMethodOnMultiplePInheritancePClass)
{
	MultiplePInheritancePClassMethodOverride instance;

	EXPECT_EQ(
		MultiplePInheritancePClassMethodOverride::staticGetArchetype().getMethodByName("methodMultiplePInheritancePClassMethodOverride")->invokeUnsafe<EMethodTestCallResult>(&instance),
		EMethodTestCallResult::MultiplePInheritancePClassMethodOverride
	);
}

//Call a virtual method from self class

//1. self class doesn't inherit from any class
TEST(Rfk_Method_invokeUnsafe, CallSelfIntroducedVirtualMethodOnNoInheritancePClass)
{
	NoInheritancePClass instance;

	EXPECT_EQ(
		NoInheritancePClass::staticGetArchetype().getMethodByName("methodNoInheritancePClass")->invokeUnsafe<EMethodTestCallResult>(&instance),
		EMethodTestCallResult::NoInheritancePClass
	);
}

//2. self class inherits from one non-polymorphic class
TEST(Rfk_Method_invokeUnsafe, CallSelfIntroducedVirtualMethodOnSingleNPInheritancePClass)
{
	SingleNPInheritancePClass instance;

	EXPECT_EQ(
		SingleNPInheritancePClass::staticGetArchetype().getMethodByName("methodSingleNPInheritancePClass")->invokeUnsafe<EMethodTestCallResult>(&instance),
		EMethodTestCallResult::SingleNPInheritancePClass
	);
}

//3. self class inherits from multiple non-polymorphic classes
TEST(Rfk_Method_invokeUnsafe, CallSelfIntroducedVirtualMethodOnMultipleNPInheritancePClass)
{
	MultipleNPInheritancePClass instance;

	EXPECT_EQ(
		MultipleNPInheritancePClass::staticGetArchetype().getMethodByName("methodMultipleNPInheritancePClass")->invokeUnsafe<EMethodTestCallResult>(&instance),
		EMethodTestCallResult::MultipleNPInheritancePClass
	);
}

//4. self class inherits from multiple classes including polymorphic classes
TEST(Rfk_Method_invokeUnsafe, CallSelfIntroducedVirtualMethodOnMultiplePInheritancePClass)
{
	MultiplePInheritancePClassMethodOverride instance;

	EXPECT_EQ(
		MultiplePInheritancePClassMethodOverride::staticGetArchetype().getMethodByName("methodMultiplePInheritancePClassMethodOverride")->invokeUnsafe<EMethodTestCallResult>(&instance),
		EMethodTestCallResult::MultiplePInheritancePClassMethodOverride
	);
}

//Call an inherited method from child class instance

//1. The virtual method is introduced by the first inherited class
TEST(Rfk_Method_invokeUnsafe, CallParentIntroducedVirtualMethodOnSinglePInheritancePClass)
{
	SinglePInheritancePClass instance;

	SinglePInheritancePClass::staticGetArchetype().getMethodByName("methodSingleNPInheritancePClass", rfk::EMethodFlags::Default, true)->invokeUnsafe<EMethodTestCallResult>(&instance);

	EXPECT_EQ(
		SinglePInheritancePClass::staticGetArchetype().getMethodByName("methodSingleNPInheritancePClass", rfk::EMethodFlags::Default, true)->invokeUnsafe<EMethodTestCallResult>(&instance),
		EMethodTestCallResult::SingleNPInheritancePClass
	);
}

//2. The non-virtual method is introduced by the first inherited class
TEST(Rfk_Method_invokeUnsafe, CallParentIntroducedNonVirtualMethodOnMultipleNPInheritanceNPClass)
{
	MultipleNPInheritanceNPClass instance;

	EXPECT_EQ(
		MultipleNPInheritanceNPClass::staticGetArchetype().getMethodByName("methodNoInheritanceNPClass", rfk::EMethodFlags::Default, true)->invokeUnsafe<EMethodTestCallResult>(&instance),
		EMethodTestCallResult::NoInheritanceNPClass
	);
}

//3. The virtual method is introduced by the first inherited class and overriden in the calling instance
TEST(Rfk_Method_invokeUnsafe, CallParentIntroducedOverridenVirtualMethodOnSinglePInheritancePClass)
{
	SinglePInheritancePClass instance;

	EXPECT_EQ(
		SinglePInheritancePClass::staticGetArchetype().getMethodByName("methodSingleNPInheritancePClass2", rfk::EMethodFlags::Default, true)->invokeUnsafe<EMethodTestCallResult>(&instance),
		EMethodTestCallResult::SinglePInheritancePClass
	);
}

//4. The virtual method is introduced by the second inherited class (and the first inherited class is polymorphic)
// We can't add this test since it is UB to call invokeUnsafe with invalid instance pointer (can't adjust the pointer).
//TEST(Rfk_Method_invokeUnsafe, CallParentIntroducedVirtualMethodOnMultiplePInheritancePClass)
//{
//	MultiplePInheritancePClassMethodOverride instance;
//
//	EXPECT_EQ(
//		MultiplePInheritancePClassMethodOverride::staticGetArchetype().getMethodByName("methodNoInheritancePClass4", rfk::EMethodFlags::Default, true)
//			->invokeUnsafe<EMethodTestCallResult>(&instance),
//		EMethodTestCallResult::NoInheritancePClass
//	);
//}

//5. The non-virtual method is introduced by the second inherited class
TEST(Rfk_Method_invokeUnsafe, CallParent2IntroducedNonVirtualMethodOnMultipleNPInheritanceNPClass)
{
	MultipleNPInheritanceNPClass instance;

	EXPECT_EQ(
		MultipleNPInheritanceNPClass::staticGetArchetype().getMethodByName("methodNoInheritanceNPClass2", rfk::EMethodFlags::Default, true)->invokeUnsafe<EMethodTestCallResult>(&instance),
		EMethodTestCallResult::NoInheritanceNPClass2
	);
}

//5.2. The non-virtual method is introduced by the second inherited class and called from a base
TEST(Rfk_Method_invokeUnsafe, CallParent2IntroducedNonVirtualMethodOnMultipleNPInheritanceNPClassBase)
{
	MultipleNPInheritanceNPClass instance;

	EXPECT_EQ(
		MultipleNPInheritanceNPClass::staticGetArchetype().getMethodByName("methodNoInheritanceNPClass2", rfk::EMethodFlags::Default, true)
			->invokeUnsafe<EMethodTestCallResult>(static_cast<NoInheritanceNPClass*>(&instance)),
		EMethodTestCallResult::NoInheritanceNPClass2
	);
}

//6. The virtual method is introduced by the second inherited class (and the first inherited class is polymorphic) and overriden by instance
//   AND the overriden version in instance is NOT reflected
// We can't add this test since it is UB to call invokeUnsafe with invalid instance pointer (can't adjust the pointer).
//TEST(Rfk_Method_invokeUnsafe, CallParentIntroducedOverridenVirtualMethodOnMultiplePInheritancePClass)
//{
//	MultiplePInheritancePClassMethodOverride instance;
//
//	EXPECT_EQ(
//		MultiplePInheritancePClassMethodOverride::staticGetArchetype().getMethodByName("methodNoInheritancePClass", rfk::EMethodFlags::Default, true)
//			->invokeUnsafe<EMethodTestCallResult>(&instance),
//		EMethodTestCallResult::MultiplePInheritancePClassMethodOverride
//	);
//}

//6.2 The virtual method is introduced by the second inherited class (and the first inherited class is polymorphic) and overriden by instance
//    AND the overriden version in instance is reflected
// We can't add this test since it is UB to call invokeUnsafe with invalid instance pointer (can't adjust the pointer).
//TEST(Rfk_Method_invokeUnsafe, CallParentIntroducedNonReflectedOverridenVirtualMethodOnMultiplePInheritancePClass)
//{
//	MultiplePInheritancePClassMethodOverride instance;
//
//	EXPECT_EQ(
//		MultiplePInheritancePClassMethodOverride::staticGetArchetype().getMethodByName("methodNoInheritancePClass2")
//			->invokeUnsafe<EMethodTestCallResult>(&instance),
//		EMethodTestCallResult::MultiplePInheritancePClassMethodOverride
//	);
//}

//7. The virtual method is introduced by a grandparent class (but in the first inheritance branch: virtual table offset = 0)
//   A<vmethod    B
//   ^            ^
//   |------------|
//		   |
//         C
//		   ^
//         D<instance
TEST(Rfk_Method_invokeUnsafe, CallGrandParentIntroducedVirtualMethodFirstInheritanceBranch)
{
	SinglePInheritancePClassLevel2 instance;

	EXPECT_EQ(
		SinglePInheritancePClassLevel2::staticGetArchetype().getMethodByName("methodSinglePInheritancePClass", rfk::EMethodFlags::Default, true)
			->invokeUnsafe<EMethodTestCallResult>(&instance),
		EMethodTestCallResult::SinglePInheritancePClass
	);
}

//8. The virtual method is introduced by a grandparent class (but NOT in the first inheritance branch: virtual table offset != 0)
//   A            B<vmethod
//   ^            ^
//   |------------|
//		   |
//         C
//		   ^
//         D<instance
// We can't add this test since it is UB to call invokeUnsafe with invalid instance pointer (can't adjust the pointer).
//TEST(Rfk_Method_invokeUnsafe, CallGrandParentIntroducedVirtualMethodNotFirstInheritanceBranch)
//{
//	SinglePInheritancePClassLevel2 instance;
//
//	EXPECT_EQ(
//		SinglePInheritancePClassLevel2::staticGetArchetype().getMethodByName("methodNoInheritancePClass4", rfk::EMethodFlags::Default, true)
//			->invokeUnsafe<EMethodTestCallResult>(&instance),
//		EMethodTestCallResult::NoInheritancePClass
//	);
//}

//9. The non-virtual method is introduced by a grandparent class (but NOT in the first inheritance branch: virtual table offset != 0)
//   A            B<non-vmethod
//   ^            ^
//   |------------|
//		   |
//         C
//		   ^
//         D<instance
TEST(Rfk_Method_invokeUnsafe, CallGrandParentIntroducedNonVirtualMethodNotFirstInheritanceBranch)
{
	SinglePInheritancePClassLevel2 instance;

	EXPECT_EQ(
		SinglePInheritancePClassLevel2::staticGetArchetype().getMethodByName("methodNoInheritancePClass3", rfk::EMethodFlags::Default, true)
			->invokeUnsafe<EMethodTestCallResult>(&instance),
		EMethodTestCallResult::NoInheritancePClass
	);
}

//9.2. The non-virtual method is introduced by a grandparent class (but NOT in the first inheritance branch: virtual table offset != 0)
//	   AND called from a base of the class
//   A<instanceBase   B<non-vmethod
//   ^                ^
//   |----------------|
//		      |
//            C
//		      ^
//            D<instance
TEST(Rfk_Method_invokeUnsafe, CallGrandParentIntroducedNonVirtualMethodNotFirstInheritanceBranchBase)
{
	SinglePInheritancePClassLevel2 instance;

	NoInheritanceNPClass& instanceBase = instance;

	EXPECT_EQ(
		SinglePInheritancePClassLevel2::staticGetArchetype().getMethodByName("methodNoInheritancePClass3", rfk::EMethodFlags::Default, true)
			->invokeUnsafe<EMethodTestCallResult>(&instanceBase),
		EMethodTestCallResult::NoInheritancePClass
	);
}

//=========================================================
//================ Method::checkedInvoke ==================
//=========================================================

TEST(Rfk_Method_checkedInvoke, SuccessfullCall)
{
	TestMethodClass instance;

	EXPECT_EQ(TestMethodClass::staticGetArchetype().getMethodByName("returnIntNoParam")->checkedInvoke<int>(instance), 0);
	EXPECT_EQ(TestMethodClass::staticGetArchetype().getMethodByName("returnIntParamInt")->checkedInvoke<int>(instance, 42), 42);
}

TEST(Rfk_Method_checkedInvoke, ThrowReturnTypeMismatch)
{
	TestMethodClass instance;

	EXPECT_THROW(TestMethodClass::staticGetArchetype().getMethodByName("returnIntNoParam")->checkedInvoke<float>(instance), rfk::ReturnTypeMismatch);
}

TEST(Rfk_Method_checkedInvoke, ReturnNonReflectedType)
{
	TestMethodClass instance;
	NonReflectedClass nrc;

	//Calling with a different non-reflected type is not catched by the checked call
	EXPECT_NO_THROW(TestMethodClass::staticGetArchetype().getMethodByName("returnNonReflectedNoParam")->checkedInvoke<NonReflectedClass2&>(instance, nrc));
	EXPECT_NO_THROW(TestMethodClass::staticGetArchetype().getMethodByName("returnNonReflectedNoParam")->checkedInvoke<NonReflectedClass&>(instance, nrc));
}

TEST(Rfk_Method_checkedInvoke, ThrowArgCountMismatch)
{
	TestMethodClass instance;

	EXPECT_THROW(TestMethodClass::staticGetArchetype().getMethodByName("returnIntParamInt")->checkedInvoke<int>(instance, 1, 2), rfk::ArgCountMismatch); //2 instead of 1
	EXPECT_THROW(TestMethodClass::staticGetArchetype().getMethodByName("noReturnNoParam")->checkedInvoke(instance, 1), rfk::ArgCountMismatch);			 //1 instead of 0
	EXPECT_NO_THROW(TestMethodClass::staticGetArchetype().getMethodByName("noReturnNoParam")->checkedInvoke(instance));
}

TEST(Rfk_Method_checkedInvoke, ThrowArgTypeMismatch)
{
	TestMethodClass instance;

	EXPECT_THROW(TestMethodClass::staticGetArchetype().getMethodByName("returnIntParamInt")->checkedInvoke<int>(instance, 1.0f), rfk::ArgTypeMismatch);	//float instead of int
}

TEST(Rfk_Method_checkedInvoke, ThrowInvalidCaller)
{
	TestMethodClass2 instance;

	EXPECT_THROW(TestMethodClass::staticGetArchetype().getMethodByName("virtualNoReturnNoParam")->checkedInvoke(instance), rfk::InvalidArchetype);
}

TEST(Rfk_Method_checkedInvoke, CatchForwardDeclaredTypeMismatch)
{
	TestMethodClass instance;
	ForwardDeclaredClass fdc;
	float value;

	EXPECT_THROW(TestMethodClass::staticGetArchetype().getMethodByName("returnFwdClassParamFwdClass")->checkedInvoke<int&>(instance, &fdc), rfk::ReturnTypeMismatch);
	EXPECT_THROW(TestMethodClass::staticGetArchetype().getMethodByName("returnFwdClassParamFwdClass")->checkedInvoke<ForwardDeclaredClass*>(instance, value), rfk::ArgTypeMismatch);
	EXPECT_EQ(TestMethodClass::staticGetArchetype().getMethodByName("returnFwdClassParamFwdClass")->checkedInvoke<ForwardDeclaredClass*>(instance, &fdc), &fdc);	//Normal call
}

TEST(Rfk_Method_checkedInvoke, NonReflectedTypeBypassArgTypeMismatch)
{
	TestMethodClass instance;
	NonReflectedClass nrc;

	EXPECT_NO_THROW(TestMethodClass::staticGetArchetype().getMethodByName("returnNonReflectedNoParam")->checkedInvoke<NonReflectedClass&>(instance, nrc));
	EXPECT_EQ(nrc.i, 42);
}

TEST(Rfk_Method_checkedInvoke, ThrowingCall)
{
	TestMethodClass instance;

	EXPECT_THROW(TestMethodClass::staticGetArchetype().getMethodByName("throwing")->checkedInvoke(instance), std::logic_error);
}