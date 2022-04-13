#include <gtest/gtest.h>
#include <Refureku/Refureku.h>

#include "TestCast.h"

//=========================================================
//========== rfk::dynamicCast<Target, Source> =============
//=========================================================

TEST(Rfk_dynamicCast_Target_Source, CastToStaticSelfType)
{
	GrandChild1 grandChild1;

	//Doesn't compile as expected
	//rfk::dynamicCast<GrandChild1>(&grandChild1);
}

TEST(Rfk_dynamicCast_Target_Source, CastToSourceParentStaticType)
{
	//Doesn't compile as expected because upcast
	//rfk::dynamicCast<Child1>(&grandChild1);
}

TEST(Rfk_dynamicCast_Target_Source, SuccessfulDownCastToSelfType)
{
	GrandChild1 grandChild1;
	Base* grandChild1AsBase = &grandChild1;

	EXPECT_EQ(rfk::dynamicCast<GrandChild1>(grandChild1AsBase), &grandChild1);
}

TEST(Rfk_dynamicCast_Target_Source, SuccessfulDownCastNotConstToNotConst)
{
	GrandChild1 grandChild1;
	Base* grandChild1AsBase = &grandChild1;
	Child1* grandChild1AsChild1 = &grandChild1;

	EXPECT_EQ(rfk::dynamicCast<Child1>(grandChild1AsBase), grandChild1AsChild1);
}

TEST(Rfk_dynamicCast_Target_Source, SuccessfulDownCastConstToConst)
{
	Child1 child1;
	GrandChild1 grandChild1;

	Base const* grandChild1AsBase = &grandChild1;
	EXPECT_EQ(rfk::dynamicCast<GrandChild1 const>(grandChild1AsBase), &grandChild1);

	Child1 const* grandChild1AsChild1 = &grandChild1;
	EXPECT_EQ(rfk::dynamicCast<Child1 const>(grandChild1AsBase), grandChild1AsChild1);
}

TEST(Rfk_dynamicCast_Target_Source, SuccessfulDownCastNotConstToConst)
{
	Child1 child1;
	GrandChild1 grandChild1;

	Base* grandChild1AsBase = &grandChild1;
	EXPECT_EQ(rfk::dynamicCast<GrandChild1 const>(grandChild1AsBase), &grandChild1);

	Child1* grandChild1AsChild1 = &grandChild1;
	EXPECT_EQ(rfk::dynamicCast<Child1 const>(grandChild1AsBase), grandChild1AsChild1);
}

TEST(Rfk_dynamicCast_Target_Source, DownCastConstToNotConst)
{
	Child1 child1;
	GrandChild1 grandChild1;

	//This doesn't compile as expected: const -> non-const implicit conversion forbidden
	/*
	Base const* grandChild1AsBase = &grandChild1;
	EXPECT_EQ(rfk::dynamicCast<GrandChild1>(grandChild1AsBase), &grandChild1);

	Child1 const* grandChild1AsChild1 = &grandChild1;
	EXPECT_EQ(rfk::dynamicCast<Child1>(grandChild1AsBase), grandChild1AsChild1);
	*/
}

TEST(Rfk_dynamicCast_Target_Source, FailedDownCast)
{
	Child1 child1;

	EXPECT_EQ(rfk::dynamicCast<GrandChild1>(&child1), nullptr);
}

TEST(Rfk_dynamicCast_Target_Source, SuccessfulDynamicCastWithMultipleInheritance)
{
	Child3 child3;

	Base*	child3AsBase = &child3;
	Child1*	child3AsChild1 = &child3;
	Base2*	child3AsBase2 = &child3;

	EXPECT_EQ(rfk::dynamicCast<Child1>(child3AsBase), child3AsChild1);
	EXPECT_EQ(rfk::dynamicCast<Base2>(child3AsBase), child3AsBase2);
	EXPECT_EQ(rfk::dynamicCast<Base>(child3AsBase2), child3AsBase);
}


TEST(Rfk_dynamicCast_Target_Source, CastInstanceWithoutGetArchetype)
{
	NotObjectChild1 child1;
	NotObjectBase* child1AsBase = &child1;

	//Doesn't compile as expected since NotObjectBase doesn't implement virtual getArchetype
	//EXPECT_EQ(rfk::dynamicCast<NotObjectChild1>(child1AsBase), &child1);
}

//===================================================================================================
//========== rfk::dynamicCast<Target>(void*, Struct const&, Struct const&, Struct const&) ===========
//===================================================================================================

TEST(Rfk_dynamicCast_Target, NullptrCast)
{
	EXPECT_EQ(rfk::dynamicCast<void>(nullptr, Base::staticGetArchetype(), Child1::staticGetArchetype(), Child3::staticGetArchetype()), nullptr);
}

TEST(Rfk_dynamicCast_Target, SuccessfulUpCastWithoutMemoryOffset)
{
	GrandChild1 grandChild1;
	Base* grandChild1AsBase = &grandChild1;

	EXPECT_EQ(rfk::dynamicCast<void>(&grandChild1, GrandChild1::staticGetArchetype(), GrandChild1::staticGetArchetype(), Base::staticGetArchetype()), grandChild1AsBase);
}

TEST(Rfk_dynamicCast_Target, FailedUpCastWithoutMemoryOffset)
{
	GrandChild1 grandChild1;

	EXPECT_EQ(rfk::dynamicCast<void>(&grandChild1, GrandChild1::staticGetArchetype(), GrandChild1::staticGetArchetype(), Base2::staticGetArchetype()), nullptr);
}

TEST(Rfk_dynamicCast_Target, SuccessfulDownCastWithoutMemoryOffsetWithDynamicArchetypeEqualsTargetArchetype)
{
	GrandChild1 grandChild1;
	Base* grandChild1AsBase = &grandChild1;

	EXPECT_EQ(rfk::dynamicCast<void>(grandChild1AsBase, Base::staticGetArchetype(), GrandChild1::staticGetArchetype(), GrandChild1::staticGetArchetype()), &grandChild1);
}

TEST(Rfk_dynamicCast_Target, SuccessfulDownCastWithoutMemoryOffsetWithDynamicArchetypeDifferentFromTargetArchetype)
{
	GrandChild1 grandChild1;
	Base* grandChild1AsBase = &grandChild1;
	Child1* grandChild1AsChild1 = &grandChild1;

	EXPECT_EQ(rfk::dynamicCast<void>(grandChild1AsBase, Base::staticGetArchetype(), GrandChild1::staticGetArchetype(), Child1::staticGetArchetype()), grandChild1AsChild1);
}

TEST(Rfk_dynamicCast_Target, SuccessfulDownUpCastWithMemoryOffset)
{
	Child3 child3;

	Base2* child3AsBase2 = &child3;
	Base* child3AsBase = &child3;

	EXPECT_EQ(rfk::dynamicCast<void>(child3AsBase2, Base2::staticGetArchetype(), Child3::staticGetArchetype(), Base::staticGetArchetype()), child3AsBase);
}

TEST(Rfk_dynamicCast_Target, SuccessfulDownUpCastWithoutMemoryOffset)
{
	Child4 child4;

	NonVirtualBase* child4AsNonVirtualBase = &child4;
	Base* child4AsBase = &child4;

	EXPECT_EQ(rfk::dynamicCast<void>(child4AsNonVirtualBase, NonVirtualBase::staticGetArchetype(), Child4::staticGetArchetype(), Base::staticGetArchetype()), child4AsBase);
}

TEST(Rfk_dynamicCast_Target, FailedDownUpCastDuringDownCast)
{
	Child4 child4;

	NonVirtualBase* child4AsNonVirtualBase = &child4;
	Base* child4AsBase = &child4;

	EXPECT_EQ(rfk::dynamicCast<void>(child4AsNonVirtualBase, NonVirtualBase::staticGetArchetype(), Child3::staticGetArchetype(), Base::staticGetArchetype()), nullptr);
}

TEST(Rfk_dynamicCast_Target, FailedDownUpCastDuringUpCast)
{
	Child4 child4;

	NonVirtualBase* child4AsNonVirtualBase = &child4;
	Base* child4AsBase = &child4;

	EXPECT_EQ(rfk::dynamicCast<void>(child4AsNonVirtualBase, NonVirtualBase::staticGetArchetype(), Child4::staticGetArchetype(), Base2::staticGetArchetype()), nullptr);
}