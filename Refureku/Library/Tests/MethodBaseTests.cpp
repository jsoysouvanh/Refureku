#include <gtest/gtest.h>
#include <Refureku/Refureku.h>

#include "TestMethodBase.h"

//=========================================================
//============= MethodBaseTests Code Coverage =============
//=========================================================

TEST(MethodBaseTests, CodeCoverage)
{
	TestMethodBaseClassChild tmbcc;

	EXPECT_NO_THROW(tmbcc.inlineMethodInHeader());
	EXPECT_NO_THROW(tmbcc.inlineMethodInSource());
	EXPECT_NO_THROW(tmbcc.funcWithParams1(1, 2, 3));
	EXPECT_NO_THROW(tmbcc.funcWithParams2(1, 2, 3));
	EXPECT_NO_THROW(tmbcc.funcWithParams3(1, 2, 3));
	EXPECT_NO_THROW(tmbcc.funcWithParams4(1, 2, 3));
	EXPECT_NO_THROW(tmbcc.funcWithParams5(1, 2, 3));
	
	EXPECT_NO_THROW(tmbcc.virtualMethod());
	EXPECT_NO_THROW(tmbcc.virtualMethod2());
	EXPECT_NO_THROW(tmbcc.pureVirtualMethod());
	EXPECT_NO_THROW(tmbcc.pureVirtualMethod2());

	TestMethodBaseClassChild2 tmbcc2;
	TestMethodBaseClassChild& tmbcc2Ref = tmbcc2;

	EXPECT_NO_THROW(tmbcc2Ref.virtualMethod());
	EXPECT_NO_THROW(tmbcc2Ref.virtualMethod2());
	EXPECT_NO_THROW(tmbcc2Ref.pureVirtualMethod());
	EXPECT_NO_THROW(tmbcc2Ref.pureVirtualMethod2());
}

//=========================================================
//=============== MethodBase::getOuterEntity ==============
//=========================================================

TEST(Rfk_MethodBase_getOuterEntity, OwnClassMethod)
{
	EXPECT_EQ(TestMethodBaseClass::staticGetArchetype().getStaticMethodByName("staticMethod")->getOuterEntity(), &TestMethodBaseClass::staticGetArchetype());
}

TEST(Rfk_MethodBase_getOuterEntity, InheritedMethod)
{
	rfk::StaticMethod const* method = TestMethodBaseClassChild::staticGetArchetype().getStaticMethodByName("staticMethod", rfk::EMethodFlags::Default, true);

	EXPECT_NE(method, nullptr);
	EXPECT_NE(method->getOuterEntity(), &TestMethodBaseClassChild::staticGetArchetype());
	EXPECT_EQ(method->getOuterEntity(), &TestMethodBaseClass::staticGetArchetype());
}

//=========================================================
//============== MethodBase::hasSameSignature =============
//=========================================================

TEST(Rfk_MethodBase_hasSameSignature, SameSignature)
{
	EXPECT_TRUE(TestMethodBaseClass::staticGetArchetype().getMethodByName("funcWithParams1")->hasSameSignature(*TestMethodBaseClass::staticGetArchetype().getMethodByName("funcWithParams2")));
}

TEST(Rfk_MethodBase_hasSameSignature, DifferentConstness)
{
	EXPECT_FALSE(TestMethodBaseClass::staticGetArchetype().getMethodByName("funcWithParams1")->hasSameSignature(*TestMethodBaseClass::staticGetArchetype().getMethodByName("funcWithParams3")));
}

TEST(Rfk_MethodBase_hasSameSignature, DifferentReturnType)
{
	EXPECT_FALSE(TestMethodBaseClass::staticGetArchetype().getMethodByName("funcWithParams1")->hasSameSignature(*TestMethodBaseClass::staticGetArchetype().getMethodByName("funcWithParams4")));
}

TEST(Rfk_MethodBase_hasSameSignature, DifferentParams)
{
	EXPECT_FALSE(TestMethodBaseClass::staticGetArchetype().getMethodByName("funcWithParams1")->hasSameSignature(*TestMethodBaseClass::staticGetArchetype().getMethodByName("funcWithParams5")));
}

//=========================================================
//================== MethodBase::isStatic =================
//=========================================================

TEST(Rfk_MethodBase_isStatic, Static)
{
	EXPECT_TRUE(TestMethodBaseClass::staticGetArchetype().getStaticMethodByName("staticMethod")->isStatic());
}

TEST(Rfk_MethodBase_isStatic, NonStatic)
{
	EXPECT_FALSE(TestMethodBaseClass::staticGetArchetype().getMethodByName("virtualMethod")->isStatic());
}

//=========================================================
//================== MethodBase::isInline =================
//=========================================================

TEST(Rfk_MethodBase_isInline, InlineQualifierDefinedInHeader)
{
	EXPECT_TRUE(TestMethodBaseClass::staticGetArchetype().getMethodByName("inlineMethodInHeader")->isInline());
}

TEST(Rfk_MethodBase_isInline, InlineQualifiedDefinedInSource)
{
	EXPECT_TRUE(TestMethodBaseClass::staticGetArchetype().getMethodByName("inlineMethodInSource")->isInline());
}

TEST(Rfk_MethodBase_isInline, NonInlineQualifiedDefinedInHeader)
{
	EXPECT_TRUE(TestMethodBaseClass::staticGetArchetype().getMethodByName("funcWithParams1")->isInline());
	EXPECT_TRUE(TestMethodBaseClass::staticGetArchetype().getMethodByName("funcWithParams2")->isInline());
	EXPECT_TRUE(TestMethodBaseClass::staticGetArchetype().getMethodByName("funcWithParams3")->isInline());
	EXPECT_TRUE(TestMethodBaseClass::staticGetArchetype().getMethodByName("funcWithParams4")->isInline());
	EXPECT_TRUE(TestMethodBaseClass::staticGetArchetype().getMethodByName("funcWithParams5")->isInline());
	EXPECT_TRUE(TestMethodBaseClass::staticGetArchetype().getMethodByName("virtualMethod")->isInline());
}

TEST(Rfk_MethodBase_isInline, NonInlineQualifiedDefinedInSource)
{
	EXPECT_FALSE(TestMethodBaseClass::staticGetArchetype().getMethodByName("constMethod")->isInline());
}

//=========================================================
//================= MethodBase::isVirtual =================
//=========================================================

TEST(Rfk_MethodBase_isVirtual, BaseVirtualMethod)
{
	EXPECT_TRUE(TestMethodBaseClass::staticGetArchetype().getMethodByName("virtualMethod")->isVirtual());
}

TEST(Rfk_MethodBase_isVirtual, PureVirtual)
{
	EXPECT_TRUE(TestMethodBaseClass::staticGetArchetype().getMethodByName("pureVirtualMethod")->isVirtual());
}

TEST(Rfk_MethodBase_isVirtual, OverrideWithoutVirtualQualifier)
{
	EXPECT_TRUE(TestMethodBaseClassChild::staticGetArchetype().getMethodByName("virtualMethod")->isVirtual());
}

TEST(Rfk_MethodBase_isVirtual, NonVirtual)
{
	EXPECT_FALSE(TestMethodBaseClass::staticGetArchetype().getMethodByName("inlineMethodInHeader")->isVirtual());
	EXPECT_FALSE(TestMethodBaseClass::staticGetArchetype().getMethodByName("funcWithParams1")->isVirtual());
}

//=========================================================
//=============== MethodBase::isPureVirtual ===============
//=========================================================

TEST(Rfk_MethodBase_isPureVirtual, BaseVirtualMethod)
{
	EXPECT_FALSE(TestMethodBaseClass::staticGetArchetype().getMethodByName("virtualMethod")->isPureVirtual());
}

TEST(Rfk_MethodBase_isPureVirtual, PureVirtual)
{
	EXPECT_TRUE(TestMethodBaseClass::staticGetArchetype().getMethodByName("pureVirtualMethod")->isPureVirtual());
}

TEST(Rfk_MethodBase_isPureVirtual, OverrideWithoutVirtualQualifier)
{
	EXPECT_FALSE(TestMethodBaseClassChild::staticGetArchetype().getMethodByName("virtualMethod")->isPureVirtual());
}

TEST(Rfk_MethodBase_isPureVirtual, NonVirtual)
{
	EXPECT_FALSE(TestMethodBaseClass::staticGetArchetype().getMethodByName("inlineMethodInHeader")->isPureVirtual());
	EXPECT_FALSE(TestMethodBaseClass::staticGetArchetype().getMethodByName("funcWithParams1")->isPureVirtual());
}

//=========================================================
//================= MethodBase::isOverride ================
//=========================================================

TEST(Rfk_MethodBase_isOverride, BaseVirtualMethod)
{
	EXPECT_FALSE(TestMethodBaseClass::staticGetArchetype().getMethodByName("virtualMethod")->isOverride());
}

TEST(Rfk_MethodBase_isOverride, PureVirtual)
{
	EXPECT_FALSE(TestMethodBaseClass::staticGetArchetype().getMethodByName("pureVirtualMethod")->isOverride());
}

TEST(Rfk_MethodBase_isOverride, OverrideWithoutVirtualQualifier)
{
	EXPECT_TRUE(TestMethodBaseClassChild::staticGetArchetype().getMethodByName("virtualMethod")->isOverride());
	EXPECT_TRUE(TestMethodBaseClassChild::staticGetArchetype().getMethodByName("pureVirtualMethod")->isOverride());
}

TEST(Rfk_MethodBase_isOverride, OverrideWithoutOverrideQualifier)
{
	EXPECT_FALSE(TestMethodBaseClassChild::staticGetArchetype().getMethodByName("virtualMethod2")->isOverride());
	EXPECT_FALSE(TestMethodBaseClassChild::staticGetArchetype().getMethodByName("pureVirtualMethod2")->isOverride());
}

TEST(Rfk_MethodBase_isOverride, NonVirtual)
{
	EXPECT_FALSE(TestMethodBaseClass::staticGetArchetype().getMethodByName("inlineMethodInHeader")->isOverride());
	EXPECT_FALSE(TestMethodBaseClass::staticGetArchetype().getMethodByName("funcWithParams1")->isOverride());
}

//=========================================================
//================== MethodBase::isFinal ==================
//=========================================================

TEST(Rfk_MethodBase_isFinal, BaseVirtualMethod)
{
	EXPECT_FALSE(TestMethodBaseClass::staticGetArchetype().getMethodByName("virtualMethod")->isFinal());
}

TEST(Rfk_MethodBase_isFinal, PureVirtual)
{
	EXPECT_FALSE(TestMethodBaseClass::staticGetArchetype().getMethodByName("pureVirtualMethod")->isFinal());
}

TEST(Rfk_MethodBase_isFinal, OverrideNonFinal)
{
	EXPECT_FALSE(TestMethodBaseClassChild::staticGetArchetype().getMethodByName("virtualMethod")->isFinal());
}

TEST(Rfk_MethodBase_isFinal, OverrideFinal)
{
	EXPECT_TRUE(TestMethodBaseClassChild::staticGetArchetype().getMethodByName("pureVirtualMethod")->isFinal());
}

TEST(Rfk_MethodBase_isFinal, OverrideNonFinalInFinalClass)
{
	EXPECT_FALSE(TestMethodBaseClassChild2::staticGetArchetype().getMethodByName("virtualMethod")->isFinal());
}

//=========================================================
//================== MethodBase::isConst ==================
//=========================================================

TEST(Rfk_MethodBase_isConst, Const)
{
	EXPECT_TRUE(TestMethodBaseClass::staticGetArchetype().getMethodByName("constMethod")->isConst());
}

TEST(Rfk_MethodBase_isConst, NonConst)
{
	EXPECT_FALSE(TestMethodBaseClass::staticGetArchetype().getMethodByName("inlineMethodInHeader")->isConst());
}

//=========================================================
//================= MethodBase::getAccess =================
//=========================================================

TEST(Rfk_MethodBase_getAccess, Private)
{
	EXPECT_EQ(TestMethodBaseClass::staticGetArchetype().getMethodByName("constMethod")->getAccess(), rfk::EAccessSpecifier::Private);
}

TEST(Rfk_MethodBase_getAccess, Protected)
{
	EXPECT_EQ(TestMethodBaseClass::staticGetArchetype().getMethodByName("virtualMethod")->getAccess(), rfk::EAccessSpecifier::Protected);
}

TEST(Rfk_MethodBase_getAccess, Public)
{
	EXPECT_EQ(TestMethodBaseClass::staticGetArchetype().getMethodByName("inlineMethodInHeader")->getAccess(), rfk::EAccessSpecifier::Public);
}

TEST(Rfk_MethodBase_getAccess, OverrideChangingAccess)
{
	EXPECT_EQ(TestMethodBaseClassChild::staticGetArchetype().getMethodByName("virtualMethod")->getAccess(), rfk::EAccessSpecifier::Public);
	EXPECT_EQ(TestMethodBaseClassChild::staticGetArchetype().getMethodByName("virtualMethod2")->getAccess(), rfk::EAccessSpecifier::Public);
	EXPECT_EQ(TestMethodBaseClassChild::staticGetArchetype().getMethodByName("pureVirtualMethod")->getAccess(), rfk::EAccessSpecifier::Public);
	EXPECT_EQ(TestMethodBaseClassChild::staticGetArchetype().getMethodByName("pureVirtualMethod2")->getAccess(), rfk::EAccessSpecifier::Public);

	EXPECT_EQ(TestMethodBaseClassChild2::staticGetArchetype().getMethodByName("virtualMethod")->getAccess(), rfk::EAccessSpecifier::Private);
	EXPECT_EQ(TestMethodBaseClassChild2::staticGetArchetype().getMethodByName("virtualMethod2")->getAccess(), rfk::EAccessSpecifier::Private);
	EXPECT_EQ(TestMethodBaseClassChild2::staticGetArchetype().getMethodByName("pureVirtualMethod2")->getAccess(), rfk::EAccessSpecifier::Private);
}